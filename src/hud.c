#include "fractol.h"

void	draw_hud_background(t_hud *hud, t_image *img)
{
	unsigned char	rect_colors[3];
	int				pixel;
	int				c;
	int				i;
	int				j;

	rect_colors[0] = hud->bg_color & 0xFF;
	rect_colors[1] = (hud->bg_color >> 8) & 0xFF;
	rect_colors[2] = (hud->bg_color >> 16) & 0xFF;
	j = 9;
	while (++j < hud->height + 10 && j < img->height)
	{
		i = 9;
		while (++i < hud->width + 10 && i < img->width)
		{
			pixel = j * img->size_line + i * (img->bpp / 8);
			c = -1;
			while (++c < 3)
			{
				img->addr[pixel + c] = (unsigned char)(hud->bg_opacity * \
				rect_colors[c] + (1.0 - hud->bg_opacity) * \
				(unsigned char)img->addr[pixel + c]);
			}
		}
	}
}

static void	render_hud_line(t_fractol *data, int y, char *label, char **tmp)
{
	const char	*str;

	if (!tmp)
	{
		mlx_string_put(data->mlx, data->window, data->hud.x, y, \
		data->hud.txt_color, label);
		return ;
	}
	if (!*tmp)
		str = "N/A";
	else
		str = *tmp;
	ft_strlcpy(data->hud.buffer, label, BUFFER_SIZE);
	ft_strlcat(data->hud.buffer, str, BUFFER_SIZE);
	mlx_string_put(data->mlx, data->window, data->hud.x, y, \
	data->hud.txt_color, data->hud.buffer);
	if (*tmp != data->color.theme_name)
		free(*tmp);
}

static int	render_hud_head(t_fractol *data, t_fractal *f, t_hud *hud)
{
	char	*tmp;
	int		y;

	y = hud->start_y;
	render_hud_line(data, y, \
	".-------------------------------------------.", NULL);
	render_hud_line(data, y += 20, \
	"|                                           |", NULL);
	render_hud_line(data, y += 20, \
	"|              H U D   M E N U              |", NULL);
	render_hud_line(data, y += 20, \
	"|                                           |", NULL);
	render_hud_line(data, y += 20, \
	"'-------------------------------------------'", NULL);
	mlx_string_put(data->mlx, data->window, hud->x + 100, y += hud->line_gap, \
	hud->txt_color, "--- INFOS ---");
	tmp = data->color.theme_name;
	render_hud_line(data, y += hud->line_gap + 10, "  - Color Theme: ", &tmp);
	tmp = ft_itoa(f->iteration_max);
	render_hud_line(data, y += hud->line_gap, "  - Iterations: ", &tmp);
	tmp = ft_ftoa(f->view.scale, 3);
	render_hud_line(data, y += hud->line_gap, "  - Scale: ", &tmp);
	return (y);
}

static int	render_hud_body(t_fractol *data, t_fractal *f, t_hud *hud)
{
	char	*tmp;

	int (y) = render_hud_head(data, f, hud);
	if (f->type == JULIA)
	{
		render_hud_line(data, y += hud->line_gap, "  - Julia constants:", NULL);
		tmp = ft_ftoa(f->c.r, 3);
		render_hud_line(data, y += hud->line_gap, "    cr: ", &tmp);
		tmp = ft_ftoa(f->c.i, 3);
		render_hud_line(data, y += hud->line_gap, "    ci: ", &tmp);
	}
	mlx_string_put(data->mlx, data->window, hud->x + 90, \
	y += hud->line_gap + 10, hud->txt_color, "--- CONTROLS ---");
	if (f->type == JULIA)
	{
		render_hud_line(data, y += hud->line_gap + 10, \
		"  - Update Julia Constants:", NULL);
		render_hud_line(data, y += hud->line_gap, \
		"    SPACE Key to activate Selection Mode", NULL);
		render_hud_line(data, y += hud->line_gap, \
		"    + Click to Set New Coordinates", NULL);
	}
	render_hud_line(data, y += hud->line_gap, \
	"  - Move: W/A/S/D or Arrow Keys", NULL);
	return (y);
}

void	render_hud(t_fractol *data, t_fractal *f, t_hud *hud)
{
	int (y) = render_hud_body(data, f, hud);
	render_hud_line(data, y += hud->line_gap, "  - Zoom: Scroll Wheel", NULL);
	render_hud_line(data, y += hud->line_gap, \
	"  - Increase iterations: + Key", NULL);
	render_hud_line(data, y += hud->line_gap, "  - Reset view: R Key", NULL);
	render_hud_line(data, y += hud->line_gap, \
	"  - Screenshot: Ctrl + Shift + 4 Keys", NULL);
	if (data->color.theme == PSYCHEDELIC)
		render_hud_line(data, y += hud->line_gap, \
		"  - Shift Color inside Theme: Shift Key", NULL);
	if (f->type != SIERPINSKI
		|| (f->type == SIERPINSKI && data->color.theme == CUSTOM))
		render_hud_line(data, y += hud->line_gap, \
		"  - Change Color Theme: C Key", NULL);
	render_hud_line(data, y += hud->line_gap, "  - Toggle HUD: H Key", NULL);
	render_hud_line(data, y += hud->line_gap, \
	"  - Exit: ESC Key or Windowcross", NULL);
	if (f->type == MANDELBROT && data->select_mode)
	{
		mlx_string_put(data->mlx, data->window, hud->x + 70, \
		y += hud->line_gap + 10, hud->txt_color, "--- SELECTION MODE ---");
		render_hud_line(data, y += hud->line_gap + 10, \
		"  - Click to Set New Julia Constants", NULL);
	}
}
