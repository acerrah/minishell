/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:13:05 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/15 11:04:26 by acerrah          ###   ########.fr       */
=======
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:28 by iremoztimur       #+#    #+#             */
/*   Updated: 2023/10/15 13:31:39 by iremoztimur      ###   ########.fr       */
>>>>>>> irem
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *g_data;

<<<<<<< HEAD

int main(int ac, char **av, char **env){

=======
int main(int ac, char **av, char **env)
{
>>>>>>> irem
    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    handle_g_data(env);
<<<<<<< HEAD
	loop();
    return 0;
}
=======
    lexer("ls -l \"xd|\" << a > b| cat -e << c", FALSE, FALSE, 0, 0);

	//char **command = ft_split("export*deneme=5", '*'); // working
	//char **command2 = ft_split("export*a=\" 3\"", '*'); // not working for env, showing double quotes
	//char **command1 = ft_split("unset*a", '*');
	char **command3 = ft_split("export*x=", '*');
	ft_export(command3);
	//ft_unset(command1);

	ft_export(ft_split("export", ' '));
	ft_env(ft_split("env", ' '));
	//ft_exit(ft_split("exit -1921839012839128", ' '));
}
>>>>>>> irem
