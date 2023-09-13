#include "minishell.h"
#include <readline/readline.h>

int	ft_count(const char *str, char c)
{
	size_t	num_of_words;
	size_t	i;

	if (!str[0])
		return (0);
	num_of_words = 0;
	i = 0;
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

int	main()
{
    char *str;
	while (1)
	{
        str = readline("minishell: ");
		
        if ((char)str == 'e')
            exit(0);
        printf("%d", ft_count(str, ' '));
	} 
}