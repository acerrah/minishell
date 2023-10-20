/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:13:05 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/20 23:31:31 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *g_data;

int main(int ac, char **av, char **env){

	if (ac != 1 || av[1] != NULL || env[0] == NULL)
		return (0);
	handle_g_data(env);
	loop();
	return 0;
}
