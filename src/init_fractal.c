#include "fractol.h"

int	is_int(const char *value)
{
	const char	*ptr;

	long (nbr) = 0;
	int (sign) = 1;
	ptr = value;
	if (!value || !*value)
		return (0);
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	if (!ft_isdigit(*ptr))
		return (0);
	while (*ptr)
	{
		if (!ft_isdigit(*ptr))
			return (0);
		nbr = nbr * 10 + (*ptr - '0');
		if ((sign == 1 && nbr > INT_MAX) || (sign == -1 && (-nbr) < INT_MIN))
			return (0);
		ptr++;
	}
	return (1);
}

static void	choose_fractal_type(char **argv, t_fractal_type *type, t_fractol *d)
{
	int		i;

	i = -1;
	while (argv[1][++i])
		argv[1][i] = ft_tolower(argv[1][i]);
	if (!ft_strncmp(argv[1], "julia", 5) && !argv[1][5])
		*type = JULIA;
	else if (!ft_strncmp(argv[1], "mandelbrot", 10) && !argv[1][10])
		*type = MANDELBROT;
	else if (!ft_strncmp(argv[1], "sierpinski", 10) && !argv[1][10])
		*type = SIERPINSKI;
	else
		error("Invalid fractal type provided", 2, d);
}

void	viewport_init(t_view *view, t_fractal *f, t_image *img)
{
	view->scale = 4.3;
	view->scale_x = view->scale / img->width;
	view->scale_y = view->scale_x;
	view->center_x = -0.42;
	if (f->type == MANDELBROT)
	{
		view->scale = 5.0;
		view->scale_x = view->scale / img->width;
		view->scale_y = view->scale_x;
		view->center_x = -1.0;
	}
	if (f->type == SIERPINSKI)
	{
		view->center_x = 0.0;
		view->center_y = 1.0;
	}
}

void	fractal_init(int argc, char **argv, t_fractal *f, t_fractol *data)
{
	choose_fractal_type(argv, &f->type, data);
	viewport_init(&f->view, f, &data->img);
	f->iteration_max = 50;
	if (f->type == SIERPINSKI)
		f->iteration_max = 4;
	if (argc >= 4 && is_int(argv[3]))
		f->iteration_max = clamp(ft_atoi(argv[3]), 5, 1000);
	else if (argc >= 4 && !is_int(argv[3]))
		error("Invalid iteration value provided", 2, data);
	if (f->type == JULIA)
	{
		f->c.r = -0.8;
		f->c.i = 0.16;
		if (argc == 6)
		{
			f->c.r = ft_atof(argv[4]);
			f->c.i = ft_atof(argv[5]);
			if (isnan(f->c.r) || isnan(f->c.i))
				error("Invalid Julia constants provided", 2, data);
			if (f->c.r > 2.0 || f->c.r < -2.0)
				f->c.r = clamp(ft_atof(argv[4]), -2, 2);
			if (f->c.i > 2.0 || f->c.i < -2.0)
				f->c.i = clamp(ft_atof(argv[5]), -2, 2);
		}
	}
}
