#include "pipex.h"

void	heredoc(t_shit *pipex, char *limiter)
{
	char	*line;
	char	*temp;

	temp = ft_strjoin(limiter, "\n");
	pipex->infile = ft_open(".heredocfile",
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	ft_putstr_fd("Heredoc >> ", 1);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			exit(0);
		if (ft_strncmp(line, temp, ft_strlen(line)) == 0)
		{
			free(line);
			free(temp);
			break ;
		}
		ft_putstr_fd("Heredoc >> ", 1);
		ft_putstr_fd(line, pipex->infile);
		free(line);
	}
	ft_close(pipex->infile);
	pipex->infile = ft_open(".heredocfile", O_RDONLY, 0666);
}

static void	getpath(t_shit *pipex, char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			pipex->path = ft_split(*envp + 5, ':');
			return ;
		}
		envp++;
	}
	ft_putstr_fd("YOU SHALL NOTTTT PATHHHH~\n", 2);
	exit (1);
}

t_shit	*initializer(char **argv, int argc, char **envp)
{
	t_shit	*pipex;

	pipex = malloc(sizeof(t_shit));
	getpath(pipex, envp);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->hereflag = 1;
		heredoc(pipex, argv[2]);
		pipex->outfile = ft_open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0666);
	}
	else
	{
		pipex->hereflag = 0;
		pipex->infile = ft_open(argv[1], O_RDONLY, 0666);
		pipex->outfile = ft_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0666);
	}
	pipex->pipenum = argc - (4 + pipex->hereflag);
	return (pipex);
}
