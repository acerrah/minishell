/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:13:05 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/11 16:48:19 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data *g_data;
/* types are as follows: */
/* 0: no redirection     */
/* 1: >                  */
/* 2: >>                 */
/* 3: <                  */
/* 4: <<                 */

char  *take_next_arg(char *str)
{
    int i;
    int j;

    i = 0;
    while(str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (NULL);
    if (str[i] == '\'')
    {
        i++;
        j = i;
        while (str[j] != '\'' && str[j] != '\0')
            j++;
        return (ft_substr(str, i, j - i));
    }
    else if (str[i] == '"')
    {
        i++;
        j = i;
        while (str[j] != '"' && str[j] != '\0')
            j++;
        return (ft_substr(str, i, j - i));
    }
    else
    {
        j = i;
        while (str[j] != ' ' && str[j] != '\0' && str[j] != '<' && str[j] != '>' && str[j] != '|')
            j++;
        return (ft_substr(str, i, j - i));
    }
}

char *take_last_arg(char *str, int i)
{
    int j;

    j = ft_strlen(str) - i;
    while (str[i] == ' ')
        i--;
    if (i == -1)
        return (NULL);
    if (str[i] == '\'')
    {
        i--;
        while (str[i] != '\'' && i != -1)
            i--;
        return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
    }
    else if (str[i] == '"')
    {
        i--;
        while (str[i] != '"' && i != -1)
            i--;
        return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
    }
    else
    {
        while (str[i] != ' ' && i != -1 && str[i] != '<' && str[i] != '>' && str[i] != '|')
            i--;
        return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
    }
    
}

void delete_last_arg(char *str, int i)
{
    while (str[i] == ' ')
        i--;
    if (i == -1)
        return;
    if (str[i] == '\'')
    {
        i--;
        while (str[i] != '\'' && i != -1)
            i--;
        str[i] = ' ';
    }
    else if (str[i] == '"')
    {
        i--;
        while (str[i] != '"' && i != -1)
            i--;
        str[i] = ' ';
    }
    else
    {
        while (str[i] != ' ' && i != -1 && str[i] != '<' && str[i] != '>' && str[i] != '|')
            i--;
        str[i] = ' ';
    }
}

void delete_next_arg(char *str, int i)
{
    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return;
    if (str[i] == '\'')
    {
        i++;
        while (str[i] != '\'' && str[i] != '\0')
            i++;
        str[i] = ' ';
    }
    else if (str[i] == '"')
    {
        i++;
        while (str[i] != '"' && str[i] != '\0')
            i++;
        str[i] = ' ';
    }
    else
    {
        while (str[i] != ' ' && str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != '|')
            i++;
        str[i] = ' ';
    }
}

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
            if (str[i][j] == '|' && !in_single_quotes && !in_double_quotes)
            {
                dynarray_push(g_data->redirections->file, "|");
                dynintarray_push(g_data->redirections->type, 0);
                break;
            }
            if (str[i][j] == '\'' && !in_double_quotes)
                in_single_quotes = !in_single_quotes;
            else if (str[i][j] == '"' && !in_single_quotes)
                in_double_quotes = !in_double_quotes;
            else if (str[i][j] == '>' && !in_single_quotes && !in_double_quotes)
            {
                if (str[i][j + 1] == '>')
                {
                    dynintarray_push(g_data->redirections->type, 2);
                    dynarray_push(g_data->redirections->file,
                        take_last_arg(str[i], j - 2));
                    delete_last_arg(str[i], j - 1);
                    str[i][j] = ' ';
                    str[i][j + 1] = ' ';
                }
                else
                {
                    dynintarray_push(g_data->redirections->type, 1);
                    dynarray_push(g_data->redirections->file,
                        take_last_arg(str[i], j - 1));
                    delete_last_arg(str[i], j - 1);
                    str[i][j] = ' ';
                }
            }
            else if (str[i][j] == '<' && !in_single_quotes && !in_double_quotes)
            {
                if (str[i][j + 1] == '<')
                {
                    dynintarray_push(g_data->redirections->type, 4);
                    dynarray_push(g_data->redirections->file,
                        take_next_arg(&str[i][j + 2]));
                    delete_next_arg(str[i], j + 2);
                    str[i][j] = ' ';
                    str[i][j + 1] = ' ';
                }
                else
                {
                    dynintarray_push(g_data->redirections->type, 3);
                    dynarray_push(g_data->redirections->file,
                        take_next_arg(&str[i][j + 1]));
                    delete_next_arg(str[i], j + 1);
                    str[i][j] = ' ';
                }
            }
            j++;
        }
        j = 0;
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
        redirections(g_data->lex->data);
        for (int i = 0; g_data->lex->data[i]; i++)
           printf("%s\n", g_data->lex->data[i]);
        for (int i = 0; g_data->redirections->file->data[i]; i++)
            printf("%s\n", g_data->redirections->file->data[i]);
        for (int i = 0; i < g_data->redirections->type->size; i++)
            printf("%d\n", g_data->redirections->type->arr[i]);
        //parser();
        //execute(command);
        free(input_str);
        dynarray_destroy(g_data->lex);
        g_data->lex = dynarray_create();
        dynarray_destroy(g_data->cmd);
        g_data->cmd = dynarray_create();
        dynintarray_destroy(g_data->redirections->type);
        g_data->redirections->type = dynintarray_create();
        dynarray_destroy(g_data->redirections->file);
        g_data->redirections->file = dynarray_create();
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