#include "minishell.h"
#include <readline/readline.h>

void	ft_free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

static t_commands	*arg_to_lst(int ac, char *av[])
{
	int		i;
	int		x;
	char	*str;

	i = 1;
	x = 0;
	str = NULL;
	while (i < ac)
	{
		str = ft_strjoin(str, av[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	return (ft_split(str, '"'));
}

int	main(int ac, char *av[])
{
    t_commands *com_list;

	while (1)
	{

		com_list->com = arg_to_lst();
	}
}