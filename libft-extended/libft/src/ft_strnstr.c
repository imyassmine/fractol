#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	if (!len)
		return (NULL);
	little_len = ft_strlen(little);
	while (*big && len-- >= little_len)
	{
		if (!ft_strncmp(big, little, little_len))
			return ((char *)big);
		big++;
	}
	return (NULL);
}
