#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_com
{
	char **com;
	int i;
	int j;
}					t_commands;

int	ft_count(const char *str, char c);
char	**ft_split(const char *s, char c, t_commands *com);

#endif