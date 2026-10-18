#include "ft_printf.h"

static void	handle_ptr(int fd, void *ptr, int *count)
{
	if (!ptr)
		putstr_count(fd, NULL_PTR, count);
	else
	{
		putstr_count(fd, "0x", count);
		puthex_count(fd, (unsigned long)ptr, count, false);
	}
}

static void	dispatch(int fd, char c, va_list ap, int *count)
{
	if (c == 'c')
		putchar_count(fd, (char)va_arg(ap, int), count);
	else if (c == 's')
		putstr_count(fd, va_arg(ap, char *), count);
	else if (c == 'p')
		handle_ptr(fd, va_arg(ap, void *), count);
	else if (c == 'd' || c == 'i')
		putnbr_count(fd, va_arg(ap, int), count);
	else if (c == 'u')
		putunbr_count(fd, va_arg(ap, unsigned int), count);
	else if (c == 'x')
		puthex_count(fd, va_arg(ap, unsigned int), count, false);
	else if (c == 'X')
		puthex_count(fd, va_arg(ap, unsigned int), count, true);
	else if (c == '%')
		putchar_count(fd, '%', count);
}

static int	print_format(int fd, const char *str, va_list ap)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '%' && str[1])
		{
			str++;
			dispatch(fd, *str, ap, &count);
		}
		else if (*str != '%')
			putchar_count(fd, *str, &count);
		str++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	if (!str)
		return (0);
	va_start(ap, str);
	count = print_format(1, str, ap);
	va_end(ap);
	return (count);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	ap;
	int		count;

	if (!str)
		return (0);
	va_start(ap, str);
	count = print_format(fd, str, ap);
	va_end(ap);
	return (count);
}
