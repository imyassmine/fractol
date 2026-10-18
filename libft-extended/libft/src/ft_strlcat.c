#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size < dst_len)
		return (size + src_len);
	if (size > dst_len)
	{
		dst += dst_len;
		while (--size > dst_len && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (dst_len + src_len);
}
