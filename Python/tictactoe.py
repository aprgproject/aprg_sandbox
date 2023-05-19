import enum
import random


class State(enum.Enum):
    Player_Move = 1
    Computer_Move = 2


empty_symbol = "  "
x_symbol = "XX"
o_symbol = "OO"
board_side_size = 5
board_size = board_side_size * board_side_size
board = [empty_symbol] * board_size


def get_index(coordinate):
    return int(coordinate[1]*board_side_size + coordinate[0])


def get_coordinate(index):
    return (int(index % board_side_size), int(index/board_side_size))


def get_available_indexes():
    return [i for i, cell in enumerate(board) if cell == empty_symbol]


def put_move_board(index, current_symbol):
    board[index] = current_symbol


def print_board():
    table_length = board_side_size * 3 + 1
    table_horizontal_line = "-" * table_length
    space = "   "
    row_break = table_horizontal_line + space + table_horizontal_line
    print(row_break)
    for y in range(board_side_size):
        guide_display = "|".join(["{:2d}".format(index) for index in range(y*board_side_size, (y+1)*board_side_size)])
        board_display = "|".join(board[y*board_side_size: (y+1)*board_side_size])
        print(f'|{guide_display}|{space}|{board_display}|')
        print(row_break)


def is_a_row_win(index, current_symbol):
    coordinate = get_coordinate(index)
    is_winning = True
    for x in range(board_side_size):
        if current_symbol != board[get_index((x, coordinate[1]))]:
            is_winning = False
            break
    return is_winning


def is_a_column_win(index, current_symbol):
    coordinate = get_coordinate(index)
    is_winning = True
    for y in range(board_side_size):
        if current_symbol != board[get_index((coordinate[0], y))]:
            is_winning = False
            break
    return is_winning


def is_a_diagonal_positive_slope_win(index, current_symbol):
    coordinate = get_coordinate(index)
    x, y = coordinate
    distance_to_corner = min(x, y)
    x -= distance_to_corner
    y -= distance_to_corner
    if (x, y) == (0, 0):
        is_winning = True
        while x < board_side_size and y < board_side_size:
            if current_symbol != board[get_index((x, y))]:
                is_winning = False
                break
            x += 1
            y += 1
    else:
        is_winning = False
    return is_winning


def is_a_diagonal_negative_slope_win(index, current_symbol):
    coordinate = get_coordinate(index)
    last_index = board_side_size-1
    x, y = coordinate
    distance_to_corner = min(x, last_index-y)
    x -= distance_to_corner
    y += distance_to_corner
    if (x, y) == (0, last_index):
        is_winning = True
        while x < board_side_size and y >= 0:
            if current_symbol != board[get_index((x, y))]:
                is_winning = False
                break
            x += 1
            y -= 1
    else:
        is_winning = False
    return is_winning


def is_a_win(index, current_symbol):
    return (is_a_row_win(index, current_symbol) or is_a_column_win(index, current_symbol)
           or is_a_diagonal_positive_slope_win(index, current_symbol) or is_a_diagonal_negative_slope_win(index, current_symbol))


def get_player_input():
    isValid = False
    while not isValid:
        try:
            index = int(input("Your move, input index: "))
            if index < 0 or index >= board_size:
                raise ValueError
            elif board[index] != empty_symbol:
                raise ValueError
            else:
                isValid = True
        except ValueError:
            print("Dont waste my time.")
    return index


def get_computer_input():
    return random.choice(get_available_indexes())


def perform_player_move(current_symbol):
    index = get_player_input()
    print("index", index)
    put_move_board(index, current_symbol)


index_guide_board = "012345678"
current_symbol = x_symbol
state = State.Player_Move
print("Game start")
print_board()
while True:
    if state == State.Player_Move:
        print("Player to move")
        index = get_player_input()
        put_move_board(index, current_symbol)
    elif state == State.Computer_Move:
        print("Computer to move")
        index = get_computer_input()
        print("The computer moved at index:", index)
        put_move_board(index, current_symbol)

    print_board()

    if is_a_win(index, current_symbol):
        if state == State.Player_Move:
            print("You win")
        elif state == State.Computer_Move:
            print("You lose")
        break
    elif len(get_available_indexes()) == 0:
        print("Draw")
        break
    else:
        state = State.Player_Move if state == State.Computer_Move else State.Computer_Move
        current_symbol = o_symbol if current_symbol == x_symbol else x_symbol
