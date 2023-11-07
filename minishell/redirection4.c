/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:41:09 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/07 14:11:59 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_last(t_data *data, t_parser *a, int i)
{
	a->in_fd = ft_check_in(a->red, data);
	a->out_fd = ft_check_out(a->red);
	if (a->out_fd == -2)
		exit(1);
	else
	{
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
