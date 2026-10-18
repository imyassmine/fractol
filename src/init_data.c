#include "fractol.h"

static void	choose_color_theme(char **argv, t_color_theme *theme, t_fractol *d)
{
	int	i;

	i = -1;
	while (argv[2][++i])
		argv[2][i] = ft_tolower(argv[2][i]);
	if (!ft_strncmp(argv[2], "psychedelic", 11) && !argv[2][11])
		*theme = PSYCHEDELIC;
	else if (!ft_strncmp(argv[2], "monochrome", 10) && !argv[2][10])
		*theme = MONOCHROME;
	else if (!ft_strncmp(argv[2], "gradient", 8) && !argv[2][8])
		*theme = GRADIENT;
	else if (!ft_strncmp(argv[2], "smooth", 6) && !argv[2][6])
		*theme = SMOOTH;
	else if (!ft_strncmp(argv[2], "fire", 4) && !argv[2][4])
		*theme = FIRE;
	else if (!ft_strncmp(argv[2], "ocean", 5) && !argv[2][5])
		*theme = OCEAN;
	else
		*theme = CUSTOM;
	if (d->f.type == SIERPINSKI && *theme != PSYCHEDELIC && *theme != CUSTOM)
		error("Invalid color theme for Sierpinski fractal", 2, d);
	if (d->f.type == MANDELBROT && *theme == SMOOTH)
		error("Invalid color theme for Mandelbrot fractal", 2, d);
}

void	set_color_theme_name(t_color_theme *theme, char **theme_name)
{
	if (*theme == PSYCHEDELIC)
		*theme_name = "Default - Psychedelic";
	else if (*theme == MONOCHROME)
		*theme_name = "Monochrome";
	else if (*theme == GRADIENT)
		*theme_name = "Gradient";
	else if (*theme == SMOOTH)
		*theme_name = "Smooth";
	else if (*theme == FIRE)
		*theme_name = "Fire";
	else if (*theme == OCEAN)
		*theme_name = "Ocean";
	else if (*theme == CUSTOM)
		*theme_name = "Custom";
}

static void	color_init(int argc, char **argv, t_color *color, t_fractol *d)
{
	char	**custom;

	color->theme = PSYCHEDELIC;
	color->theme_name = "Default - Psychedelic";
	if (argc >= 3)
	{
		choose_color_theme(argv, &color->theme, d);
		set_color_theme_name(&color->theme, &color->theme_name);
		if (color->theme == CUSTOM)
		{
			custom = ft_split(argv[2], ' ');
			if (!custom)
				error("Failed to split color arguments", EXIT_FAILURE, d);
			if (!custom[0] || !custom[1] || !custom[2] || !is_int(custom[0])
				|| !is_int(custom[1]) || !is_int(custom[2]))
			{
				free_split(custom);
				error("Invalid or missing RGB values for custom theme", 2, d);
			}
			color->base_r = clamp(ft_atoi(custom[0]), 0, 255);
			color->base_g = clamp(ft_atoi(custom[1]), 0, 255);
			color->base_b = clamp(ft_atoi(custom[2]), 0, 255);
			free_split(custom);
		}
	}
}

static void	hud_init(t_hud *hud)
{
	hud->visible = 1;
	hud->x = 20;
	hud->start_y = 20;
	hud->txt_color = 0xFFFFFF;
	hud->line_gap = 25;
	hud->width = 290;
	hud->height = 780;
	hud->bg_color = 0x202020;
	hud->bg_opacity = 0.8;
}

void	data_init(int argc, char **argv, t_fractol *data, t_image *img)
{
	char	*title;

	ft_memset(data, 0, sizeof(t_fractol));
	data->mlx = mlx_init();
	if (!data->mlx)
		error("Failed to initialize MLX library", EXIT_FAILURE, NULL);
	img->width = 1500;
	img->height = 800;
	fractal_init(argc, argv, &data->f, data);
	color_init(argc, argv, &data->color, data);
	hud_init(&data->hud);
	if (data->f.type == JULIA)
		title = "Fract-ol - Julia set";
	else if (data->f.type == MANDELBROT)
		title = "Fract-ol - Mandelbrot set";
	else if (data->f.type == SIERPINSKI)
		title = "Fract-ol - Sierpinski carpet";
	data->window = mlx_new_window(data->mlx, img->width, img->height, title);
	if (!data->window)
		error("Failed to create window", EXIT_FAILURE, data);
	img->ptr = mlx_new_image(data->mlx, img->width, img->height);
	if (!img->ptr)
		error("Failed to create image", EXIT_FAILURE, data);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, \
	&img->endian);
}
