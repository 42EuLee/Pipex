#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_shit
{
	char	**path;
	int		pipenum;
	int		outfile;
	int		infile;
	int		hereflag;

}	t_shit;

int		main(int argc, char **argv, char **envp); // my int main here so good
t_shit	*initializer(char **argv, int argc, char **envp);
void	executor(t_shit *pipex, char **argv, char **envp);
char	*join_key_value(char *str1, char *str2, char c);

/* Utils */
int		ft_open(char *, int flags, int chmod);
void	ft_pipe(int pipefd[2]);
int		ft_fork(void);
void	ft_dup2(int oldfd, int newfd);
void	ft_close(int fd);

#endif