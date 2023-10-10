#include "../inc/minishell.h"

extern t_data *g_data;

/* */
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
    g_data->lex = dynarray_create();
    g_data->cmd = dynarray_create();
    g_data->redirections = dynarray_create();
    g_data->heredocs = dynarray_create();
}