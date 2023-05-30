import numpy as np
import math
import random
import skimage.io


def get_color_for_normal_background(image, x, y, top_left_color, top_right_color, bottom_left_color, bottom_right_color):
    y_size, x_size, _ = np.shape(image)
    x_scale, y_scale = x/x_size, y/y_size
    top_left = math.dist((0, 0), (x, y))
    top_right = math.dist((x_size-1, 0), (x, y))
    bottom_left = math.dist((0, y_size-1), (x, y))
    bottom_right = math.dist((x_size-1, y_size-1), (x, y))
    hyp_scale = top_left/math.dist((0, 0), (x_size-1, y_size-1))
    without_top_left = top_right*bottom_right*bottom_left
    without_top_right = top_left*bottom_right*bottom_left
    without_bottom_left = top_left*top_right*bottom_right
    without_bottom_right = top_left*top_right*bottom_left
    numerators = [0, 0, 0]
    for i in range(3):
        numerators[i] = (without_top_left*top_left_color[i]
                         + without_top_right*top_right_color[i]
                         + without_bottom_left*bottom_left_color[i]
                         + without_bottom_right*bottom_right_color[i])
    denominator = (without_top_left + without_top_right +
                   without_bottom_left + without_bottom_right)
    result = [n/denominator for n in numerators]

    for i in range(3):
        result[i] = (16 + 0.8*result[i] + 0.3*x_scale*top_left_color[i]
                     + 0.3*y_scale*bottom_left_color[i] + 0.3*random.random()*(1-hyp_scale)*top_right_color[i])
    return result


def get_rgb_on_circle(scale, rgb_start, rgb_end):
    return round(scale*(rgb_end - rgb_start) + rgb_start)


def get_scale_on_circle(scale_to_change, noise_scale):
    return 0.8*scale_to_change*noise_scale + 0.2*random.random()*(1-noise_scale)


def get_rgb_on_text(original_rgb, alpha_scale, x_scale):
    return 127 + 128*0.9*(0.8*x_scale + 0.2*(1-x_scale)*random.random()) + 0.1*alpha_scale*original_rgb


def draw_pixel_for_title(image, x, y, top_left, bottom_right, color_start, color_end):
    x_scale = (x-top_left[0])/(bottom_right[0]-top_left[0])
    y_scale = (y-top_left[1])/(bottom_right[1]-top_left[1])
    scale_hyp = math.dist(top_left, (x, y)) / math.dist(top_left, bottom_right)

    image[y, x] = [
        get_rgb_on_circle(get_scale_on_circle(x_scale, x_scale),
                          color_start[0], color_end[0]),
        get_rgb_on_circle(get_scale_on_circle(y_scale, x_scale),
                          color_start[1], color_end[1]),
        get_rgb_on_circle(get_scale_on_circle(
            scale_hyp, x_scale), color_start[2], color_end[2]),
        255]


def fill_normal_background(image):
    y_size, x_size, _ = np.shape(image)
    top_left_color, top_right_color, bottom_left_color, bottom_right_color = (
        76, 129, 134), (210, 223, 225), (127, 85, 131), (15, 10, 16)
    for x in range(x_size):
        for y in range(y_size):
            color = get_color_for_normal_background(image, x, y, top_left_color,
                                                    top_right_color, bottom_left_color, bottom_right_color)
            image[y, x] = [round(color[0]), round(
                color[1]), round(color[2]), 255]


def fill_title_background(image):
    y_size, x_size, _ = np.shape(image)
    color_top_left, color_top_right, color_bottom_left, color_bottom_right = (
        76, 129, 134), (210, 223, 225), (127, 85, 131), (15, 10, 16)
    wave_radius = x_size/100
    multiplier_sin_function = wave_radius/4
    multiplier_to_angle = math.pi/wave_radius
    top_left = (0, 0)
    bottom_right = (x_size, y_size)
    for x in range(x_size):
        y_wave_position = (0.8 + 0.1 * (x/x_size)) * y_size
        for y in range(y_size):
            sin_wave = math.sin(x * multiplier_to_angle) * \
                multiplier_sin_function
            wave_y = y_wave_position - sin_wave

            if y < wave_y:
                draw_pixel_for_title(
                    image, x, y, top_left, bottom_right, color_top_left, color_top_right)
            else:
                draw_pixel_for_title(
                    image, x, y, top_left, bottom_right, color_bottom_left, color_bottom_right)


def generate_normal_background():
    image = skimage.io.imread('sample.png')
    fill_normal_background(image)
    skimage.io.imsave('normal_background.png', image)


def generate_title_background():
    image = skimage.io.imread('sample.png')
    fill_title_background(image)
    skimage.io.imsave('title_background.png', image)


if __name__ == '__main__':
    generate_normal_background()
    # generate_title_background()
    print('done!')
