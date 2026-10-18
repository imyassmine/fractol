#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_c;
	char	*src_c;

	dest_c = (char *)dest;
	src_c = (char *)src;
	if (dest_c > src_c)
	{
		while (n-- > 0)
			dest_c[n] = src_c[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
