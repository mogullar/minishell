/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:34:42 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:34:53 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_init(t_data *data)
{
	int	qcount;
	int	dqcount;

	dqcount = dquotecount(data);
	qcount = quotecount(data);
	data->dquote = (char **)ft_calloc(((dqcount / 2) + 1), sizeof(char *));
	data->dquote[dqcount / 2] = NULL;
	data->quote = (char **)ft_calloc(((qcount / 2) + 1), sizeof(char *));
	data->quote[qcount / 2] = NULL;
}

int	fillforcontents(t_data *data, int *len, int i)
{
	while (data->command_line[i] && data->command_line[i] != ' ')
	{
		if (data->command_line[i] == '\'')
			i = fill_tokens_quote(data, i, len);
		else if (data->command_line[i] == '\"')
			i = fill_tokens_dquote(data, i, len);
		else if (isspecialchar(data->command_line[i]))
			i = fill_tokens_specials(data, i, len);
		else
			i = fill_tokens_default(data, i, len);
	}
	return (i);
}

void	fill_for_tokens(t_data *data)
{
	while (data->tokens->contents->prev != NULL)
		data->tokens->contents = data->tokens->contents->prev;
	data->tokens->next = malloc(sizeof(t_token));
	data->tokens->next->prev = data->tokens;
	data->tokens->next->contents = malloc(sizeof(t_contents));
	data->tokens->next->contents->next = NULL;
	data->tokens->next->contents->prev = NULL;
	data->tokens = data->tokens->next;
}
