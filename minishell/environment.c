/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:41:44 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 18:18:05 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_index(char *content, int *index)
{
	int	j;

	j = 0;
	while (content[j] && content[j] != '=')
		j++;
	*index = -1;
	if (!content || !content[0])
		return (-1);
	return (j);
}

char	**fill_vars(char *content)
{
	char	**content_val;
	int		j;

	j = find_index(content, &j);
	content_val = ft_calloc(3, sizeof(char *));
	content_val[0] = ft_substr(content, 0, j);
	if (content[j])
		content_val[1] = ft_substr(content, j, ft_strlen(content));
	else
		content_val[1] = NULL;
	return (content_val);
}

int	main_loop_ex(t_data *d, t_append_var ***len_strs, int **len, char *content)
{
	int		index;
	int		cntrol;
	char	**content_val;

	if (find_index(content, &index) == -1)
		return (if_not_var(d, &content));
	content_val = fill_vars(content);
	while (d->envp[++index])
	{
		cntrol = if_var_exist(d, &content, &content_val, index);
		if (cntrol)
			break ;
		free_arrays(&d->vars, -1);
	}
	if (!if_only_equal(content, 0))
	{
		if (cntrol == 1 && (content_val[1] != 0
				|| (content[ft_strlen(content) - 1] == '=' && !d->vars[1])))
			change_var(d, index, content_val);
		else if (!cntrol)
			fill_for_strs(d, &len, &len_strs, content);
	}
	if (free_of_export(d, content, &content_val, cntrol) == 2)
		return (0);
	return (1);
}

int	main_loop_for_ex(t_data *data, t_parser *a, t_append_var **len_strs,
		int *len)
{
	int	i;
	int	r;

	i = 0;
	while (a->commands[++i] != NULL)
		r = main_loop_ex(data, &len_strs, &len, ft_strdup(a->commands[i]));
	return (r);
}

int	export(t_data *data, t_parser *a)
{
	t_append_var	*len_strs;
	t_append_var	*tmp;
	int				cntrol;
	int				len;
	int				r;

	cntrol = 0;
	len = 0;
	if_only_export(data, a);
	len_strs = ft_calloc(1, sizeof(t_append_var));
	len_strs->next = NULL;
	tmp = len_strs;
	r = main_loop_for_ex(data, a, &len_strs, &len);
	fill_env(data, len, tmp, len_strs);
	free_len_strs(len_strs, tmp);
	if (r)
		data->exit_status = 0;
	return (data->exit_status);
}
