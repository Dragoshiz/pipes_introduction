/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:30:09 by dimbrea           #+#    #+#             */
/*   Updated: 2022/05/24 17:31:27 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_vars
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
	int		fd_f1;
	int		fd_f2;
	int		fd[2];
	int		pid;
}t_vars;

void	ft_path(char *env[], t_vars *vars);
void	ft_exist(char *argv[]);
void	ft_close_fds(t_vars *vars);
void	ft_check_n_open(int argc, char *argv[], char *env[], t_vars *vars);
void	ft_errmsg(int err);
char	*ft_cmnd1_chk(t_vars *vars, char *argv[]);
char	*ft_cmnd2_chk(t_vars *vars, char *argv[]);

#endif