/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:34:16 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:34:21 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	continue_fillquotes(t_data *data, int i)
{
	int	index;
	int	len;

	index = i;
	len = 0;
	while (data->command_line[i] && data->command_line[i] != '\'')
	{
		i++;
		len++;
	}
	data->quote[data->counter_quote++] = ft_substr(data->command_line, index,
			len);
	i++;
	return (i);
}

void	fillforquotes(t_data *data, int *i)
{
	int	k;

	k = 0;
	while (data->command_line[*i] && data->command_line[*i] == '\'')
	{
		(*i)++;
		k++;
	}
	if (!(k % 2))
	{
		data->quote[data->counter_quote++] = ft_calloc(1, sizeof(char));
		while (data->command_line[*i] && (data->command_line[*i] != '\''
				&& data->command_line[*i] != '\"'))
			(*i)++;
	}
	else
		*i = continue_fillquotes(data, *i);
}

int	continue_filldquotes(t_data *data, int i)
{
	int	index;
	int	len;

	index = i;
	len = 0;
	while (data->command_line[i] && data->command_line[i] != '\"')
	{
		i++;
		len++;
	}
	data->dquote[data->counter_dquote++] = ft_substr(data->command_line, index,
			len);
	i++;
	return (i);
}

void	fillfordquotes(t_data *data, int *i)
{
	int	k;

	k = 0;
	while (data->command_line[*i] && data->command_line[*i] == '\"')
	{
		(*i)++;
		k++;
	}
	if (!(k % 2))
	{
		data->dquote[data->counter_dquote++] = ft_calloc(1, sizeof(char));
		while (data->command_line[*i] && (data->command_line[*i] != '\"'
				&& data->command_line[*i] != '\''))
			(*i)++;
	}
	else
		*i = continue_filldquotes(data, *i);
}

void	lexer(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = data->command_line;
	data->command_line = ft_strtrim(tmp, " ");
	if (tmp)
		free(tmp);
	lexer_init(data);
	while (data->command_line[i])
	{
		j = i;
		if (data->command_line[i] == '\'')
			fillforquotes(data, &i);
		else if (data->command_line[i] == '\"')
			fillfordquotes(data, &i);
		if (i == j)
			i++;
	}
	lexer2(data);
}
