#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* ================================ INCLUDES ================================ */

# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>

/* ================================ DEFINES ================================= */

# define NULL_PTR "(nil)"

/* =========================== FUNCTION PROTOTYPES ========================== */

/* --- Main functions --- */

int	ft_printf(const char *str, ...);
int	ft_dprintf(int fd, const char *str, ...);

/* --- Helper Functions --- */

int	putchar_count(int fd, char c, int *count);
int	putstr_count(int fd, char *s, int *count);
int	putnbr_count(int fd, int n, int *count);
int	putunbr_count(int fd, unsigned int n, int *count);
int	puthex_count(int fd, unsigned long n, int *count, bool uppercase);

#endif
