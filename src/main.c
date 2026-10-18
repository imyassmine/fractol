#include "fractol.h"

int	main(int ac, char **argv)
{
	t_fractol	data;

	if (ac < 2)
		error("Missing arguments", 2, NULL);
	if (ac == 2 && !ft_strncmp(argv[1], "--help", 6) && !argv[1][6])
	{
		print_help();
		exit(0);
	}
	data_init(ac, argv, &data, &data.img);
	if ((ac > 6 && data.f.type == JULIA) || (ac > 4 && data.f.type != JULIA))
		error("Too many arguments passed", 2, &data);
	render_fractal(&data, &data.f);
	mlx_hook(data.window, KEY_PRESS, KEYPRESSMASK, key_press, &data);
	mlx_hook(data.window, BUTTON_PRESS, BUTTONPRESSMASK, mouse_press, &data);
	mlx_hook(data.window, DESTROY_NOTIFY, STRUCNOTIFYMASK, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
