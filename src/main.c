/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:13:05 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/10 22:13:06 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *g_data;

void redirections(char **str)
{
    int i = 0;
    int j = 0;
    bool in_single_quotes = false;
    bool in_double_quotes = false;
    while (str[i])
    {
        while (str[i][j])
        {
            if (str[i][j] == '\'' && !in_double_quotes)
                in_single_quotes = !in_single_quotes;
            else if (str[i][j] == '"' && !in_single_quotes)
                in_double_quotes = !in_double_quotes;
            //redirection handling
            //currently working on it
            j++;
        }
        i++;
    }
}

int main(int ac, char **av, char **env){

    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    handle_g_data(env);
    lexer("ls -l \"xd|\" << a > b| cat -e << c", false, false, 0, 0);
    int i = 0;
    while (g_data->exp->data[i])
    {
        printf("%s\n", g_data->exp->data[i]);
        i++;
    }
    return 0;
}