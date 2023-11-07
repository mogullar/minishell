/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:36:00 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 20:21:01 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arrays(char ***split, int i)
{
	while ((*split)[++i])
		free((*split)[i]);
	free(*split);
}

int	if_only_equal(char *content, int index)
{
	if ((content[find_index(content, &index)] == '=' && find_index(content,
				&index) != 0) || content[find_index(content, &index)] != '=')
		return (0);
	return (1);
}

int	if_command(t_data *data, int k)
{
	if (((data->types[k - 1] == STRING || data->types[k - 1] == COMMAND
				|| data->types[k - 1] == PIPE)
			&& data->types[k] == STRING) || data->types[k] == COMMAND)
		return (1);
	return (0);
}
