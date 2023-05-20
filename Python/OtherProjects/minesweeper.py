import enum
import random


Cell_Hidden_Space = -1
Cell_Hidden_Bomb = -2
Cell_Revealed_Bomb = -3


grid_length = 10
grid_width = 5
grid_size = grid_length * grid_width
number_of_bombs = int(grid_size*0.1)


def get_index(coordinate):
    return int(coordinate[1]*grid_length + coordinate[0])


def is_hidden(cell):
    return Cell_Hidden_Bomb == cell or Cell_Hidden_Space == cell


def is_revealed(cell):
    return Cell_Revealed_Bomb == cell or cell >= 0


def is_a_bomb(cell):
    return Cell_Hidden_Bomb == cell or Cell_Revealed_Bomb == cell


def is_within_grid(coordinate):
    return coordinate[0] >= 0 and coordinate[0] < grid_length and coordinate[1] >= 0 and coordinate[1] < grid_width


def are_all_spaces_revealed(grid):
    return all([Cell_Hidden_Space != cell for cell in grid])


def create_empty_grid():
    return [Cell_Hidden_Space] * grid_size


def create_grid_with_bombs():
    grid = create_empty_grid()
    for _ in range(number_of_bombs):
        bomb_index = random.randrange(0, len(grid))
        grid[bomb_index] = Cell_Hidden_Bomb
    return grid


def get_cell_display_with_hidden(cell):
    if Cell_Hidden_Space == cell:
        return '?'
    elif Cell_Hidden_Bomb == cell:
        return '?'
    elif Cell_Revealed_Bomb == cell:
        return '*'
    elif 0 == cell:
        return ' '
    else:
        return str(cell)


def get_cell_display_with_reveal(cell):
    if Cell_Hidden_Space == cell:
        return ' '
    elif Cell_Hidden_Bomb == cell:
        return '*'
    elif Cell_Revealed_Bomb == cell:
        return '*'
    elif 0 == cell:
        return ' '
    else:
        return str(cell)


def print_grid(grid, display_function):
    horizontal_line = '-' * (grid_length*4+1)
    board_display = [display_function(cell) for cell in grid]
    print(horizontal_line)
    for y in range(grid_width):
        grid_string = ' | '.join(board_display[y*grid_length: (y+1)*grid_length])
        print(f'| {grid_string} |')
        print(horizontal_line)


def get_adjacent_coordinates(coordinate):
    return [
        (coordinate[0]-1, coordinate[1]-1),
        (coordinate[0], coordinate[1]-1),
        (coordinate[0]+1, coordinate[1]-1),
        (coordinate[0]-1, coordinate[1]),
        (coordinate[0]+1, coordinate[1]),
        (coordinate[0]-1, coordinate[1]+1),
        (coordinate[0], coordinate[1]+1),
        (coordinate[0]+1, coordinate[1]+1),
    ]


def get_number_of_adjacent_bombs(grid, coordinate):
    result = 0
    for adjacent in get_adjacent_coordinates(coordinate):
        if is_within_grid(adjacent):
            if is_a_bomb(grid[get_index(adjacent)]):
                result += 1
    return result


def sweep(grid, coordinate):
    if is_within_grid(coordinate):
        index = get_index(coordinate)
        cell = grid[index]
        if is_hidden(cell):
            if is_a_bomb(cell):
                grid[index] = Cell_Revealed_Bomb
            else:
                adjacent_bombs = get_number_of_adjacent_bombs(grid, coordinate)
                grid[index] = adjacent_bombs
                if adjacent_bombs == 0:
                    for adjacent in get_adjacent_coordinates(coordinate):
                        sweep(grid, adjacent)


def get_player_input(grid):
    isValid = False
    while not isValid:
        try:
            inputs_string = input('Input a coordinate to sweep: ')
            inputs = [int(input_string) for input_string in inputs_string.split(',')]
            if len(inputs) == 2:
                if not is_within_grid(inputs):
                    raise ValueError
                elif is_revealed(grid[get_index(inputs)]):
                    raise ValueError
                else:
                    isValid = True
            else:
                raise ValueError
        except ValueError:
            print('Dont waste my time.')
    return tuple(inputs)


def play_mine_sweeper():
    grid = create_grid_with_bombs()
    while True:
        print_grid(grid, get_cell_display_with_hidden)
        coordinate = get_player_input(grid)
        index = get_index(coordinate)
        if is_a_bomb(grid[index]):
            print('The bomb exploded on you. Game Over!')
            print_grid(grid, get_cell_display_with_reveal)
            break
        else:
            sweep(grid, coordinate)
            if are_all_spaces_revealed(grid):
                print('You win!')
                print_grid(grid, get_cell_display_with_reveal)
                break

if __name__ == '__main__':  # good practice :)
    play_mine_sweeper()
