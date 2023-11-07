/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:40:56 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 19:06:39 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*for_content(t_data *data_tmp, char **content, int *i, int *index)
{
	int		len;
	char	*str;

	*content = NULL;
	*index = -1;
	len = 0;
	while (data_tmp->tokens->contents->next != NULL)
	{
		str = join_content(data_tmp);
		*content = ft_strjoin2(*content, str);
		data_tmp->tokens->contents = data_tmp->tokens->contents->next;
	}
	while (data_tmp->tokens->contents->prev != NULL)
		data_tmp->tokens->contents = data_tmp->tokens->contents->prev;
	*i = 0;
	if (!(*content) || !(**content))
		return (NULL);
	while ((*content)[*i] && (*content)[*i] != '=')
		(*i)++;
	return (*content);
}

void	change_var(t_data *data, int index, char **content_val)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_strjoin(data->vars[0], content_val[1]);
	free(data->envp[index]);
	data->envp[index] = ft_calloc(ft_strlen(var) + 1, 1);
	ft_strlcpy(data->envp[index], var, ft_strlen(var) + 1);
	if (content_val[1])
		free(var);
}

int	free_of_unset(t_data *data, char **split, char *content)
{
	free_arrays(&split, -1);
	ft_putstr_fd("minishell: unset: `': not a valid identifier\n", 2);
	free(content);
	data->exit_status = 1;
	return (0);
}

int	free_of_unset2(t_data *data, char **split, char *content)
{
	free_arrays(&split, -1);
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(content);
	data->exit_status = 1;
	return (0);
}

void	fill_for_strs_unset(t_data *data, int **len, t_append_var ***len_strs,
		char *content)
{
	int	i;

	i = find_index(content, &i);
	if (ft_isdigit(content[0]) || !ft_isalnum_str(content, i))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->exit_status = 1;
		return ;
	}
	(**len)++;
	if (!(**len_strs))
		(**len_strs) = ft_calloc(1, sizeof(t_append_var));
	(**len_strs)->content = ft_calloc(ft_strlen(content) + 1, 1);
	ft_strlcpy((**len_strs)->content, content, ft_strlen(content) + 1);
	(**len_strs)->next = NULL;
	(**len_strs) = (**len_strs)->next;
}
