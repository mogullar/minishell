/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:33:35 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 20:34:47 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	array_filler(t_data *data, char ***contents, int **types, char *content)
{
	if (data->tokens->contents->prev)
		data->icopy++;
	fill_arrays(data, &(*contents)[data->icopy], &(*types)[data->icopy],
		content);
	if (data->tokens->contents->next)
		data->icopy++;
}

int	*continue_contents(t_data *data, char ***contents, int **types)
{
	char	*content;

	data->icopy = 0;
	while (data->tokens->next)
	{
		while (data->tokens->contents->next)
		{
			content = join_content(data);
			if (data->tokens->contents->type != 6
				&& data->tokens->contents->type != 7)
				array_filler(data, contents, types, content);
			else
				fill_arrays(data, &(*contents)[data->icopy],
					&(*types)[data->icopy], content);
		}
		data->icopy++;
		go_to_back(data, 1);
	}
	go_to_back(data, 0);
	return (*types);
}

char	**contents_splitter(t_data *data, int len)
{
	int		*types;
	char	**contents;

	contents = ft_calloc(len + 1, sizeof(char *));
	types = malloc(sizeof(int) * (len + 1));
	if (!contents || !types)
		return (NULL);
	types = continue_contents(data, &contents, &types);
	data->types = types;
	return (contents);
}

char	**to_contents_returner(t_data *data, int len)
{
	char	**contents;

	go_to_back(data, 0);
	contents = contents_splitter(data, len);
	return (contents);
}

char	**to_contents(t_data *data)
{
	int	len;
	int	if_string;

	len = 0;
	while (data->tokens->next)
	{
		if_string = 0;
		while (data->tokens->contents->next)
		{
			if (data->tokens->contents->type != 6
				&& data->tokens->contents->type != 7)
				len++;
			else if (data->tokens->contents->next->type == 6
				|| data->tokens->contents->next->type == 7)
				if_string = 1;
			else
				len++;
			data->tokens->contents = data->tokens->contents->next;
		}
		if (if_string)
			len++;
		go_to_back(data, 1);
	}
	return (to_contents_returner(data, len));
}
