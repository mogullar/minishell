/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:33:41 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 20:36:35 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_memory(int k, t_data *data, int token, char ***commands)
{
	int		len_of_c;
	char	**red;

	len_of_c = counter_commands(data, token, k);
	(*commands) = ft_calloc(len_of_c + 1, sizeof(char *));
	red = ft_calloc(token - len_of_c + 1, sizeof(char *));
	(*commands)[len_of_c] = NULL;
	red[token - len_of_c] = NULL;
	return (red);
}

int	to_commandline(t_data *data, int i)
{
	char	**commands;
	char	**red;
	int		token;
	int		k;

	token = 0;
	if (data->types[i] == PIPE)
		i++;
	k = i;
	while (data->contents[i] && data->types[i] != PIPE)
	{
		token++;
		i++;
	}
	red = allocate_memory(k, data, token, &commands);
	fill_the_arrays(&k, data, &commands, &red);
	return (i);
}

void	token_typer(t_data *data)
{
	int			quote_type;
	t_contents	*contents;

	quote_type = data->tokens->contents->quote_type;
	contents = data->tokens->contents;
	if (!ft_strcmp(contents->content, "<") && quote_type == 0)
		contents->type = RD_L;
	else if (!ft_strcmp(contents->content, "<<") && quote_type == 0)
		contents->type = RD_LL;
	else if (!ft_strcmp(contents->content, ">") && quote_type == 0)
		contents->type = RD_R;
	else if (!ft_strcmp(contents->content, ">>") && quote_type == 0)
		contents->type = RD_RR;
	else if (!ft_strcmp(contents->content, "|") && quote_type == 0)
		contents->type = PIPE;
	else if ((data->tokens->prev == NULL && contents->prev == NULL)
		|| (data->tokens->prev && !contents->prev
			&& data->tokens->prev->contents->type == PIPE) || (contents->prev
			&& contents->prev->type == PIPE) || (contents->prev
			&& contents->prev->type == COMMAND))
		data->tokens->contents->type = COMMAND;
	else
		data->tokens->contents->type = STRING;
}

void	get_token_type(t_data *data)
{
	while (data->tokens->next != NULL)
	{
		while (data->tokens->contents->next != NULL)
		{
			token_typer(data);
			data->tokens->contents = data->tokens->contents->next;
		}
		while (data->tokens->contents->prev != NULL)
			data->tokens->contents = data->tokens->contents->prev;
		data->tokens = data->tokens->next;
	}
	while (data->tokens->prev != NULL)
		data->tokens = data->tokens->prev;
}

void	parser(t_data *data)
{
	int			i;
	int			p_count;
	int			p_count2;
	t_parser	*tmp;

	i = 0;
	get_token_type(data);
	data->contents = to_contents(data);
	p_count = pipe_counter(data);
	p_count2 = p_count;
	tmp = data->mini->arr;
	while (p_count)
	{
		ft_lstadd_back_par(&data->mini->arr, ft_lstnew_parser());
		i = to_commandline(data, i);
		data->mini->arr = data->mini->arr->next;
		p_count--;
	}
	data->mini->arr = tmp;
	data->mini->p_count = p_count2;
}
