#include "minishell.h"

int ft_pwd(void)
{
	char buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
	{
		ft_putendl_fd(buff, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
