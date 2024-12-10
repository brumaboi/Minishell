/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:12:45 by marvin            #+#    #+#             */
/*   Updated: 2024/12/07 01:12:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	process_here_doc(int *pipefd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			perror("readline");
			return (-1);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_here_doc(t_ast *node)
{
	int		pipefd[2];
	char	*delimiter;

	if (!node || !node->file)
		return (-1);
	delimiter = node->file;
	create_pipe(pipefd);
	if (process_here_doc(pipefd, delimiter) == -1)
	{
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);
	if (redir_fd(pipefd[0], STDIN_FILENO, "dup2") == -1)
		return (-1);
	close(pipefd[0]);
	return (0);
}
