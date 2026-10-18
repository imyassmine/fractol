#include "libft.h"

static size_t	count_digits(long n)
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

char	*ft_itoa(int n)
{
	long	nb;
	size_t	neg;
	size_t	len;
	char	*str;

	nb = n;
	neg = (n < 0);
	if (neg)
		nb = -nb;
	len = count_digits(nb) + neg;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > neg)
	{
		len--;
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
