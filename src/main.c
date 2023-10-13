/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:28 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 18:51:26 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *g_data;

int main(int ac, char **av, char **env)
{
    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    handle_g_data(env);
    lexer("ls -l \"xd|\" << a > b| cat -e << c", false, false, 0, 0);

	//char **command = ft_split("export*deneme=5", '*'); // working
	//char **command2 = ft_split("export*a=\" 3\"", '*'); // not working for env, showing double quotes
	//char **command1 = ft_split("unset*a", '*');
	char **command3 = ft_split("export*x=", '*');
	ft_export(command3);
	//ft_unset(command1);

	ft_export(ft_split("export", ' '));
	ft_env(ft_split("env", ' '), 0);
	//ft_exit(ft_split("exit -1921839012839128", ' '));
}
