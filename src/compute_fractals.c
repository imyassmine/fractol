#include "fractol.h"

t_complex	map_position_to_complex(int x, int y, t_image *img, t_view *view)
{
	t_complex	c;

	c.r = (x - img->width / 2.0) * view->scale_x + view->center_x;
	c.i = (img->height / 2.0 - y) * view->scale_y + view->center_y;
	return (c);
}

static void	iterate_fractal(t_fractal *f)
{
	double	tmp_zr;

	f->depth = 0;
	while (f->depth < f->iteration_max)
	{
		tmp_zr = f->z.r * f->z.r - f->z.i * f->z.i + f->c.r;
		f->z.i = 2.0 * f->z.r * f->z.i + f->c.i;
		f->z.r = tmp_zr;
		if (f->z.r * f->z.r + f->z.i * f->z.i > 4.0)
			break ;
		f->depth++;
	}
}

int	calculate_julia(t_fractal *f, t_image *img, int x, int y)
{
	f->z = map_position_to_complex(x, y, img, &f->view);
	iterate_fractal(f);
	return (f->depth);
}

int	calculate_mandelbrot(t_fractal *f, t_image *img, int x, int y)
{
	f->z.r = 0.0;
	f->z.i = 0.0;
	f->c = map_position_to_complex(x, y, img, &f->view);
	iterate_fractal(f);
	return (f->depth);
}

int	calculate_sierpinski(t_fractal *f, int x, int y)
{
	f->depth = 0;
	while (f->depth < f->iteration_max)
	{
		if (x % 3 == 1 && y % 3 == 1)
			break ;
		x /= 3;
		y /= 3;
		f->depth++;
	}
	return (f->depth);
}
