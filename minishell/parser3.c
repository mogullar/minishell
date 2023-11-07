/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:24:05 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:33:23 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_for_commands(t_data *data, int k, int *j)
{
	char	*path;

	if (!(*j))
	{
		(*j)++;
		if (!ft_strcmp(data->contents[k], ""))
			return (ft_calloc(1, 1));
		if (is_our_command(data->contents[k]))
			return (ft_strdup(data->contents[k]));
		else
		{
			if (ft_strchr(data->contents[k], '/'))
				return (ft_strdup(data->contents[k]));
			else
			{
				path = find_path(data, data->contents[k]);
				if (!path)
					return (ft_strdup(data->contents[k]));
				return (path);
			}
		}
	}
	else
		return (ft_strdup(data->contents[k]));
}

void	fill_the_arrays(int *k, t_data *data, char ***commands, char ***red)
{
	int	j;
	int	l;
	int	i;

	j = 0;
	l = 0;
	i = 0;
	while (data->contents[(*k)] && data->types[(*k)] != PIPE)
	{
		if (*k != 0)
		{
			if (if_command(data, *k))
				(*commands)[j++] = fill_for_commands(data, *k, &i);
			else
				(*red)[l++] = data->contents[(*k)];
		}
		else if (data->types[(*k)] == COMMAND)
			(*commands)[j++] = fill_for_commands(data, *k, &i);
		else
			(*red)[l++] = data->contents[(*k)];
		(*k)++;
	}
	data->mini->arr->commands = (*commands);
	data->mini->arr->red = (*red);
}

void	find_len(t_data *data, int *len, int *i)
{
	*len = 0;
	while (data->tokens->contents->content[*i]
		&& data->tokens->contents->content[*i] != '$')
	{
		(*len)++;
		(*i)++;
	}
}

char	*join_content(t_data *data)
{
	char	*content;
	int		i;
	int		j;
	int		len;

	i = 0;
	content = NULL;
	if (data->tokens->contents->quote_type == 1
		|| !data->tokens->contents->content[i])
	{
		content = ft_strdup(data->tokens->contents->content);
		return (content);
	}
	while (data->tokens->contents->content[i])
	{
		if (data->tokens->contents->content[i] == '$')
			content = ft_strjoin2(content, fordollar2(data, &i));
		j = i;
		find_len(data, &len, &i);
		content = fill_content(data, j, len, &content);
	}
	return (content);
}

void	go_to_back(t_data *data, int i)
{
	if (i)
	{
		while (data->tokens->contents->prev)
			data->tokens->contents = data->tokens->contents->prev;
		data->tokens = data->tokens->next;
	}
	else
		while (data->tokens->prev)
			data->tokens = data->tokens->prev;
}
