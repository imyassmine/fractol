#include "libft.h"
#include <math.h>

static size_t	count_digits(unsigned long long n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_digits(char *str, unsigned long long n, size_t len)
{
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
}

static unsigned long long	split_number(double n, int precision,
	unsigned long long *frac_part)
{
	unsigned long long	int_part;
	unsigned long long	scale;

	scale = 1;
	while (precision-- > 0)
		scale *= 10;
	int_part = (unsigned long long)n;
	*frac_part = (unsigned long long)((n - int_part) * scale + 0.5);
	if (*frac_part >= scale)
	{
		int_part++;
		*frac_part -= scale;
	}
	return (int_part);
}

static char	*format_number(unsigned long long int_part,
	unsigned long long frac_part, int precision, size_t neg)
{
	size_t	int_len;
	size_t	total;
	char	*str;

	int_len = count_digits(int_part);
	total = neg + int_len + (precision > 0) + precision;
	str = malloc(sizeof(char) * (total + 1));
	if (!str)
		return (NULL);
	if (neg)
		str[0] = '-';
	fill_digits(str + neg, int_part, int_len);
	if (precision > 0)
	{
		str[neg + int_len] = '.';
		fill_digits(str + neg + int_len + 1, frac_part, precision);
	}
	str[total] = '\0';
	return (str);
}

char	*ft_ftoa(double n, int precision)
{
	unsigned long long	int_part;
	unsigned long long	frac_part;
	size_t				neg;

	if (isnan(n) || isinf(n) || n >= 1e18 || n <= -1e18)
		return (NULL);
	neg = (n < 0);
	if (neg)
		n = -n;
	if (precision < 0)
		precision = 0;
	if (precision > 15)
		precision = 15;
	int_part = split_number(n, precision, &frac_part);
	return (format_number(int_part, frac_part, precision, neg));
}
