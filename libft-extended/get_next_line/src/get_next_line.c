#include "get_next_line.h"

static char	*ft_strjoin_with_len(const char *s1, const char *s2,
	size_t s1_len, size_t s2_len)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

static bool	fill_remainder(int fd, char **rem, char *buffer, size_t *rem_len)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*rem, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (false);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin_with_len(*rem, buffer, *rem_len, bytes_read);
		free(*rem);
		*rem = tmp;
		if (!*rem)
			return (false);
		*rem_len += bytes_read;
	}
	return (true);
}

static char	*extract_line(char **rem)
{
	char	*line;
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*rem)[len] && (*rem)[len] != '\n')
		len++;
	if ((*rem)[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, *rem, len);
	line[len] = '\0';
	tmp = ft_strdup((*rem) + len);
	free(*rem);
	*rem = tmp;
	if (!*rem || !**rem)
		(free(*rem), *rem = NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*buffer;
	size_t		rem_len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!rem)
		rem = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!rem || !buffer)
		return (free(buffer), free(rem), rem = NULL, NULL);
	rem_len = ft_strlen(rem);
	if (fill_remainder(fd, &rem, buffer, &rem_len) == false)
		return (free(buffer), free(rem), rem = NULL, NULL);
	free(buffer);
	if (!rem || !*rem)
		return (free(rem), rem = NULL, NULL);
	return (extract_line(&rem));
}
