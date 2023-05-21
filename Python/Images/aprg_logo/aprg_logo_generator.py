import numpy as np
import math
import random
import skimage.io


def get_rgb_on_circle(scale, rgb_start, rgb_end):
    return round(scale*(rgb_end - rgb_start) + rgb_start)


def get_scale_on_circle(scale_to_change, noise_scale):
    return 0.8*scale_to_change*noise_scale + 0.2*random.random()*(1-noise_scale)


def get_rgb_on_text(color, noise_scale):
    return color*(0.5 + 0.4*noise_scale + 0.1*(1-noise_scale)*random.random())


def draw_pixel_at_circle(image, x, y, top_left, bottom_right, color_start, color_end):
    scale_x = (x-top_left[0])/(bottom_right[0]-top_left[0])
    scale_y = (y-top_left[1])/(bottom_right[1]-top_left[1])
    scale_hyp = math.dist(top_left, (x, y)) / math.dist(top_left, bottom_right)

    image[y, x] = [
        get_rgb_on_circle(get_scale_on_circle(scale_x, scale_x),
                          color_start[0], color_end[0]),
        get_rgb_on_circle(get_scale_on_circle(scale_y, scale_x),
                          color_start[1], color_end[1]),
        get_rgb_on_circle(get_scale_on_circle(
            scale_hyp, scale_x), color_start[2], color_end[2]),
        255]


def draw_A(image, x, y, x_size):
    scale_x = x/x_size

    y_above1 = (14920387*x**3)/14491651970796 - (13359929155*x**2)/4830550656932 + \
        (3859517180479*x)/7245825985398 + 11887532885881/13270743563
    y_above2 = -(16347715*x**3)/853840460088 + (4101465239*x**2)/106730057511 - \
        (18746791928537*x)/853840460088 + 772744266377663/213460115022
    y_below1 = (757969*x**3)/1081410201144 - (341375914*x**2) / \
        135176275143 + (1704921335*x)/2868462072 + 1758514572850/2145655161
    y_below2 = (167663*x**3)/17310267072 - (179742863*x**2) / \
        5770089024 + (298684357607*x)/8655133536 - 416010121655/34345768
    if (y < y_above1 and y > y_below1) or (y < y_above2 and y > y_below2):
        color = get_rgb_on_text(255, scale_x)
        image[y, x] = [color, color, color, 255]


def draw_circle(image):
    y_size, x_size, _ = np.shape(image)
    color_above_1, color_above_2 = (76, 129, 134), (210, 223, 225)
    color_below_1, color_below_2 = (127, 85, 131), (15, 10, 16)
    radius = x_size*0.4
    multiplier_sin_function = radius/4
    multiplier_to_angle = math.pi/radius
    midpoint = ((x_size+1)//2, (y_size+1)//2)
    top_left = (midpoint[0]-radius, midpoint[1]-radius)
    bottom_right = (midpoint[0]+radius, midpoint[1]+radius)
    for x in range(x_size):
        for y in range(y_size):
            distance = math.dist(midpoint, (x, y))
            if distance < radius:
                if y < midpoint[1] - math.sin((x - top_left[0])*multiplier_to_angle)*multiplier_sin_function:
                    draw_pixel_at_circle(
                        image, x, y, top_left, bottom_right, color_above_1, color_above_2)
                else:
                    draw_pixel_at_circle(
                        image, x, y, top_left, bottom_right, color_below_1, color_below_2)
                draw_A(image, x, y, x_size)


def generate_aprg_logo():
    image = skimage.io.imread('sample.png')

    draw_circle(image)

    skimage.io.imsave('aprg_logo.png', image)


if __name__ == '__main__':
    generate_aprg_logo()
    print('done!')
