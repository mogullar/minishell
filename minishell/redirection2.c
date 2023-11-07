/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:44:31 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/07 14:11:11 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_error(t_data *data, char **redir, int i, t_parser *a)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir[i + 1], 2);
	if (!access(redir[i + 1], X_OK) || !access(redir[i + 1], F_OK))
	{
		data->exit_status = 1;
		if (!access(redir[i + 1], X_OK))
			ft_putstr_fd(": is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
	}
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	close_fds(data);
	if (!is_our_command(a->commands[0]))
		exit(1);
}

int	ft_check_out(char **redir)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (redir[i])
	{
		if (!ft_strcmp(redir[i], ">") || !ft_strcmp(redir[i], ">>"))
		{
			if (fd > 0)
				close(fd);
			if (!ft_strcmp(redir[i], ">"))
				fd = open(redir[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
			else
				fd = open(redir[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		i++;
	}
	return (fd);
}

int	ft_check_last(char **redir)
{
	int	flag;
	int	i;

	flag = -1;
	i = 0;
	while (redir[i])
	{
		if (!ft_strcmp(redir[i], "<"))
			flag = 0;
		else if (!ft_strcmp(redir[i], "<<"))
			flag = 1;
		i++;
	}
	return (flag);
}

int	ft_check_in(char **redir, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (redir[i])
	{
		if (!ft_strcmp(redir[i], "<"))
		{
			if (fd > 0)
				close(fd);
			fd = open(redir[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(redir[i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				data->exit_status = 1;
				return (-2);
			}
		}
		i++;
	}
	return (fd);
}

void	take_outputs(t_data *data, t_parser *a)
{
	if (ft_check_last(a->red) == 1 && a->hd_fd > 0)
		dup2(a->hd_fd, 0);
	else if (ft_check_last(a->red) == 0 && a->in_fd > 0)
		dup2(a->in_fd, 0);
	if (a->out_fd > 0)
		dup2(a->out_fd, 1);
	close_fds(data);
}
