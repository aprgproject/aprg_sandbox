
import copy
import numpy as np
import math
import randomimport skimage.io


def get_rgb_on_circle(scale, rgb_start, rgb_end):    return round(scale*(rgb_end - rgb_start) + rgb_start)


def get_scale_on_circle(scale_to_change, noise_scale):
    return 0.8*scale_to_change*noise_scale + 0.2*random.random()*(1-noise_scale)


def get_rgb_on_text(original_rgb, alpha_scale, scale_x):
    return 127 + 128*0.9*(0.8*scale_x + 0.2*(1-scale_x)*random.random()) + 0.1*alpha_scale*original_rgb


def draw_pixel_at_circle(image, x, y, top_left, bottom_right, color_start, color_end):    scale_x = (x-top_left[0])/(bottom_right[0]-top_left[0])
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


def are_colors_too_far(pixel1, pixel2):
    difference_limit = 48
    return (abs(int(pixel1[0]) - int(pixel2[0])) > difference_limit
            or abs(int(pixel1[1]) - int(pixel2[1])) > difference_limit
            or abs(int(pixel1[2]) - int(pixel2[2])) > difference_limit)


def get_darker(color, scale):
    darkest = 0.3
    remaining_scale = 1 - darkest
    scale = darkest + remaining_scale*scale
    return [color[0]*scale, color[1]*scale, color[2]*scale, color[3]]


def add_to_edge_point(image, x, y, edge_point_to_color):
    y_size, x_size, _ = np.shape(image)
    radius = 3
    for ix in range(-radius, radius+1):
        for iy in range(-radius, radius+1):
            distance = math.dist((0, 0), (ix, iy))
            if distance <= radius:
                coordinate = (y+iy, x+ix)
                if coordinate[0] >= 0 and coordinate[0] < x_size and coordinate[1] >= 0 and coordinate[1] < y_size:
                    new_color = get_darker(
                        image[coordinate], 0.6+0.4*(distance/radius))
                    if coordinate in edge_point_to_color:
                        old_color = edge_point_to_color[coordinate]
                        if (new_color[0] < old_color[0] or new_color[1] < old_color[1] or new_color[2] < old_color[2]):
                            edge_point_to_color[coordinate] = new_color
                    else:
                        edge_point_to_color[coordinate] = new_color


def draw_pixel_at_A(image, x, y, original_pixel, x_mid, x_size):
    color_scale = x/x_size
    alpha_scale = 1 - (abs(x-x_mid)/x_mid)
    image[y, x] = [get_rgb_on_text(original_pixel[0], alpha_scale, color_scale), get_rgb_on_text(
        original_pixel[1], alpha_scale, color_scale), get_rgb_on_text(original_pixel[2], alpha_scale, color_scale), 255*alpha_scale]


def draw_circle(image):
    y_size, x_size, _ = np.shape(image)
    color_top_left, color_top_right, color_bottom_left, color_bottom_right = (
        76, 129, 134), (210, 223, 225), (127, 85, 131), (15, 10, 16)
    radius = x_size*0.4
    multiplier_sin_function = radius/4
    multiplier_to_angle = math.pi/radius    midpoint = ((x_size+1)//2, (y_size+1)//2)
    top_left = (midpoint[0]-radius, midpoint[1]-radius)
    bottom_right = (midpoint[0]+radius, midpoint[1]+radius)
    for x in range(x_size):
        for y in range(y_size):
            distance = math.dist(midpoint, (x, y))
            if distance < radius:
                wave_y = midpoint[1] - math.sin((x - top_left[0])
                                                * multiplier_to_angle)*multiplier_sin_function
                if y < wave_y:
                    draw_pixel_at_circle(
                        image, x, y, top_left, bottom_right, color_top_left, color_top_right)
                else:
                    draw_pixel_at_circle(
                        image, x, y, top_left, bottom_right, color_bottom_left, color_bottom_right)


def draw_A(image):
    y_size, x_size, _ = np.shape(image)
    x_mid = (x_size+1)//2
    y_s_multiplier = y_size/1280
    edge_point1 = None
    for x in range(x_size):
        for y in range(y_size):
            # check notes for more info about the polynomials
            x_s = x*1280/x_size
            top_left = (7.641401711352939E-08*x_s**3 + -0.001469426845249755*x_s **
                        2 + 0.03767793712239261*x_s + 907.881474319954) * y_s_multiplier
            bottom_left = (-5.658652163930147E-07*x_s**3 + -0.0004084999223478625 *
                           x_s**2 + -0.4834368000620288*x_s + 1018.7052478722) * y_s_multiplier
            top_right = (6.311007900381323E-06*x_s**3 + -0.02249420409310314*x_s **
                         2 + 27.20634107875812*x_s + -10127.11612409357) * y_s_multiplier
            bottom_right = (9.12861766646765E-06*x_s**3 + -0.02921189077082613 *
                            x_s**2 + 31.41800966282249*x_s + -10257.89060798793) * y_s_multiplier
            top_middle = (-2.752092040586441E-06*x_s**3 + 0.004841462611769976 *
                          x_s**2 + -2.473153786213333*x_s + 1012.876600748878) * y_s_multiplier
            bottom_middle = (-1.594617762447137E-06*x_s**3 + 0.003361228023313456 *
                             x_s**2 + -1.797687047234969*x_s + 921.5631013947169) * y_s_multiplier
            original = copy.deepcopy(image[y, x])
            if y > top_left and y < bottom_left and y > top_right:
                draw_pixel_at_A(image, x, y, original, x_mid, x_size)
            if y > top_right and y < bottom_right and y > top_left:
                draw_pixel_at_A(image, x, y, original, x_mid, x_size)
            if y > top_middle and y < bottom_middle and y > top_right:
                draw_pixel_at_A(image, x, y, original, x_mid, x_size)


def darken_edges(image):
    y_size, x_size, _ = np.shape(image)
    edge_point_to_color = {}
    for x in range(2, x_size-2):
        for y in range(2, y_size-2):
            if (are_colors_too_far(image[y, x], image[y, x-1])
                or are_colors_too_far(image[y, x], image[y, x+1])
                or are_colors_too_far(image[y, x], image[y-1, x])
                    or are_colors_too_far(image[y, x], image[y+1, x])):
                add_to_edge_point(image, x, y, edge_point_to_color)

    print(len(edge_point_to_color))
    for edge_point, color in edge_point_to_color.items():
        image[edge_point[0], edge_point[1]] = color


def generate_aprg_logo():
    image = skimage.io.imread('sample.png')

    draw_circle(image)
    draw_A(image)
    darken_edges(image)

    skimage.io.imsave('aprg_logo.png', image)

if __name__ == '__main__':
    generate_aprg_logo()
    print('done!')