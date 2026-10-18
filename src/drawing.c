#include "fractol.h"

static void	set_vibrant_color_theme(t_fractal *f, t_color *color)
{
	color->t = (double)f->depth / f->iteration_max;
	if (color->theme == PSYCHEDELIC)
	{
		color->r = (int)(127.5 * (1 + sin(3.0 * M_PI * color->t \
		+ color->shift)));
		color->g = (int)(127.5 * (1 + sin(3.0 * M_PI * color->t + 2 * M_PI / 3 \
		+ color->shift)));
		color->b = (int)(127.5 * (1 + sin(3.0 * M_PI * color->t + 4 * M_PI / 3 \
		+ color->shift)));
	}
	else if (color->theme == GRADIENT)
	{
		color->r = (int)(255 * pow(color->t, 1.0));
		color->g = (int)(255 * pow(color->t, 0.5));
		color->b = (int)(255 * pow(color->t, 0.3));
	}
	else if (color->theme == SMOOTH)
	{
		color->t = f->depth + 1 - (log(log(f->z.r * f->z.r + f->z.i * f->z.i) \
		/ 2.0) / log(2));
		color->r = (int)(127.5 * (1 + sin(0.1 * color->t + 0)));
		color->g = (int)(127.5 * (1 + sin(0.1 * color->t + 2 * M_PI / 3)));
		color->b = (int)(127.5 * (1 + sin(0.1 * color->t + 4 * M_PI / 3)));
	}
}

static void	set_simple_color_theme(t_fractal *f, t_color *color)
{
	color->t = (double)f->depth / f->iteration_max;
	if (color->theme == MONOCHROME)
	{
		color->r = (int)(255 * color->t);
		color->g = (int)(255 * color->t);
		color->b = (int)(255 * color->t);
	}
	else if (color->theme == FIRE)
	{
		color->r = (int)(255 * color->t);
		color->g = (int)(128 * pow(color->t, 0.5));
		color->b = (int)(0);
	}
	else if (color->theme == OCEAN)
	{
		color->r = (int)(0);
		color->g = (int)(128 * pow(color->t, 0.5));
		color->b = (int)(255 * color->t);
	}
	else if (color->theme == CUSTOM)
	{
		color->r = (int)(color->base_r * color->t);
		color->g = (int)(color->base_g * color->t);
		color->b = (int)(color->base_b * color->t);
	}
}

static void	set_color_pixel(t_color *color, t_fractol *data, int x, int y)
{
	int		pixel;

	set_vibrant_color_theme(&data->f, color);
	set_simple_color_theme(&data->f, color);
	pixel = (y * data->img.size_line) + (x * (data->img.bpp / 8));
	data->img.addr[pixel + 0] = clamp(color->b, 0, 255);
	data->img.addr[pixel + 1] = clamp(color->g, 0, 255);
	data->img.addr[pixel + 2] = clamp(color->r, 0, 255);
}

inline void	render_fractal(t_fractol *data, t_fractal *f)
{
	register int	x;
	register int	y;

	y = -1;
	while (++y < data->img.height)
	{
		x = -1;
		while (++x < data->img.width)
		{
			if (f->type == JULIA)
				f->depth = calculate_julia(f, &data->img, x, y);
			else if (f->type == MANDELBROT)
				f->depth = calculate_mandelbrot(f, &data->img, x, y);
			else if (f->type == SIERPINSKI)
				f->depth = calculate_sierpinski(f, x, y);
			set_color_pixel(&data->color, data, x, y);
		}
	}
	if (data->hud.visible)
		draw_hud_background(&data->hud, &data->img);
	mlx_put_image_to_window(data->mlx, data->window, data->img.ptr, 0, 0);
	if (data->hud.visible)
		render_hud(data, f, &data->hud);
}
