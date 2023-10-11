/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_g_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <alierdemcerrah@student.42.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:12:52 by acerrah           #+#    #+#             */
/*   Updated: 2023/10/11 15:56:54 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_data *g_data;

/* handle_g_data function creates the global data structure and fills it with  */
/* the environment variables.                                                  */
/* ft_strdup_2d function duplicates an array of strings.                       */
char **ft_strdup_2d(char **str)
{
    int i = 0;
    char **rtn;

    while (str[i])
        i++;
    rtn = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (str[i])
    {
        rtn[i] = ft_strdup(str[i]);
        i++;
    }
    rtn[i] = NULL;
    return (rtn);
}

void handle_g_data(char **env)
{
    int i = 0;

    g_data = malloc(sizeof(t_data));
    g_data->env = dynarray_create();
    while (env[i])
    {
        dynarray_push(g_data->env, env[i]);
        i++;
    }
    g_data->exp = dynarray_create();
    i = 0;
    while (env[i])
    {
        dynarray_push(g_data->exp, ft_strjoin("declare -x ", env[i]));
        i++;
    }
    g_data->lex = dynarray_create();
    g_data->cmd = dynarray_create();
    g_data->redirections = malloc(sizeof(t_redirections));
    g_data->redirections->type = dynintarray_create();
    g_data->redirections->file = dynarray_create();
}