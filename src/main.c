/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:13:05 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/11 15:17:19 by acerrah          ###   ########.fr       */
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
            else if (str[i][j] == '>' && !in_single_quotes && !in_double_quotes)
            //redirection handling
            //currently working on it
            j++;
        }
        i++;
    }
}


void loop(void)
{
    char *input_str;

    while (1)
    {
        input_str = readline("minishell-0.1$ ");
        if (ft_strtrim(input_str, " ") == NULL)
            continue;
        add_history(input_str);
        lexer(input_str, false, false, 0, 0);
        //redirections(command);
        //parser();
        //execute(command);
        free(input_str);
        dynarray_destroy(g_data->lex);
        g_data->lex = dynarray_create();
        //free(command);
    }
}

int main(int ac, char **av, char **env){

    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    handle_g_data(env);
    loop();
    return 0;
}