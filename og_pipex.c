/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   og_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 04:02:27 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/05/17 17:07:27 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		pid;
	int		i;
	int		fd[2];
	int		fdd;
	int		fdd1;
	char	**split;
	char	**path;
	char	*command;

	path = get_path(env);
	if (!path)
		return (1);
	i = -1;
	if (ac == 5)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			fdd1 = open(av[1], O_RDONLY);
			if (fdd1 == -1)
			{
				perror("Error");
				exit(1);
			}
			close(fd[0]);
			dup2(fdd1, 0);
			dup2(fd[1], 1);
			split = ft_split(av[2], ' ');
			while(path[++i])
			{
				command = ft_strjoin(path[i], split[0]);
				if (!access(command, X_OK))
				{
					execve(command, split, env);
				}		
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
			fdd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fdd == -1)
			{
				perror("Error");
				return(1);
			}
			close(fd[1]);
			dup2(fd[0], 0);
			dup2(fdd, 1);
			split = ft_split(av[3], ' ');
			while(path[++i])
			{
				command = ft_strjoin(path[i], split[0]);
				if (!access(command, X_OK))
				{
					execve(command, split, env);
				}		
			}
		}
	}
}