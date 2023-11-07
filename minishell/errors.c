/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:51:51 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 20:01:25 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_errors(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->contents[++i])
	{
		j = i + 1;
		if (isspecialtype(data->types[i]) && (!data->contents[j]
				|| (data->contents[j] && (isspecialtype(data->types[j])
						|| data->contents[j][0] == '$'))
			|| (data->types[i] == PIPE && (!data->types[i - 1]))))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if (isspecialtype(data->types[i]) && data->types[i] != PIPE)
				ft_putstr_fd("newline", 2);
			else
				ft_putstr_fd(data->contents[i], 2);
			ft_putstr_fd("'\n", 2);
			data->exit_status = 2;
			return (1);
		}
	}
	return (0);
}
