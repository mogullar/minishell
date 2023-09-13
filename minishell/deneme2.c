#include "minishell.h"
#include <readline/readline.h>

int	ft_count(const char *str, char c)
{
	size_t	num_of_words;
	size_t	i;
	int flag;

	flag = 0;
	if (!str[0])
		return (0);
	num_of_words = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{	
		if (str[i] == '"' || flag == 1)
        {
            while (str[i] && str[i] != '"')
                i++;
            if (str[i] == '"')
                flag == 0;
        }
		else if (str[i] == c)
		{
			num_of_words++;
			while (str[i] && str[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (str[i - 1] != c)
		num_of_words++;
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