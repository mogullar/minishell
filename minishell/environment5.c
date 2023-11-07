/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:35:24 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 18:18:33 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_len_strs(t_append_var *len_strs, t_append_var *tmp)
{
	len_strs = tmp;
	while (len_strs)
	{
		tmp = len_strs->next;
		free(len_strs->content);
		free(len_strs);
		len_strs = tmp;
	}
	free(len_strs);
}

int	free_of_export(t_data *data, char *content, char ***content_val, int cntrol)
{
	free(content);
	free_arrays(content_val, -1);
	if (cntrol)
		free_arrays(&(data->vars), -1);
	if (data->exit_status)
		return (2);
	return (cntrol);
}

int	ft_free_content(char **split, char *content)
{
	if (ft_strcmp(split[0], content))
	{
		free(content);
		return (2);
	}
	free(content);
	free_arrays(&split, -1);
	return (1);
}

int	env(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->envp[++i] != NULL)
	{
		j = -1;
		while (data->envp[i][++j])
		{
			if (data->envp[i][j] == '=')
				break ;
		}
		if (data->envp[i][j] == '=')
			printf("%s\n", data->envp[i]);
	}
	data->exit_status = 0;
	return (data->exit_status);
}

int	if_not_var(t_data *data, char **content)
{
	ft_putstr_fd("minishell: export: `': not a valid identifier\n", 2);
	data->exit_status = 1;
	free(&content);
	return (1);
}
