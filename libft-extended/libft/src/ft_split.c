#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static void	free_tab(char **tab, size_t i)
{
	while (i--)
		free(tab[i]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	word_count;
	size_t	i;
	size_t	word_len;

	word_count = count_words(s, c);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	tab[word_count] = NULL;
	i = -1;
	while (++i < word_count)
	{
		while (*s == c)
			s++;
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		tab[i] = ft_substr(s, 0, word_len);
		if (!tab[i])
			return (free_tab(tab, i), NULL);
		s += word_len;
	}
	return (tab);
}
