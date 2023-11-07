/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:23:55 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:23:56 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_arrays(t_data *data, char **contents, int *types, char *content)
{
	*contents = ft_strjoin2(*contents, content);
	*types = data->tokens->contents->type;
	data->tokens->contents = data->tokens->contents->next;
}
