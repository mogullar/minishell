/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:35:01 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:35:06 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_tokens_quote(t_data *data, int j, int *len)
{
	*len = 0;
	while (data->command_line[j] && data->command_line[j] == '\'')
		j++;
	*len = ft_strlen(data->quote[data->counter_quote]);
	data->tokens->contents->content = malloc(sizeof(char) * ((*len) + 1));
	ft_strlcpy(data->tokens->contents->content,
		data->quote[data->counter_quote], (*len) + 1);
	data->tokens->contents->content[*len] = '\0';
	data->counter_quote++;
	data->tokens->contents->quote_type = 1;
	data->tokens->contents->next = malloc(sizeof(t_contents));
	data->tokens->contents->next->prev = data->tokens->contents;
	data->tokens->contents = data->tokens->contents->next;
	data->tokens->contents->next = NULL;
	if (*len == 0)
		return (j);
	j += (*len) + 1;
	return (j);
}

int	fill_tokens_dquote(t_data *data, int j, int *len)
{
	*len = 0;
	while (data->command_line[j] && data->command_line[j] == '\"')
		j++;
	*len = ft_strlen(data->dquote[data->counter_dquote]);
	data->tokens->contents->content = malloc(sizeof(char) * ((*len) + 1));
	ft_strlcpy(data->tokens->contents->content,
		data->dquote[data->counter_dquote], (*len) + 1);
	data->tokens->contents->content[*len] = '\0';
	data->counter_dquote++;
	data->tokens->contents->quote_type = 2;
	data->tokens->contents->next = malloc(sizeof(t_contents));
	data->tokens->contents->next->prev = data->tokens->contents;
	data->tokens->contents = data->tokens->contents->next;
	data->tokens->contents->next = NULL;
	if (*len == 0)
		return (j);
	j += (*len) + 1;
	return (j);
}

int	fill_tokens_specials(t_data *data, int j, int *len)
{
	int		index;
	int		i;
	char	c;

	index = j;
	i = j;
	c = data->command_line[j];
	*len = 0;
	while (data->command_line[i] && data->command_line[i] == c)
	{
		(*len)++;
		i++;
	}
	data->tokens->contents->content = ft_substr(data->command_line, index,
			*len);
	data->tokens->contents->quote_type = 0;
	data->tokens->contents->next = malloc(sizeof(t_contents));
	data->tokens->contents->next->prev = data->tokens->contents;
	data->tokens->contents = data->tokens->contents->next;
	data->tokens->contents->next = NULL;
	j = j + (*len);
	return (j);
}

int	fill_tokens_default(t_data *data, int j, int *len)
{
	int	index;

	index = j;
	*len = 0;
	*len = token_len(index, data);
	data->tokens->contents->content = ft_substr(data->command_line, index,
			*len);
	data->tokens->contents->quote_type = 0;
	data->tokens->contents->next = malloc(sizeof(t_contents));
	data->tokens->contents->next->prev = data->tokens->contents;
	data->tokens->contents = data->tokens->contents->next;
	data->tokens->contents->next = NULL;
	j = j + (*len);
	return (j);
}

void	lexer2(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	data->counter_quote = 0;
	data->counter_dquote = 0;
	while (data->command_line[i])
	{
		while (data->command_line[i] == ' ')
			i++;
		if (data->command_line[i] == '\'')
			i = fill_tokens_quote(data, i, &len);
		else if (data->command_line[i] == '\"')
			i = fill_tokens_dquote(data, i, &len);
		else if (isspecialchar(data->command_line[i]))
			i = fill_tokens_specials(data, i, &len);
		else
			i = fill_tokens_default(data, i, &len);
		i = fillforcontents(data, &len, i);
		fill_for_tokens(data);
	}
	data->tokens->next = NULL;
	while (data->tokens->prev != NULL)
		data->tokens = data->tokens->prev;
}
