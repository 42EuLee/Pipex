#include "pipex.h"

void	parent(t_shit *pipex, int count, int *prev_fd, int fd[2])
{
	if (count == 0)
	{
		ft_close(fd[1]);
		*prev_fd = fd[0];
	}
	else if (count == pipex->pipenum)
	{
		ft_close(*prev_fd);
	}
	else
	{
		ft_close(*prev_fd);
		ft_close(fd[1]);
		*prev_fd = fd[0];
	}
}

void	children(t_shit *pipex, int count, int prev_fd, int fd[2])
{
	if (count == 0)
	{
		ft_dup2(pipex->infile, 0);
		ft_close(pipex->infile);
		ft_dup2(fd[1], 1);
		ft_close(fd[1]);
		ft_close(fd[0]);
	}
	else if (count == pipex->pipenum)
	{
		ft_dup2(pipex->outfile, 1);
		ft_close(pipex->outfile);
		ft_dup2(fd[0], 0);
		ft_close(fd[0]);
		// ft_close(fd[1]); // here is wrong ;_;
	}
	else
	{
		ft_dup2(prev_fd, 0);
		ft_close(prev_fd);
		ft_dup2(fd[1], 1);
		ft_close(fd[1]);
		ft_close(fd[0]);
	}
}

void	execute_command(t_shit *pipex, char **argv, char **envp, int count)
{
	int		i;
	char	**cmd;
	char	*temp;

	i = 0;
	cmd = ft_split(argv[count + 2 + pipex->hereflag], ' ');
	while (pipex->path[i])
	{
		temp = join_key_value(pipex->path[i],
				argv[count + 2 + pipex->hereflag], '/');
		execve(temp, cmd, envp);
		free(temp);
		i++;
	}
	ft_putstr_fd("Execuve failed\n", 2);
	exit(1);
}

void	executor(t_shit *pipex, char **argv, char **envp)
{
	static int	prev_fd;
	int			fd[2];
	int			count;
	int			process;

	count = 0;
	while (count <= pipex->pipenum)
	{
		if (count != pipex->pipenum)
			ft_pipe(fd);
		process = fork();
		if (process == 0)
		{
			children(pipex, count, prev_fd, fd);
			execute_command(pipex, argv, envp, count);
			exit(0);
		}
		else
			parent(pipex, count, &prev_fd, fd);
		count++;
	}
}
