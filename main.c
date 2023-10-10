#include "minishell.h"

t_data *global_var;

void write_environment(void)
{
	int i;

	i = 0;
	while (global_var->env[i])
		printf("%s\n", global_var->env[i++]);
}

void ft_env(char **command, int flag)
{
	int i;

	i = 1;
	if (command[i] == 0 && flag == 0)
		write_environment();
}

int len_env(char **environment)
{
	int i;

	i = 0;
	while (environment[i])
		i++;
	return (i);
}

int main(int argc, char **av, char **env)
{
    if (!argc || !av || !env)
        return (0);
    //copy env into global_var->env
    global_var = (t_data *)malloc(sizeof(t_data));
    global_var->env = ft_calloc(sizeof(char *), len_env(env) + 1);
    int i = 0;
    while (env[i])
    {
        global_var->env[i] = ft_strdup(env[i]);
        i++;
    }
    ft_env(av, 0);

    return (0);
}

