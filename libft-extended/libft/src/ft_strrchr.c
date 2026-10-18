#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	s += s_len;
	s_len++;
	while (s_len--)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
