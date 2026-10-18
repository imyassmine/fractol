#include "fractol.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	free_split(char **s)
{
	int	i;

	if (!s || !*s)
		return ;
	i = -1;
	while (s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

void	clean_exit(int status, t_fractol *data)
{
	if (data->window)
		(mlx_destroy_window(data->mlx, data->window));
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(status);
}

void	print_help(void)
{
	ft_printf("\nUsage: ./fractol [Fractal Type] [Color Theme] [Iterations] \
[Julia cr] [Julia ci]\n\n");
	ft_printf("Parameters:\n\n");
	ft_printf("  Mandatory:\n");
	ft_printf("    Fractal Types:\n      - Julia\n      - Mandelbrot\n\
      - Sierpinski\n\n");
	ft_printf("  Optional:\n");
	ft_printf("    Color Themes:\n      - Psychedelic (Default)\n\
      - Monochrome\n      - Gradient\n      - Smooth\n      - Fire\n");
	ft_printf("      - Ocean\n      - Custom RGB: Provide 3 integers between 0 \
and 255 (e.g., \"255 0 0\" for red)\n\n");
	ft_printf("    Iterations:\n");
	ft_printf("      - An integer between 5 and 1000\n");
	ft_printf("      - Examples:\n");
	ft_printf("          * Julia: 50\n          * Sierpinski: 5\n\n");
	ft_printf("    Julia Set Constants:\n");
	ft_printf("      - cr: Real part of the constant\n");
	ft_printf("      - ci: Imaginary part of the constant\n");
	ft_printf("      - Some beautiful Julia sets examples: -0.8 0.16, -0.75 0.13, \
-0.4 0.6, 0 1, 0.285 0.01, 0.355 0.355, 0.3555 -0.337, 0.37 0.1 ..\n\n");
	ft_printf("Examples:\n  ./fractol Julia Smooth 500 0.285 0.01\n  ./fractol \
Mandelbrot gradient 50\n  ./fractol Sierpinski Psychedelic 5\n\n");
	ft_printf("Note:\n  - Color Themes 'Monochrome', 'Gradient', 'Fire', and \
'Ocean' are available only for Julia and Mandelbrot sets.\n  \
- Color Theme 'Smooth' is only available for Julia Set.\n");
}

void	error(const char *error_msg, int status, t_fractol *data)
{
	ft_putendl_fd(error_msg, 2);
	if (status == 2)
		print_help();
	if (data)
		clean_exit(status, data);
	else
		exit(status);
}
