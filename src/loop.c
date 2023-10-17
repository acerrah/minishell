#include "../inc/minishell.h"

extern t_data *g_data;

void loop_clear(char *input_str)
{
    int i;

    i = 0;
    free(input_str);
    if (g_data->lex)
    {
        dynarray_destroy(g_data->lex);
        g_data->lex = dynarray_create();
    }
    if (g_data->cmd)
    {
        while (i < g_data->line)
            dynarray_destroy(g_data->cmd[i++]);
        free(g_data->cmd);
    }
    if (g_data->redirections->type)
    {
        dynintarray_destroy(g_data->redirections->type);
        g_data->redirections->type = dynintarray_create();
        dynarray_destroy(g_data->redirections->file);
        g_data->redirections->file = dynarray_create();
    }
    if (g_data->fd)
    {
        while (i < g_data->line)
        {
            free(g_data->fd[IN]->arr);
            free(g_data->fd[OUT]->arr);
            i++;
        }
        free(g_data->fd[IN]);
        free(g_data->fd[OUT]);
        free(g_data->fd);
        g_data->fd = malloc(sizeof(t_dynintarray *) * 2);
        g_data->fd[IN] = dynintarray_create();
        g_data->fd[OUT] = dynintarray_create();
    }
}

void loop(void)
{
    char *input_str;

    while (true)
    {
        input_str = readline("minishell-0.2$ ");
        if (ft_strtrim(input_str, " ") == NULL)
            continue;
        add_history(input_str);
        if (lexer(input_str, false, false, 0, 0) != 0)
        {
            loop_clear(input_str);
            continue;
        }
        redirections();
        parser();
        //print command table and fd
		/*
        for (int i = 0; i < g_data->line; i++)
        {
            for (size_t j = 0; j < g_data->cmd[i]->size; j++)
                printf("'%s'\n", g_data->cmd[i]->data[j]);
            printf("fd[IN] = %d\n", g_data->fd[IN]->arr[i]);
            printf("fd[OUT] = %d\n", g_data->fd[OUT]->arr[i]);
        }*/
        //execute(command);
		loop_clear(input_str);
    }
}
