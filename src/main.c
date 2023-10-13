/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:28 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/13 16:27:56 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_exit(ft_split("exit -1921839012839128", ' '));
}
