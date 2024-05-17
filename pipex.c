/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:40:33 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/05/10 08:50:02 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"
// #include <unistd.h>
// #include <stdio.h>

// int	main(int ac, char **av, char **env)
// {
// 	char	**split;
// 	char	**path;
// 	pid_t	pid;
// 	int		i;

// 	pid = fork();
// 		path = ft_split("/Users/asid-ahm/Library/Python/3.9/bin:/Users/asid-ahm/.docker/bin:/Users/asid-ahm/Library/Python/3.9/bin:/Users/asid-ahm/.docker/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/asid-ahm/Downloads/42-ValgrindContainer", ':');
// 		i = -1;
// 		while (path[++i])
// 			path[i] = ft_strjoin(path[i], "/");
// 		i = -1;
// 		if (ac >= 3)
// 		{
// 			if (pid)
// 			{
// 				// printf("this first\n");
// 				split = ft_split(av[1], ' ');
// 				while (path[++i])
// 				{
// 					if (!access(ft_strjoin(path[i], split[0]), X_OK))
// 						execve(ft_strjoin(path[i], split[0]), split, env);
// 				}
// 			}
// 			else
// 			{
// 				// printf("no this first\n");
// 				split = ft_split(av[2], ' ');
// 				i = -1;
// 				while (path[++i])
// 				{
// 					if (!access(ft_strjoin(path[i], split[0]), X_OK))
// 						execve(ft_strjoin(path[i], split[0]), split, env);
// 				}
// 			}
// 		}
// }

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> // Include for open() and O_CREAT

int main(int ac, char **av, char **env) {
    char **split;
    char **path;
    pid_t pid;
    int i;
    int j;

	j = 0;
    // Create a file descriptor for redirection
    // int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // if (fd == -1) {
    //     perror("open");
    //     return 1;
    // }

    while (j++ <= ac)
	{
		pid = fork();
		path = ft_split(getenv("PATH"), ':');
		i = -1;
		while (path[++i])
			path[i] = ft_strjoin(path[i], "/");
		i = -1;
		if (ac >= 3) {
			if (pid == 0) {
				split = ft_split(av[j], ' ');
				i = -1;
				while (path[++i]) {
					if (!access(ft_strjoin(path[i], split[0]), X_OK)) {
						// Redirect output to the file descriptor
						// if (dup2(fd, 1) == -1) {
						// 	perror("dup2");
						// 	return 1;
						// }
						// Close the original file descriptor
						// close(fd);
						execve(ft_strjoin(path[i], split[0]), split, env);
					}
				}
			}
    	}
	}

    // Close the file descriptor if it's not closed in the child process
    // close(fd);

    return 0;
}
