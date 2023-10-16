#include "../inc/minishell.h"

extern t_data *g_data;

/* pipe[2]: index 0 - fd_in, index 1 - fd_out. */ 
/*
typedef struct files
{
    int fd_in;
    int fd_out;
    int fd_err;
    int pipe[2];
} t_files;*/

//write me a function to take input from user as heredoc it will get input unless the key is given it will return fd of the file
int heredoc(char *str)
{
    int fd;
    char *line;
    char *tmp;

    fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(line, str) == 0)
        {
            free(line);
            break;
        }
        tmp = ft_strjoin(line, "\n");
        write(fd, tmp, ft_strlen(tmp));
        free(tmp);
        free(line);
    }
    close(fd);
    return (open("heredoc", O_RDONLY));
}

void swap(void *a, void *b)
{
    void *tmp;

    tmp = a;
    a = b;
    b = tmp;
}

int parser()
{
    //command table'a sırasıyla in, out, command, flags, args, NULL eklenir.
    //command table 2d dynamic string array olacak
    //her bir pipe bir line olarak alınacak
    
    size_t i;
    int j;

    i = 0;
    j = 0;
    if (g_data->redirections->file->size == 0)
    {
        dynintarray_push(g_data->fd[IN], STDIN);
        dynintarray_push(g_data->fd[OUT], STDOUT);
    }
    while (i < g_data->redirections->file->size)
    {
        if (g_data->redirections->type->arr[i] == PIPE)
        {
            if (g_data->fd[IN]->size < j + 1 && j != 0)
                dynintarray_push(g_data->fd[IN], -2);
            else if (g_data->fd[IN]->size < j + 1 && j == 0)
                dynintarray_push(g_data->fd[IN], STDIN);
            if (g_data->fd[OUT]->size < j + 1)
                dynintarray_push(g_data->fd[OUT], -2);
            dynintarray_push(g_data->fd[IN], -2);
            i++;
            j++;
            continue;
        }
        else if (g_data->redirections->type->arr[i] == REDIR_IN || g_data->redirections->type->arr[i] == REDIR_IN_HERE_DOC)
        {
            if (g_data->fd[IN]->size == j + 1 && g_data->redirections->type->arr[i] != REDIR_IN_HERE_DOC)
            {
                close(g_data->fd[IN]->arr[j]);
                dynintarray_pull(g_data->fd[IN], j);
            }
            if (g_data->redirections->type->arr[i] == REDIR_IN)
                dynintarray_push(g_data->fd[IN], open(g_data->redirections->file->data[i], O_RDONLY));
            else
            {
                close(g_data->fd[IN]->arr[j]);
                dynintarray_set(g_data->fd[IN], 0, heredoc(g_data->redirections->file->data[i]));
            }
        }
        else if (g_data->redirections->type->arr[i] == REDIR_OUT || g_data->redirections->type->arr[i] == REDIR_OUT_APPEND)
        {
            if (g_data->fd[OUT]->size == j + 1)
            {
                close(g_data->fd[OUT]->arr[j]);
                dynintarray_pull(g_data->fd[OUT], j);
            }
            if (g_data->redirections->type->arr[i] == REDIR_OUT)
                dynintarray_push(g_data->fd[OUT], open(g_data->redirections->file->data[i], O_WRONLY | O_CREAT | O_TRUNC, 0644));
            else
                dynintarray_push(g_data->fd[OUT], open(g_data->redirections->file->data[i], O_WRONLY | O_CREAT | O_APPEND, 0644));
        }
        if (i + 1 == g_data->redirections->file->size)
        {
            if (g_data->fd[OUT]->size < j + 1)
                dynintarray_push(g_data->fd[OUT], STDOUT);
        }
        i++;
    }
    i = 0;
    j = 0;
    while (i < g_data->lex->size)
    {
        if (ft_strtrim(g_data->lex->data[i], " ")[0] == '|')
            j++;
        i++;
    }
    g_data->line = j + 1;
    g_data->cmd = malloc(sizeof(t_dynarray *) * (j + 1) );
    i = 0;
    j = 0;
    //lexer'ın içindeki flag ve argümanları space göre parçalara ayır
    int in_single_quotes = false;
    int in_double_quotes = false;
    int k = 0;
    int l = 0;
    int m = 0;
    while (i < g_data->lex->size)
    {
        if (g_data->lex->data[i][0] == '|')
        {
            i++;
            continue;
        }
        g_data->lex->data[i] = ft_strtrim(g_data->lex->data[i], " ");
        while (g_data->lex->data[i][j])
        {
            if (g_data->lex->data[i][j] == '\'' && !in_double_quotes)
                in_single_quotes = !in_single_quotes;
            else if (g_data->lex->data[i][j] == '"' && !in_single_quotes)
                in_double_quotes = !in_double_quotes;
            else if (g_data->lex->data[i][j] == ' ' && !in_single_quotes && !in_double_quotes)
            {
                while (g_data->lex->data[i][j + 1] == ' ')
                    j++;
                g_data->lex->data[i][j] = '\0';
                j++;
                k++;
                continue;
            }
            if (g_data->lex->data[i][j + 1] == '\0')
                k++;
            j++;
        }
        g_data->cmd[m] = dynarray_create();
        j = 0;
        while (j < k)
        {
            dynarray_push(g_data->cmd[m], ft_strtrim(g_data->lex->data[i], " "));
            l += ft_strlen(g_data->lex->data[i]) + 1;
            g_data->lex->data[i] += ft_strlen(g_data->lex->data[i]) + 1;
            j++;
        }
        g_data->lex->data[i] -= l;
        l = 0;
        j = 0;
        k = 0;
        i++;
        m++;
    }
    return 0;
}

