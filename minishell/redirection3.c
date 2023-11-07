/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:39:46 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/07 14:11:48 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_first(t_data *data, t_parser *a, int i)
{
	a->in_fd = ft_check_in(a->red, data);
	a->out_fd = ft_check_out(a->red);
	if (a->out_fd == -2)
		exit(1);
	else
	{
		dup2(data->mini->pipe[i].fd[1], 1);
		take_outputs(data, a);
		if (is_our_command(a->commands[0]) && a->in_fd != -2)
			if_our_command(data, a);
		else if (!is_our_command(a->commands[0]) && a->in_fd != -2)
			ft_execve(data, a, a->commands[0]);
		exit(data->exit_status);
	}
}

void	ft_middle(t_data *data, t_parser *a, int i)
{
	a->in_fd = ft_check_in(a->red, data);
	a->out_fd = ft_check_out(a->red);
	if (a->out_fd == -2)
		exit(1);
	else
	{
		dup2(data->mini->pipe[i].fd[1], 1);
		dup2(data->mini->pipe[i - 1].fd[0], 0);
		if (ft_check_last(a->red) == 1 && a->hd_fd > 0)
			dup2(a->hd_fd, 0);
		else if (ft_check_last(a->red) == 0 && a->in_fd > 0)
			dup2(a->in_fd, 0);
		if (a->out_fd > 0)
			dup2(a->out_fd, 1);
		close_fds(data);
		if (is_our_command(a->commands[0]) && a->in_fd != -2)
			if_our_command(data, a);
		else if (!is_our_command(a->commands[0]) && a->in_fd != -2)
			ft_execve(data, a, a->commands[0]);
		exit(data->exit_status);
	}
}

void	if_only_command(t_data *data, t_parser *a)
{
	pid_t	pid;

	g_global.test2 = 1;
	a->in_fd = ft_check_in(a->red, data);
	a->out_fd = ft_check_out(a->red);
	if (a->out_fd == -2)
		return ;
	else
	{
		if (ft_check_last(a->red) != -1 || a->out_fd > 0)
		{
			pid = fork();
			if (pid == 0)
			{
				take_outputs(data, a);
				if (a->in_fd != -2 && a->out_fd != -2)
					exit(if_our_command(data, a));
				if (a->hd_fd == -1)
					exit(130);
			}
			ft_wait_single(pid, data);
		}
		else
			if_our_command(data, a);
	}
}

void	if_multiple_commands(t_data *data, t_parser *a)
{
	int	i;

	i = 0;
	while (i < data->mini->p_count && !g_global.a)
	{
		data->mini->pipe[i].pid = fork();
		if (data->mini->pipe[i].pid == 0)
		{
			if (i == 0)
				ft_first(data, a, i);
			else if (i == data->mini->p_count - 1)
				ft_last(data, a, i);
			else
				ft_middle(data, a, i);
		}
		a = a->next;
		i++;
	}
	close_fds(data);
	ft_wait(data, data->mini);
}

void	execute(t_data *data)
{
	t_parser	*a;

	ft_heredoc_init(*data, data->mini);
	ft_init_pipe(data->mini);
	a = data->mini->arr;
	if (data->mini->p_count == 1 && is_our_command(a->commands[0])
		&& !g_global.a)
		if_only_command(data, a);
	else
		if_multiple_commands(data, a);
}
