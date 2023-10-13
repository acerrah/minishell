#include "../inc/minishell.h"

t_data *g_data;

int main(int ac, char **av, char **env)
{

    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    handle_g_data(env);
    lexer("ls -l \"xd|\" << a > b| cat -e << c", false, false, 0, 0);

	char **command = ft_split("export*a=' 3'", '*');
	char **command1 = ft_split("unset*a", '*');
	ft_export(command); // quote doesn't work
	ft_unset(command1); // doesn't work

	ft_env(ft_split("env", ' '), 0);
	//ft_export(ft_split("export", ' '));
}
