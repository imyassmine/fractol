#include "ft_printf.h"

int	putchar_count(int fd, char c, int *count)
{
	*count += write(fd, &c, 1);
	return (*count);
}

int	putstr_count(int fd, char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
		putchar_count(fd, *s++, count);
	return (*count);
}

int	putnbr_count(int fd, int n, int *count)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		putchar_count(fd, '-', count);
		nb = -nb;
	}
	if (nb / 10)
		putnbr_count(fd, nb / 10, count);
	putchar_count(fd, nb % 10 + '0', count);
	return (*count);
}

int	putunbr_count(int fd, unsigned int n, int *count)
{
	if (n / 10)
		putunbr_count(fd, n / 10, count);
	putchar_count(fd, n % 10 + '0', count);
	return (*count);
}

int	puthex_count(int fd, unsigned long n, int *count, bool uppercase)
{
	char	*base;

	base = "0123456789abcdef";
	if (uppercase == true)
		base = "0123456789ABCDEF";
	if (n / 16)
		puthex_count(fd, n / 16, count, uppercase);
	putchar_count(fd, base[n % 16], count);
	return (*count);
}
