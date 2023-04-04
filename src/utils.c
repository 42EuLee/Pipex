#include "pipex.h"

int	ft_open(char *filename, int flags, int chmod)
{
	int	fd;

	fd = open(filename, flags, chmod);
	if (fd == -1)
	{
		if (!filename)
			ft_putstr_fd("(null)", 2);
		else
			ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	return (fd);
}

void	ft_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("Pipe failed\n");
		exit(1);
	}
}

int	ft_fork(void)
{
	int	process;

	process = fork();
	if (process == -1)
	{
		perror("Fork failed\n");
		exit(1);
	}
	return (process);
}

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed\n");
		exit(1);
	}
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Close failed\n");
		exit(1);
	}
}
