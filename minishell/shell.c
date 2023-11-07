/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:39:12 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 15:39:12 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	datacreate(t_data *data)
{
	getcwd(data->path, 4096);
	data->tokens = (t_token *)ft_calloc(1, sizeof(t_token));
	data->tokens->contents = (t_contents *)ft_calloc(1, sizeof(t_contents));
	data->mini = (t_pata *)ft_calloc(1, sizeof(t_pata));
	data->mini->arr = ft_calloc(1, sizeof(t_parser));
	data->mini->arr->in_fd = -1;
	data->mini->arr->hd_fd = -1;
	data->mini->arr->out_fd = -1;
	data->tokens->contents->next = NULL;
	data->tokens->contents->prev = NULL;
	data->tokens->next = NULL;
	data->tokens->prev = NULL;
	data->vars = NULL;
	data->fds = NULL;
	data->red_r_fd = 0;
	data->red_l_fd = 0;
	data->red_ll_fd = 0;
	data->counter_dquote = 0;
	data->counter_quote = 0;
	return (*data);
}

void	fill_envp(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->envp = ft_calloc((i + 1), sizeof(char *));
	i = -1;
	while (envp[++i] != NULL)
	{
		data->envp[i] = malloc(ft_strlen(envp[i]) + 1);
		ft_strlcpy(data->envp[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	data->exit_status = 0;
}

void	main_loop(t_data *data)
{
	data->command_line = readline("minishell$ ");
	if (data->command_line == NULL)
		exit(0);
	add_history(data->command_line);
}

void	loop(t_data data)
{
	while (1)
	{
		main_loop(&data);
		if ((quotecount(&data) % 2 != 0 || dquotecount(&data) % 2 != 0)
			|| !(data.command_line && ft_strcmp(data.command_line, "")))
		{
			free(data.command_line);
			continue ;
		}
		else
		{
			lexer(&data);
			parser(&data);
			data.mini->pipe = ft_calloc(data.mini->p_count, sizeof(t_pipe));
			if (!check_for_errors(&data))
				execute(&data);
		}
		reset_values(&data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 1)
		ft_putstr_fd("minishell: there is a parameter\n", 2);
	(void)av;
	data = datacreate(&data);
	fill_envp(&data, envp);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, ft_handler);
	delete_ctrl();
	loop(data);
}
