import enum
import random


class Move_State(enum.Enum):
    Player_Move = 1
    Computer_Move = 2


class Cell(enum.Enum):
    Empty = 0
    X = 1
    O = 2


class Calculated_Move:
    def __init__(self, index, score):
        self.index = index
        self.score = score


display_empty = '  '
display_x = 'XX'
display_o = 'OO'
board_side_size = 3
board_size = board_side_size * board_side_size


def get_cell_display(cell):
    if Cell.Empty == cell:
        return display_empty
    elif Cell.X == cell:
        return display_x
    elif Cell.O == cell:
        return display_o


def get_index(coordinate):    return int(coordinate[1]*board_side_size + coordinate[0])


def get_coordinate(index):
    return (int(index % board_side_size), int(index/board_side_size))


def get_available_indexes(board):
    return [i for i, cell in enumerate(board) if cell == Cell.Empty]


def toggle_cell(current_cell):
    return Cell.O if current_cell == Cell.X else Cell.X


def create_empty_board():
    return [Cell.Empty] * board_size


def put_move_board(board, index, current_cell):
    board[index] = current_cell


def print_board(board):
    table_length = board_side_size * 3 + 1
    table_horizontal_line = '-' * table_length
    space = '   '
    board_display = [get_cell_display(cell) for cell in board]
    row_break = table_horizontal_line + space + table_horizontal_line
    print(row_break)
    for y in range(board_side_size):
        guide_string = '|'.join(['{:2d}'.format(index) for index in range(y*board_side_size, (y+1)*board_side_size)])
        board_string = '|'.join(board_display[y*board_side_size: (y+1)*board_side_size])
        print(f'|{guide_string}|{space}|{board_string}|')
        print(row_break)


def is_a_row_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    is_winning = True
    for x in range(board_side_size):
        if current_cell != board[get_index((x, coordinate[1]))]:
            is_winning = False
            break
    return is_winning


def is_a_column_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    is_winning = True
    for y in range(board_side_size):
        if current_cell != board[get_index((coordinate[0], y))]:
            is_winning = False
            break
    return is_winning


def is_a_diagonal_positive_slope_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    x, y = coordinate
    distance_to_corner = min(x, y)    x -= distance_to_corner
    y -= distance_to_corner
    if (x, y) == (0, 0):
        is_winning = True
        while x < board_side_size and y < board_side_size:
            if current_cell != board[get_index((x, y))]:
                is_winning = False
                break
            x += 1            y += 1
    else:
        is_winning = False
    return is_winning


def is_a_diagonal_negative_slope_win(board, index, current_cell):
    coordinate = get_coordinate(index)
    last_index = board_side_size-1
    x, y = coordinate    distance_to_corner = min(x, last_index-y)
    x -= distance_to_corner
    y += distance_to_corner
    if (x, y) == (0, last_index):
        is_winning = True
        while x < board_side_size and y >= 0:
            if current_cell != board[get_index((x, y))]:
                is_winning = False
                break
            x += 1            y -= 1
    else:
        is_winning = False
    return is_winning


def is_a_win(board, index, current_cell):
    return (is_a_row_win(board, index, current_cell)
            or is_a_column_win(board, index, current_cell)
            or is_a_diagonal_positive_slope_win(board, index, current_cell)
            or is_a_diagonal_negative_slope_win(board, index, current_cell))


def is_a_draw(board):
    return len(get_available_indexes(board)) == 0


def is_first_move(board):
    return board == create_empty_board()


def get_player_input(board):
    isValid = False
    while not isValid:
        try:
            index = int(input('Your move, input index: '))
            if index < 0 or index >= board_size:
                raise ValueError
            elif board[index] != Cell.Empty:
                raise ValueError
            else:
                isValid = True
        except ValueError:
            print('Dont waste my time.')
    return index


# scores is defined as number_of_empty+1 (positive if winning, negative if losing)
# check minimax algorithm for clarification (https://en.wikipedia.org/wiki/Minimax)
def get_best_calculated_move(board, cell, depth):
    if depth == 0:
        return Calculated_Move(get_random_index(board), 0)  # just put a random move
    else:
        calculated_moves = []
        available_indexes = get_available_indexes(board)
        for index_to_analyze in available_indexes:
            board_to_analyze = board.copy()
            put_move_board(board_to_analyze, index_to_analyze, cell)
            number_of_empty_cells = len(get_available_indexes(board_to_analyze))
            if is_a_win(board_to_analyze, index_to_analyze, cell):  # win
                return Calculated_Move(index_to_analyze, number_of_empty_cells+1)  # quick exit if there is a win
                # calculated_moves.append(Calculated_Move(index_to_analyze, number_of_empty_cells+1))
            elif number_of_empty_cells == 0:  # draw
                calculated_moves.append(Calculated_Move(index_to_analyze, 0))
            else:
                opponent_move = get_best_calculated_move(board_to_analyze, toggle_cell(cell), depth-1)
                calculated_moves.append(Calculated_Move(index_to_analyze, -1*opponent_move.score))
        best_move = max(calculated_moves, key=lambda calculated_move: calculated_move.score)
        return best_move


def get_best_index(board, cell):
    if is_first_move(board):
        return get_random_index(board)
    else:
        # -1 depth means unlimited depth
        return get_best_calculated_move(board, cell, -1).index


def get_random_index(board):
    return random.choice(get_available_indexes(board))


def play_tic_tac_toe():
    current_cell = Cell.O
    state = Move_State.Computer_Move
    main_board = create_empty_board()
    print('Game start')
    print_board(main_board)
    while True:
        if state == Move_State.Player_Move:
            print('Player to move')
            index = get_player_input(main_board)
            put_move_board(main_board, index, current_cell)
        elif state == Move_State.Computer_Move:
            print('Computer to move')
            index = get_best_index(main_board, current_cell)  # smart AI
            # index = get_random_index(main_board)  # stupid AI
            print('The computer moved at index:', index)
            put_move_board(main_board, index, current_cell)

        print_board(main_board)

        if is_a_win(main_board, index, current_cell):
            if state == Move_State.Player_Move:
                print('You win')
            elif state == Move_State.Computer_Move:
                print('You lose')
            break
        elif is_a_draw(main_board):
            print('Draw')
            break
        else:
            state = Move_State.Player_Move if state == Move_State.Computer_Move else Move_State.Computer_Move
            current_cell = toggle_cell(current_cell)

if __name__ == '__main__':  # good practice :)
    play_tic_tac_toe()