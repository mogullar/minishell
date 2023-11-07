/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:35:13 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 19:56:15 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, t_parser *a, char *cmnd)
{
	if (!a->commands[0])
		data->exit_status = 0;
	else if (execve(a->commands[0], a->commands, data->envp) == -1)
	{
		data->exit_status = 127;
		if (!if_path_exist(data, a))
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (a->commands[0] && ft_strchr(a->commands[0], '/'))
		{
			if (!access(cmnd, X_OK) || !access(cmnd, F_OK))
			{
				data->exit_status = 126;
				if (!access(cmnd, X_OK))
					ft_putstr_fd(": is a directory\n", 2);
				else
					ft_putstr_fd(": Permission denied\n", 2);
			}
			else
				ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (a->commands[0] && !ft_strchr(a->commands[0], '/'))
			ft_putstr_fd(": command not found\n", 2);
	}
	exit(data->exit_status);
}

void	ft_bexit(t_data *data, int exitcode)
{
	reset_values(data);
	exit(exitcode);
}

int	ft_exit(t_data *data)
{
	ft_putendl_fd("exit", 2);
	if (data->mini->arr->commands[1] && data->mini->arr->commands[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		data->exit_status = 1;
		return (1);
	}
	if (data->mini->arr->commands[1]
		&& !ft_isalldigit(data->mini->arr->commands[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->mini->arr->commands[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_bexit(data, -1);
	}
	else if (data->mini->arr->commands[1])
		ft_bexit(data, ft_atoi(data->mini->arr->commands[1]));
	else
		ft_bexit(data, 0);
	return (0);
}

int	if_our_command(t_data *data, t_parser *a)
{
	char	*cmnd;
	int		j;

	j = 0;
	cmnd = a->commands[0];
	if (cmnd == NULL)
		return (1);
	if (!ft_strcmp(cmnd, "echo"))
		j = echo(data, a);
	else if (!ft_strcmp(cmnd, "env"))
		j = env(data);
	else if (!ft_strcmp(cmnd, "cd"))
		j = cd(data, a);
	else if (!ft_strcmp(cmnd, "pwd"))
		j = pwd(data);
	else if (!ft_strcmp(cmnd, "export"))
		j = export(data, a);
	else if (!ft_strcmp(cmnd, "unset"))
		j = unset(data, a);
	else if (!ft_strcmp(cmnd, "exit"))
		j = ft_exit(data);
	while (data->tokens->prev != NULL)
		data->tokens = data->tokens->prev;
	return (j);
}

int	is_our_command(char *content)
{
	if (!ft_strcmp(content, "exit") || !ft_strcmp(content, "pwd")
		|| !ft_strcmp(content, "cd") || !ft_strcmp(content, "export")
		|| !ft_strcmp(content, "unset") || !ft_strcmp(content, "env")
		|| !ft_strcmp(content, "echo"))
		return (1);
	return (0);
}
