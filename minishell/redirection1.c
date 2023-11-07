/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:45:11 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 15:55:02 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_init(t_data data, t_pata *mini)
{
	int			i;
	int			j;
	t_parser	*x;

	i = -1;
	x = mini->arr;
	while (++i < mini->p_count)
	{
		j = -1;
		if (!x->red)
		{
			x = x->next;
			continue ;
		}
		while (x->red[++j])
		{
			if (!strcmp(x->red[j], "<<"))
				x->hd_fd = ft_her(x->red[j + 1], data, i);
			if (!x->hd_fd)
				return ;
		}
		x = x->next;
	}
}

void	ft_init_pipe(t_pata *mini)
{
	int	i;

	i = 0;
	while (i < mini->p_count - 1)
	{
		if (pipe(mini->pipe[i++].fd) == -1)
			exit(0);
	}
}

void	close_fds(t_data *x)
{
	int			i;
	t_parser	*z;

	i = 0;
	z = x->mini->arr;
	while (i < x->mini->p_count - 1)
	{
		close(x->mini->pipe[i].fd[0]);
		close(x->mini->pipe[i].fd[1]);
		close(z->hd_fd);
		close(z->in_fd);
		close(z->out_fd);
		i++;
		z = z->next;
	}
	close(z->hd_fd);
	close(z->in_fd);
	close(z->out_fd);
}

void	ft_wait(t_data *data, t_pata *mini)
{
	int	status;
	int	i;

	i = 0;
	while (i < mini->p_count)
		waitpid(mini->pipe[i++].pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
}

void	ft_wait_single(pid_t pid, t_data *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
}
