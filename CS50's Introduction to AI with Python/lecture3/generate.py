import sys
from collections import deque

from crossword import *


class CrosswordCreator():

    def __init__(self, crossword):
        """
        Create new CSP crossword generate.
        """
        self.crossword = crossword
        self.domains = {
            var: self.crossword.words.copy()
            for var in self.crossword.variables
        }

    def letter_grid(self, assignment):
        """
        Return 2D array representing a given assignment.
        """
        letters = [
            [None for _ in range(self.crossword.width)]
            for _ in range(self.crossword.height)
        ]
        for variable, word in assignment.items():
            direction = variable.direction
            for k in range(len(word)):
                i = variable.i + (k if direction == Variable.DOWN else 0)
                j = variable.j + (k if direction == Variable.ACROSS else 0)
                letters[i][j] = word[k]
        return letters

    def print(self, assignment):
        """
        Print crossword assignment to the terminal.
        """
        letters = self.letter_grid(assignment)
        for i in range(self.crossword.height):
            for j in range(self.crossword.width):
                if self.crossword.structure[i][j]:
                    print(letters[i][j] or " ", end="")
                else:
                    print("█", end="")
            print()

    def save(self, assignment, filename):
        """
        Save crossword assignment to an image file.
        """
        from PIL import Image, ImageDraw, ImageFont
        cell_size = 100
        cell_border = 2
        interior_size = cell_size - 2 * cell_border
        letters = self.letter_grid(assignment)

        # Create a blank canvas
        img = Image.new(
            "RGBA",
            (self.crossword.width * cell_size,
             self.crossword.height * cell_size),
            "black"
        )
        font = ImageFont.truetype("assets/fonts/OpenSans-Regular.ttf", 80)
        draw = ImageDraw.Draw(img)

        for i in range(self.crossword.height):
            for j in range(self.crossword.width):

                rect = [
                    (j * cell_size + cell_border,
                     i * cell_size + cell_border),
                    ((j + 1) * cell_size - cell_border,
                     (i + 1) * cell_size - cell_border)
                ]
                if self.crossword.structure[i][j]:
                    draw.rectangle(rect, fill="white")
                    if letters[i][j]:
                        _, _, w, h = draw.textbbox((0, 0), letters[i][j], font=font)
                        draw.text(
                            (rect[0][0] + ((interior_size - w) / 2),
                             rect[0][1] + ((interior_size - h) / 2) - 10),
                            letters[i][j], fill="black", font=font
                        )

        img.save(filename)

    def solve(self):
        """
        Enforce node and arc consistency, and then solve the CSP.
        """
        self.enforce_node_consistency()
        self.ac3()
        return self.backtrack(dict())

    def enforce_node_consistency(self):
        """
        Update `self.domains` such that each variable is node-consistent.
        (Remove any values that are inconsistent with a variable's unary
         constraints; in this case, the length of the word.)
        """
        for variable in self.domains:
            # 创建要删除的单词列表
            to_remove = set()
            for word in self.domains[variable]:
                # 如果单词长度不等于变量长度，则不符合约束
                if len(word) != variable.length:
                    to_remove.add(word)
            # 从域中删除不符合约束的单词
            self.domains[variable] -= to_remove

    def revise(self, x, y):
        """
        Make variable `x` arc consistent with variable `y`.
        To do so, remove values from `self.domains[x]` for which there is no
        possible corresponding value for `y` in `self.domains[y]`.

        Return True if a revision was made to the domain of `x`; return
        False if no revision was made.
        """
        revised = False
        overlap = self.crossword.overlaps[x, y]
        if overlap is None:
            return False
        i, j = overlap
        to_remove = set()

        for word_x in self.domains[x]:
            # 检查是否存在一个word_y 使得word_x[i] == word_y[j]
            found = False
            for word_y in self.domains[y]:
                if word_x[i] == word_y[j]:
                    found = True
                    break
            # 如果没有找到匹配的word_y,则从x的域中删除word_x
            if not found:
                to_remove.add(word_x)
                revised = True
        self.domains[x] -= to_remove
        return revised

    def ac3(self, arcs=None):
        """
        Update `self.domains` such that each variable is arc consistent.
        If `arcs` is None, begin with initial list of all arcs in the problem.
        Otherwise, use `arcs` as the initial list of arcs to make consistent.

        Return True if arc consistency is enforced and no domains are empty;
        return False if one or more domains end up empty.
        """
        queue = deque()

        # 初始化队列
        if arcs is None:
            # 添加所有可能的弧
            for x in self.domains:
                for y in self.crossword.neighbors(x):
                    queue.append((x, y))
        else:
            queue = deque(arcs)

        while queue:
            x, y = queue.popleft()
            if self.revise(x, y):
                # 如果x的域变为空，则问题无解
                if len(self.domains[x]) == 0:
                    return False
                # 将x的所有邻居（除了y）重新加入队列
                for z in self.crossword.neighbors(x):
                    if z != y:
                        queue.append((z, x))
        return True

    def assignment_complete(self, assignment):
        """
        Return True if `assignment` is complete (i.e., assigns a value to each
        crossword variable); return False otherwise.
        """
        return len(assignment) == len(self.crossword.variables)

    def consistent(self, assignment):
        """
        Return True if `assignment` is consistent (i.e., words fit in crossword
        puzzle without conflicting characters); return False otherwise.
        """
        # 检查所有值是否不同
        if len(set(assignment.values())) != len(assignment.values()):
            return False

        for variable, word in assignment.items():
            # 检查单词长度是否正确
            if len(word) != variable.length:
                return False

            # 检查与邻居的冲突
            for neighbor in self.crossword.neighbors(variable):
                if neighbor in assignment:
                    overlap = self.crossword.overlaps[variable,neighbor]
                    if overlap:
                        i, j = overlap
                        if word[i] != assignment[neighbor][j]:
                            return False
        return True

    def order_domain_values(self, var, assignment):
        """
        Return a list of values in the domain of `var`, in order by
        the number of values they rule out for neighboring variables.
        The first value in the list, for example, should be the one
        that rules out the fewest values among the neighbors of `var`.
        """
        # 计算每个值对未分配邻居的影响
        value_scores = []

        for value in self.domains[var]:
            count = 0
            # 检查所有未分配的邻居
            for neighbor in self.crossword.neighbors(var):
                if neighbor not in assignment:
                    overlap = self.crossword.overlaps[var, neighbor]
                    if overlap:
                        i, j = overlap
                        # 计算有多少邻居的值会被排除
                        for neighbor_value in self.domains[neighbor]:
                            if value[i] != neighbor_value[j]:
                                count += 1
            value_scores.append((value, count))

            # 按影响大小从小到大排序
            value_scores.sort(key=lambda x: x[1])
            return [value for value, _ in value_scores]

    def select_unassigned_variable(self, assignment):
        """
        Return an unassigned variable not already part of `assignment`.
        Choose the variable with the minimum number of remaining values
        in its domain. If there is a tie, choose the variable with the highest
        degree. If there is a tie, any of the tied variables are acceptable
        return values.
        """
        unassigned = [v for v in self.crossword.variables if v not in assignment]

        # 按剩余值数量排序
        unassigned.sort(key=lambda  v: len(self.domains[v]))

        # 如果有多个变量有相同的最小剩余值数量，按度数（邻居数量）排序
        min_domain_size = len(self.domains[unassigned[0]])
        candidates = [v for v in unassigned if len(self.domains[v]) == min_domain_size]

        if len(candidates) > 1:
            # 按度数降序排序（度数高的在前）
            candidates.sort(key=lambda  v: len(self.crossword.neighbors(v)), reverse=True)

        return candidates[0]

    def backtrack(self, assignment):
        """
        Using Backtracking Search, take as input a partial assignment for the
        crossword and return a complete assignment if possible to do so.

        `assignment` is a mapping from variables (keys) to words (values).

        If no assignment is possible, return None.
        """
        # 如果赋值已完成，返回结果
        if self.assignment_complete(assignment):
            return assignment
        # 选择未分配的变量
        var = self.select_unassigned_variable(assignment)

        # 尝试变量的所有可能值
        for value in self.order_domain_values(var, assignment):
            # 创建新的赋值副本
            new_assignment =assignment.copy()
            new_assignment[var] = value

            # 检查一致性
            if self.consistent(new_assignment):
                # 进行推理（维护弧一致性）
                domains_backup = self.domains.copy()
                inferences = self.ac3([(neighbor, var) for neighbor in self.crossword.neighbors(var) if neighbor not in new_assignment])

                if inferences:
                    result = self.backtrack(new_assignment)
                    if result is not None:
                        return result

                    # 回溯：恢复域
                    self.domains = domains_backup

        return None



def main():

    # Check usage
    if len(sys.argv) not in [3, 4]:
        sys.exit("Usage: python generate.py structure words [output]")

    # Parse command-line arguments
    structure = sys.argv[1]
    words = sys.argv[2]
    output = sys.argv[3] if len(sys.argv) == 4 else None

    # Generate crossword
    crossword = Crossword(structure, words)
    creator = CrosswordCreator(crossword)
    assignment = creator.solve()

    # Print result
    if assignment is None:
        print("No solution.")
    else:
        creator.print(assignment)
        if output:
            creator.save(assignment, output)


if __name__ == "__main__":
    main()
