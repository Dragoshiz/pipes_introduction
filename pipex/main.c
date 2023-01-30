/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:29:25 by dimbrea           #+#    #+#             */
/*   Updated: 2022/05/27 14:17:02 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//function to check if command exists
char	*ft_cmnd1_chk(t_vars *vars, char *argv[])
{
	int	i;

	i = 0;
	vars->cmd1 = ft_split(argv[2], ' ');
	while (vars->paths[i])
	{
		vars->cmd1_path = ft_strjoin(vars->paths[i], "/");
		vars->cmd1_path = ft_strjoin2(vars->cmd1_path, vars->cmd1[0]);
		if (access(vars->cmd1_path, F_OK) == 0)
			return (vars->cmd1_path);
		else
		{
			free(vars->cmd1_path);
		}
		i++;
	}
	ft_errmsg(3);
	return (NULL);
}

//function to checl of command 2 exists
char	*ft_cmnd2_chk(t_vars *vars, char *argv[])
{
	int	i;

	i = 0;
	vars->cmd2 = ft_split (argv[3], ' ');
	while (vars->paths[i])
	{
		vars->cmd2_path = ft_strjoin(vars->paths[i], "/");
		vars->cmd2_path = ft_strjoin2(vars->cmd2_path, vars->cmd2[0]);
		if (access(vars->cmd2_path, F_OK) == 0)
			return (vars->cmd2_path);
		else
		{
			free(vars->cmd2_path);
		}
		i++;
	}
	ft_errmsg(3);
	return (NULL);
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars	vars;

	ft_check_n_open(argc, argv, env, &vars);
	if (pipe(vars.fd) < 0)
		ft_errmsg(0);
	vars.pid = fork();
	if (vars.pid == 0)
	{
		if (dup2(vars.fd_f1, 0) < 0 || dup2(vars.fd[1], 1) < 0)
			ft_errmsg(4);
		ft_close_fds(&vars);
		if (!execve(vars.cmd1_path, vars.cmd1, env))
			ft_errmsg(5);
	}
	waitpid(vars.pid, NULL, 0);
	if (vars.pid > 0)
	{
		if (dup2(vars.fd_f2, 1) < 0 || dup2(vars.fd[0], 0) < 0)
			ft_errmsg(4);
		ft_close_fds(&vars);
		if (!execve(vars.cmd2_path, vars.cmd2, env))
			ft_errmsg(5);
	}
	return (0);
}
