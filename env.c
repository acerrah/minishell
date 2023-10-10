#include "minishell.h"

t_data *global_var;

void write_environment(void)
{
	int i;

	i = 0;
	while (global_var->env[i])
		printf("%s", global_var->env[i++]);
}

void ft_env(char **command, int flag)
{
	int i;

	i = 1;
	if (command[i] == 0 && flag == 0)
		write_environment();
}
