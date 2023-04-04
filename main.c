#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_shit	*pipex;

	if (argc >= 5)
	{
		pipex = initializer(argv, argc, envp);
		executor(pipex, argv, envp);
		unlink(".heredocfile");
		// system("leaks peepex");
	}
	else
	{
		ft_putstr_fd("Wong number of arguments\n", 2);
		return (1);
	}
	return (0);
}
