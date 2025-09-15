"""
Tic Tac Toe Player
"""
import copy
import math

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_count = sum(row.count(X) for row in board)
    o_count = sum(row.count(O) for row in board)

    if x_count == o_count:
        return X
    else:
        return O

def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    possible_actions = set()
    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                possible_actions.add((i,j))
    return possible_actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    i,j = action
    if i < 0 or i > 2 or j < 0 or j > 2:
        raise Exception("Invalid action: out of bounds")

    if board[i][j] != EMPTY:
        raise Exception("Invalid action")

    new_board = copy.deepcopy(board)
    current_player = player(board)
    new_board[i][j] = current_player
    return new_board

def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    # 检查行
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] and board[i][0] != EMPTY:
            return board[i][0]

    # 检查列
    for j in range(3):
        if board[0][j] == board[1][j] == board[2][j] and board[0][j] != EMPTY:
            return board[0][j]

    # 检查对角线
    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != EMPTY:
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] and board[0][2] != EMPTY:
        return board[0][2]

    return None
def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    # 有赢家，游戏结束
    if winner(board) is not None:
        return True
    # 没有赢家且棋盘未满，游戏继续
    for row in board:
        if EMPTY in row:
            return False

    # 没有赢家且棋盘已满，平局
    return True

def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    win = winner(board)
    if win == X:
        return 1
    elif win == O:
        return -1
    else:
        return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None

    current_player = player(board)

    if current_player == X:
        value,action = max_value(board)
        return action
    else:
        value,action = min_value(board)
        return action

def max_value(board):
    if terminal(board):
        return utility(board), None
    v = float('-inf')
    best_action = None

    for action in actions(board):
        new_board = result(board,action)
        min_val,_ = min_value(new_board)

        if min_val > v:
            v = min_val
            best_action = action

        if v ==1:
            break
    return v,best_action

def min_value(board):
    if terminal(board):
        return utility(board),None
    v = float('inf')
    best_action = None
    for action in actions(board):
        new_board = result(board,action)
        max_val,_ = max_value(new_board)

        if max_val<v:
            v = max_val
            best_action = action

        if v == -1:
            break
    return v,best_action