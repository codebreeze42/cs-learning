import itertools
import random


class Minesweeper():
    """
    Minesweeper game representation
    """

    def __init__(self, height=8, width=8, mines=8):

        # Set initial width, height, and number of mines
        self.height = height
        self.width = width
        self.mines = set()

        # Initialize an empty field with no mines
        self.board = []
        for i in range(self.height):
            row = []
            for j in range(self.width):
                row.append(False)
            self.board.append(row)

        # Add mines randomly
        while len(self.mines) != mines:
            i = random.randrange(height)
            j = random.randrange(width)
            if not self.board[i][j]:
                self.mines.add((i, j))
                self.board[i][j] = True

        # At first, player has found no mines
        self.mines_found = set()

    def print(self):
        """
        Prints a text-based representation
        of where mines are located.
        """
        for i in range(self.height):
            print("--" * self.width + "-")
            for j in range(self.width):
                if self.board[i][j]:
                    print("|X", end="")
                else:
                    print("| ", end="")
            print("|")
        print("--" * self.width + "-")

    def is_mine(self, cell):
        i, j = cell
        return self.board[i][j]

    def nearby_mines(self, cell):
        """
        Returns the number of mines that are
        within one row and column of a given cell,
        not including the cell itself.
        """

        # Keep count of nearby mines
        count = 0

        # Loop over all cells within one row and column
        for i in range(cell[0] - 1, cell[0] + 2):
            for j in range(cell[1] - 1, cell[1] + 2):

                # Ignore the cell itself
                if (i, j) == cell:
                    continue

                # Update count if cell in bounds and is mine
                if 0 <= i < self.height and 0 <= j < self.width:
                    if self.board[i][j]:
                        count += 1

        return count

    def won(self):
        """
        Checks if all mines have been flagged.
        """
        return self.mines_found == self.mines


class Sentence():
    """
    Logical statement about a Minesweeper game
    A sentence consists of a set of board cells,
    and a count of the number of those cells which are mines.
    """

    def __init__(self, cells, count):
        self.cells = set(cells)
        self.count = count

    def __eq__(self, other):
        return self.cells == other.cells and self.count == other.count

    def __str__(self):
        return f"{self.cells} = {self.count}"

    def known_mines(self):
        """
        Returns the set of all cells in self.cells known to be mines.
        """

        if len(self.cells) == self.count and self.count > 0:
            return set(self.cells)
        return set()

    def known_safes(self):
        """
        Returns the set of all cells in self.cells known to be safe.
        """
        if self.count == 0:
            return set(self.cells)
        return set()

    def mark_mine(self, cell):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be a mine.
        """
        if cell in self.cells:
            self.cells.remove(cell)
            self.count -= 1

    def mark_safe(self, cell):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be safe.
        """
        if cell in self.cells:
            self.cells.remove(cell)


class MinesweeperAI():
    """
    Minesweeper game player
    """

    def __init__(self, height=8, width=8):

        # Set initial height and width
        self.height = height
        self.width = width

        # Keep track of which cells have been clicked on
        self.moves_made = set()

        # Keep track of cells known to be safe or mines
        self.mines = set()
        self.safes = set()

        # List of sentences about the game known to be true
        self.knowledge = []

    def mark_mine(self, cell):
        """
        Marks a cell as a mine, and updates all knowledge
        to mark that cell as a mine as well.
        """
        self.mines.add(cell)
        for sentence in self.knowledge:
            sentence.mark_mine(cell)

    def mark_safe(self, cell):
        """
        Marks a cell as safe, and updates all knowledge
        to mark that cell as safe as well.
        """
        self.safes.add(cell)
        for sentence in self.knowledge:
            sentence.mark_safe(cell)

    def add_knowledge(self, cell, count):
        """
        Called when the Minesweeper board tells us, for a given
        safe cell, how many neighboring cells have mines in them.

        This function should:
            1) mark the cell as a move that has been made
            2) mark the cell as safe
            3) add a new sentence to the AI's knowledge base
               based on the value of `cell` and `count`
            4) mark any additional cells as safe or as mines
               if it can be concluded based on the AI's knowledge base
            5) add any new sentences to the AI's knowledge base
               if they can be inferred from existing knowledge
        """
        # 1) mark the cell as a move that has been made
        self.moves_made.add(cell)
        # 2) mark the cell as safe
        self.mark_safe(cell)
        # 3) add a new sentence to the AI's knowledge base
        neighbors = set()
        i, j = cell
        known_mine_count = 0
        # 获取相邻格子
        for di in [-1,0,1]:
            for dj in [-1,0,1]:
                if di == 0 and dj == 0:
                    continue
                ni, nj = i + di, j + dj
                if 0 <= ni < self.height and 0 <= nj < self.width:
                    neighbor_cell = (ni, nj)
                    # 排除已知安全格和地雷
                    if neighbor_cell in self.mines:
                        known_mine_count += 1

                    elif (neighbor_cell not in self.safes and
                          neighbor_cell not in self.moves_made):
                        neighbors.add(neighbor_cell)
        adjusted_count = count - known_mine_count

        if neighbors and adjusted_count >= 0 and adjusted_count <= len(neighbors):
            new_sentence = Sentence(neighbors, adjusted_count)

            if new_sentence not in self.knowledge:
                self.knowledge.append(new_sentence)

        # 4) mark any additional cells as safe or as mines
        # 5) add any new sentences to the AI's knowledge base
        changed = True
        while changed:
            changed = False
            changed = self.update_knowledge() or changed
            changed = self.infer_new_sentences() or changed



    def update_knowledge(self):
        """
        通过标记已知的地雷和安全的格子更新知识
        """

        changed = False

        # 复制知识库的副本
        knowledge_copy = self.knowledge.copy()
        for sentence in knowledge_copy:
            # 移除空句子
            if len(sentence.cells) == 0:
                self.knowledge.remove(sentence)
                continue
            # 检查已知的地雷
            known_mines = sentence.known_mines().copy()
            for mine_cell in known_mines:
                if mine_cell not in self.mines:
                    self.mark_mine(mine_cell)
                    changed = True
            # 检查已知的安全格子
            known_safes = sentence.known_safes().copy()
            for safe_cell in known_safes:
                if safe_cell not in self.safes:
                    self.mark_safe(safe_cell)
                    changed = True
        return changed

    def infer_new_sentences(self):
        """
        根据现存的知识库推断新的句子
        """

        changed = False
        knowledge_copy = self.knowledge.copy()

        for sentence1 in knowledge_copy:
            for sentence2 in knowledge_copy:
                if sentence1 == sentence2:
                    continue
                if sentence1.cells.issubset(sentence2.cells):
                    new_cells = sentence2.cells - sentence1.cells
                    new_count = sentence2.count - sentence1.count
                    new_sentence = Sentence(new_cells, new_count)

                    # 添加新句子
                    if new_sentence not in self.knowledge:
                        self.knowledge.append(new_sentence)
                        changed = True

        return changed

    def make_safe_move(self):
        """
        Returns a safe cell to choose on the Minesweeper board.
        The move must be known to be safe, and not already a move
        that has been made.

        This function may use the knowledge in self.mines, self.safes
        and self.moves_made, but should not modify any of those values.
        """
        safe_moves = self.safes - self.moves_made - self.mines

        if safe_moves:
            return random.choice(list(safe_moves))
        return None

    def make_random_move(self):
        """
        Returns a move to make on the Minesweeper board.
        Should choose randomly among cells that:
            1) have not already been chosen, and
            2) are not known to be mines
        """
        # 获取所有可能的格子
        all_cells = set()
        for i in range(self.height):
            for j in range(self.width):
                all_cells.add((i,j))

        possible_moves = all_cells - self.moves_made - self.mines

        if possible_moves:
            return random.choice(list(possible_moves))
        return None