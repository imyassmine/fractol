#include "fractol.h"

void	reset_view(t_fractal *f, t_image *img)
{
	ft_memset(&f->view, 0, sizeof(t_view));
	viewport_init(&f->view, f, img);
}

void	activate_selection_mode(t_fractol *data, t_fractal *f)
{
	f->type = MANDELBROT;
	data->select_mode = 1;
	reset_view(&data->f, &data->img);
	render_fractal(data, f);
}

int	change_julia_cst(t_fractal *f, t_fractol *data, int x, int y)
{
	f->c = map_position_to_complex(x, y, &data->img, &f->view);
	data->f.type = JULIA;
	data->select_mode = 0;
	reset_view(f, &data->img);
	render_fractal(data, f);
	return (0);
}

void	change_color_theme(t_color *color, t_fractal *f)
{
	int	i;

	i = -1;
	if (color->theme == CUSTOM && f->type == SIERPINSKI)
		color->theme = PSYCHEDELIC;
	else if (f->type != SIERPINSKI)
	{
		if (color->theme == CUSTOM || color->theme == OCEAN)
			color->theme = PSYCHEDELIC;
		else
		{
			while (++i < OCEAN)
			{
				if ((int)color->theme == i)
				{
					color->theme += 1;
					break ;
				}
			}
		}
		if (color->theme == SMOOTH && f->type == MANDELBROT)
			color->theme = FIRE;
	}
	color->shift = 0;
	set_color_theme_name(&color->theme, &color->theme_name);
}
