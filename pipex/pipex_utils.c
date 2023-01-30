/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:51:02 by dimbrea           #+#    #+#             */
/*   Updated: 2022/05/24 17:35:42 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//finds path environment var, splits by ':' and saves.
void	ft_path(char *env[], t_vars *vars)
{
	int		i;
	int		k;
	int		j;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			path = ft_strdup(env[i]);
		i++;
	}
	i = 5;
	vars->paths = ft_split(path, ':');
	k = ft_strlen(vars->paths[0]);
	j = 0;
	while (i <= k)
	{
		vars->paths[0][j] = vars->paths[0][i];
		i++;
		j++;
	}
	vars->paths[0][j] = '\n';
	free(path);
}

//checks if files exists and if readable/writeble is valid
void	ft_exist(char *argv[])
{
	int	fd;

	fd = access(argv[1], R_OK);
	if (fd < 0)
	{
		write(1, "First file does not exist/not readable", 38);
		exit(0);
	}
}

//checks if arguments ar valid and open files
void	ft_check_n_open(int argc, char *argv[], char *env[], t_vars *vars)
{
	if (argc != 5)
	{
		write(1, "Pipex must have 4 arguments!", 28);
		exit(1);
	}
	ft_exist(argv);
	ft_path(env, vars);
	ft_cmnd1_chk(vars, argv);
	ft_cmnd2_chk(vars, argv);
	vars->fd_f1 = open(argv[1], O_RDONLY);
	vars->fd_f2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (vars->fd_f1 < 0 || vars->fd_f2 < 0)
		ft_errmsg(2);
}

//function to close file descriptors
void	ft_close_fds(t_vars *vars)
{
	close(vars->fd[0]);
	close(vars->fd[1]);
	close(vars->fd_f1);
	close(vars->fd_f2);
}

//function to write errmsg and exit program
void	ft_errmsg(int err)
{
	if (err == 0)
		write(1, "Error with pipe function", 24);
	if (err == 1)
		write(1, "Error with fork function", 24);
	if (err == 2)
		write(1, "Error opening a file", 20);
	if (err == 3)
		write(1, "Command not found!", 18);
	if (err == 4)
		write(1, "Error with the dup2 function", 28);
	if (err == 5)
		write(1, "Error executing command (execve)", 32);
	exit(1);
}
