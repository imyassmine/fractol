#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	sub_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (len < sub_len)
		sub_len = len;
	str = malloc(sizeof(char) * (sub_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, sub_len + 1);
	return (str);
}
