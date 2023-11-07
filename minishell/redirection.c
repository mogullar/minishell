/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:23:42 by msaritas          #+#    #+#             */
/*   Updated: 2023/11/06 16:23:43 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_file_her(int i)
{
	char	*file;
	char	*number;
	char	*the_file;

	file = ft_strdup("heredoc");
	number = ft_itoa(i);
	the_file = ft_strjoin(file, number);
	free(number);
	free(file);
	return (the_file);
}

int	if_del(int *fd, char **line, char **the_file)
{
	int	fd2;

	close(*fd);
	free(*line);
	fd2 = open(*the_file, O_RDONLY);
	free(*the_file);
	return (fd2);
}

void	ft_if_broke(t_data data, int fd, char *file, char *line)
{
	ft_init_pipe(data.mini);
	if (data.mini->p_count > 1)
		if_multiple_commands(&data, data.mini->arr);
	close(fd);
	free(line);
	free(file);
	reset_values(&data);
	loop(data);
}

int	ft_global_a(int fd, char *line, char *the_file)
{
	close(fd);
	free(line);
	free(the_file);
	return (-1);
}

int	ft_her(char *delim, t_data data, int i)
{
	char	*line;
	char	*last_line;
	int		fd;
	char	*the_file;

	the_file = open_file_her(i);
	fd = open(the_file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	g_global.test1 = 1;
	while (1)
	{
		line = readline("> ");
		if (g_global.a)
			return (ft_global_a(fd, line, the_file));
		if (!line)
			ft_if_broke(data, fd, the_file, line);
		if (!ft_strcmp(line, delim))
			return (if_del(&fd, &line, &the_file));
		last_line = ft_strjoin(line, "\n");
		free(line);
		write(fd, last_line, strlen(last_line));
		if (!line)
			return (1);
		free(last_line);
	}
}
