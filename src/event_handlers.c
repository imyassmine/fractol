#include "fractol.h"

int	mouse_press(int button, int x, int y, t_fractol *data)
{
	if (data->hud.visible && x <= data->hud.x + data->hud.width)
		return (0);
	if (data->select_mode && data->f.type == MANDELBROT && button == LEFT_CLICK)
		return (change_julia_cst(&data->f, data, x, y));
	data->f.mouse = map_position_to_complex(x, y, &data->img, &data->f.view);
	if (button == SCROLL_UP)
	{
		data->f.view.scale /= ZOOM_FACTOR;
		data->f.iteration_max += SCALE_ITERATION;
	}
	else if (button == SCROLL_DOWN)
	{
		data->f.view.scale *= ZOOM_FACTOR;
		data->f.iteration_max -= SCALE_ITERATION;
	}
	data->f.iteration_max = clamp(data->f.iteration_max, 4, 1000);
	data->f.view.scale_x = data->f.view.scale / data->img.width;
	data->f.view.scale_y = data->f.view.scale_x;
	data->f.view.center_x = data->f.mouse.r - (x - data->img.width / 2.0) \
	* data->f.view.scale_x;
	data->f.view.center_y = data->f.mouse.i - (data->img.height / 2.0 - y) \
	* data->f.view.scale_y;
	render_fractal(data, &data->f);
	return (0);
}

int	key_press(int keycode, t_fractol *data)
{
	if (keycode == ESC)
		clean_exit(0, data);
	else if (keycode == SPACE)
		activate_selection_mode(data, &data->f);
	else if (keycode == SHIFT)
		data->color.shift += 1;
	else if (keycode == PLUS)
		data->f.iteration_max += SCALE_ITERATION;
	else if (keycode == R)
		reset_view(&data->f, &data->img);
	else if (keycode == W || keycode == UP)
		data->f.view.center_y += (MOVE_STEP / data->f.view.scale);
	else if (keycode == S || keycode == DOWN)
		data->f.view.center_y -= (MOVE_STEP / data->f.view.scale);
	else if (keycode == A || keycode == LEFT)
		data->f.view.center_x -= (MOVE_STEP / data->f.view.scale);
	else if (keycode == D || keycode == RIGHT)
		data->f.view.center_x += (MOVE_STEP / data->f.view.scale);
	else if (keycode == C)
		change_color_theme(&data->color, &data->f);
	else if (keycode == H)
		data->hud.visible = !data->hud.visible;
	clamp(data->f.iteration_max, 4, 1000);
	render_fractal(data, &data->f);
	return (0);
}

// int	key_release(int keycode, t_fractol *data)
// {
// 	if (keycode == SPACE)
// 		data->space_key = 0;
// 	return (0);
// }

int	close_window(t_fractol *data)
{
	clean_exit(0, data);
	return (0);
}
