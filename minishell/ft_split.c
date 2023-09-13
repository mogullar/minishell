#include "minishell.h"
#include <readline/readline.h>

static inline
char	**ft_deallocate(char **result, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
		free(result[j++]);
	free(result);
	return (NULL);
}

static inline
char	*ft_sub(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (len - start) + 1);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (j < (len - start))
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static inline
char	*ft_get_word(const char *str, char c, int word, t_commands *com)
{
	char			*result;

	while (str[com->i] && str[com->i] == c)
		com->i++;
	com->j = com->i;
	while (str[com->i])
	{
        if (str[com->i] == '"')
        {
			com->i++;
            while (str[com->i] && str[com->i] != '"')
                com->i++;
			com->j++;
            return (ft_sub(str, com->j, com->i++));
        }
        else if (str[com->i] == '\'')
        {
			com->i++;
            while (str[com->i] && str[com->i] != '\'')
                com->i++;
			com->j++;
            return (ft_sub(str, com->j, com->i));
        }
		while (str[com->i] == c)
		{
			com->i++;
		}
		while (str[com->i] && str[com->i] != c)
			com->i++;
		if (str[com->i - 1] != c || str[com->i - 2] != c)
			return (ft_sub(str, com->j, com->i));
	}
	return (result);
}

int	ft_count(const char *str, char c)
{
	size_t	num_of_words;
	size_t	i;
	int hold;

	if (!str[0])
		return (0);
	num_of_words = 0;
	i = 0;
	hold = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{	
		if (str[i] == 34 && str[i])
		{
			num_of_words++;
            i++;
			while (str[i] && str[i] != 34)
				i++;
			i++;
			continue ;
		}
		else if (str[i] == 39 && str[i])
		{
			num_of_words++;
            i++;
			while (str[i] && str[i] != 39)
				i++;
			i++;
			continue ;
		}
		while (str[i] == c)
			i++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i - 1] != c || str[i - 2] != c)
			num_of_words++;
		i++;
	}
	return (num_of_words);
}

char	**ft_split(const char *s, char c, t_commands *com)
{
	char	**result;
	int		num_of_words;
	size_t	i;

	if (!s)
		return (NULL);
	num_of_words = ft_count(s, c);
	result = (char **)malloc(sizeof(char *) * (num_of_words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (num_of_words--)
	{
		result[i] = ft_get_word(s, c, num_of_words, com);
		if (!result[i])
			return (ft_deallocate(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	main()
{
	t_commands *com;
    char *str;

	com->i = 0;
	com->j = 0;
	while (1)
	{
        str = readline("minishell$ ");
		
        char **str1 = ft_split(str, ' ', com);
		int i = 0;
		while (str1[i] != NULL)
		{
			printf("%s\n", str1[i]);
			i++;
		}
		i = 0;
		while (str1[i] != NULL)
		{
			free(str1[i]);
			i++;
		}
		com->i = 0;
		com->j = 0;
	} 
}