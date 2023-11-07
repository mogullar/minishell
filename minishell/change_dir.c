/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:43:27 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/07 14:13:53 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_content(t_data *data, int j, int len, char **content)
{
	char	*for_dollar;
	char	*tmp;
	char	*last_content;

	last_content = NULL;
	if (len != 0)
	{
		for_dollar = NULL;
		for_dollar = ft_substr(data->tokens->contents->content, j, len);
		tmp = *content;
		last_content = ft_strjoin2(tmp, for_dollar);
	}
	else
		last_content = *content;
	return (last_content);
}

void	go_to_home(char **path, t_data *data)
{
	*path = isenv(data, "HOME");
	if (chdir(*path) != 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	data->exit_status = 1;
	if (*path)
		free(*path);
}

void	if_error_cd(t_data *data, char *path)
{
	data->exit_status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (ft_strchr(path, '.'))
		ft_putstr_fd(": Not a directory\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

int	cd(t_data *data, t_parser *a)
{
	char	*path;

	data->tokens = data->tokens->next;
	path = NULL;
	if (a->commands[1] == NULL)
		go_to_home(&path, data);
	else
	{
		path = ft_strdup(a->commands[1]);
		if (chdir(path) != 0 && path != NULL)
			if_error_cd(data, path);
		else
			data->exit_status = 0;
		free(path);
	}
	return (data->exit_status);
}

int	pwd(t_data *data)
{
	printf("%s\n", getcwd(data->path, 4096));
	return (data->exit_status);
}
