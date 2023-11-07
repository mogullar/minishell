/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:37:50 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 15:37:52 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_counter(t_data *data)
{
	int	i;
	int	p_count;

	p_count = 0;
	i = 0;
	while (data->contents[i])
	{
		if (data->types[i] == PIPE)
			p_count++;
		i++;
	}
	p_count++;
	return (p_count);
}

int	counter_commands(t_data *data, int token, int k)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (++i < token)
	{
		if (k != 0)
		{
			if (((data->types[k - 1] == STRING || data->types[k - 1] == COMMAND
						|| data->types[k - 1] == PIPE)
					&& data->types[k] == STRING) || data->types[k] == COMMAND)
				len++;
		}
		else if (data->types[k] == COMMAND)
			len++;
		k++;
	}
	return (len);
}

int	isspecialtype(int c)
{
	if (c == PIPE || c == RD_L || c == RD_LL || c == RD_R || c == RD_RR)
		return (1);
	return (0);
}

int	isspecialchar(char c)
{
	if (c == '\0')
		return (0);
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	token_len(int i, t_data *data)
{
	int	len;

	len = 0;
	while (data->command_line[i] && (data->command_line[i] != ' '
			&& data->command_line[i] != '\'' && data->command_line[i] != '\"'
			&& data->command_line[i] != '|' && data->command_line[i] != '<'
			&& data->command_line[i] != '>'))
	{
		i++;
		len++;
	}
	return (len);
}
