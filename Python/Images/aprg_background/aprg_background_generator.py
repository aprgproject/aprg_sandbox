import numpy as np
import math
import random
import skimage.io


def get_rgb_value(x, y, x_size, y_size, top_left_color, top_right_color, bottom_left_color, bottom_right_color):

    distance_to_top_left = math.dist((0, 0), (x, y))
    distance_to_top_right = math.dist((x_size-1, 0), (x, y))
    distance_to_bottom_left = math.dist((0, y_size-1), (x, y))
    distance_to_bottom_right = math.dist((x_size-1, y_size-1), (x, y))
    distance_sum = distance_to_top_left + distance_to_top_right + \
        distance_to_bottom_left+distance_to_bottom_right
    (1 - distance_to_top_left/distance_sum) * top_left_color + 
    unfinished
    return round(
        0.5*(noise_scale*scale_x*(rgb_x_end - rgb_x_start) + rgb_x_start) +
        0.5*(noise_scale*scale_y*(rgb_y_end - rgb_y_start) + rgb_y_start))


def fill(image):
    y_size, x_size, _ = np.shape(image)
    print(x_size, y_size, np.shape(image))
    top_left_color, top_right_color, bottom_left_color, bottom_right_color = (
        76, 129, 134), (210, 223, 225), (127, 85, 131), (15, 10, 16)
    for x in range(x_size):
        for y in range(y_size):
            scale_x = x/x_size
            scale_y = y/y_size
            scale_hyp = / hypotenuse

            #print(x, y)
            #print(image[y, x])
            image[y, x] = [
                get_rgb_value(scale_x, scale_y, scale_hyp,
                              color_above_1[0], color_above_2[0], color_below_1[0], color_below_2[0]),
                get_rgb_value(scale_x, scale_y, scale_hyp,
                              color_above_1[1], color_above_2[1], color_below_1[1], color_below_2[1]),
                get_rgb_value(scale_x, scale_y, scale_hyp,
                              color_above_1[2], color_above_2[2], color_below_1[2], color_below_2[2]),
                255]


def generate_aprg_background():
    image = skimage.io.imread('sample.png')
    fill(image)
    skimage.io.imsave('aprg_background.png', image)


if __name__ == '__main__':
    generate_aprg_background()
    print('done!')
