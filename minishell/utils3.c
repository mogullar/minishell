/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:34:22 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 15:37:11 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**from_env(t_data *data)
{
	char	**path;
	char	*str;

	str = isenv(data, "PATH");
	path = ft_split(str, ':');
	if (str)
		free(str);
	return (path);
}

void	free_for_path(char **path, char *tmp, int i, char *str)
{
	free(path[i]);
	free(tmp);
	free(str);
}

char	*put_slash(char **str, char *cmnd, char **path, int i)
{
	char	*tmp;

	*str = ft_strjoin(path[i], "/");
	tmp = *str;
	*str = ft_strjoin(tmp, cmnd);
	return (tmp);
}

char	*find_path(t_data *data, char *cmnd)
{
	char	*tmp;
	char	*str;
	char	**path;
	int		i;

	i = -1;
	path = from_env(data);
	if (path)
	{
		while (path[++i])
		{
			tmp = put_slash(&str, cmnd, path, i);
			if (!access(str, F_OK))
			{
				free(tmp);
				free_arrays(&path, i - 1);
				return (str);
			}
			free_for_path(path, tmp, i, str);
		}
		free_arrays(&path, i - 1);
		return (0);
	}
	return (0);
}

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			return (1);
		i++;
	}
	return (0);
}
