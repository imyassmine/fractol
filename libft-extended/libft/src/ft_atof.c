#include "libft.h"
#include <math.h>

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static double	parse_integer(const char **str, size_t *digits)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
		(*digits)++;
	}
	return (result);
}

static double	parse_fraction(const char **str, size_t *digits)
{
	double	result;
	double	divisor;

	if (**str != '.')
		return (0.0);
	(*str)++;
	result = 0.0;
	divisor = 1.0;
	while (ft_isdigit(**str))
	{
		result = result * 10.0 + (**str - '0');
		divisor *= 10.0;
		(*str)++;
		(*digits)++;
	}
	return (result / divisor);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	size_t	digits;

	if (!str)
		return (NAN);
	digits = 0;
	sign = parse_sign(&str);
	result = parse_integer(&str, &digits);
	result += parse_fraction(&str, &digits);
	if (*str || !digits)
		return (NAN);
	return (sign * result);
}
