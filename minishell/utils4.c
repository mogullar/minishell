/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:34:53 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 18:46:36 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum_str(char *content, int i)
{
	int	j;

	j = 0;
	while (content[j] && j < i)
	{
		if (!ft_isalnum(content[j]) && content[j] != '_' && content[j] != '=')
			return (0);
		j++;
	}
	return (1);
}

void	reset_values1(t_data *data)
{
	t_contents	*tmp;
	t_token		*tmp1;

	free(data->command_line);
	data->command_line = NULL;
	while (data->tokens != NULL)
	{
		while (data->tokens->contents->next != NULL)
		{
			tmp = data->tokens->contents->next;
			free(data->tokens->contents->content);
			free(data->tokens->contents);
			data->tokens->contents = tmp;
		}
		free(data->tokens->contents);
		tmp1 = data->tokens->next;
		free(data->tokens);
		data->tokens = tmp1;
	}
	free(data->tokens);
}

void	reset_values(t_data *data)
{
	t_parser	*tmp2;

	g_global.a = 0;
	g_global.test1 = 0;
	g_global.test2 = 0;
	reset_values1(data);
	free_arrays(&(data->quote), -1);
	free_arrays(&(data->dquote), -1);
	free_arrays(&(data->contents), -1);
	while (data->mini->arr->next)
	{
		free_arrays(&data->mini->arr->commands, -1);
		free(data->mini->arr->red);
		tmp2 = data->mini->arr->next;
		free(data->mini->arr);
		data->mini->arr = tmp2;
	}
	free(data->mini->arr->commands);
	free(data->mini->arr);
	free(data->mini->pipe);
	free(data->mini);
	free(data->types);
	*data = datacreate(data);
	data->counter_quote = 0;
	data->counter_dquote = 0;
}

int	check_for_var(char *content, int j)
{
	if (content[j] == '$' || content[j] == '\"' || content[j] == '/'
		|| !ft_isalnum(content[j]) || content[j] == ' ' || content[j] == '='
		|| !content[j])
		return (1);
	return (0);
}

int	if_path_exist(t_data *data, t_parser *a)
{
	char	*str;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(a->commands[0], 2);
	str = isenv(data, "PATH");
	if (!str)
		return (0);
	free(str);
	return (1);
}
