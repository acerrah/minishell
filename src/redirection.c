#include "../inc/minishell.h"

extern t_data *g_data;

/* types are as follows: */
/* 0: no redirection     */
/* 1: >                  */
/* 2: >>                 */
/* 3: <                  */
/* 4: <<                 */
/* 5: |                  */
char *next_arg_in_quote(char *str, int i)
{
    int j;
    
    if (str[i] == '\'')
    {
        i++;
        j = i;
        while (str[j] != '\'' && str[j] != '\0')
            j++;
        return (ft_substr(str, i, j - i));
    }
    else
    {
        i++;
        j = i;
        while (str[j] != '"' && str[j] != '\0')
            j++;
        return (ft_substr(str, i, j - i));
    }
}

char  *take_next_arg(char *str)
{
    int i;
    int j;

    i = 0;
    while(str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (NULL);
    if (str[i] == '\'' || str[i] == '"')
        return (next_arg_in_quote(str, i));
    else
    {
        j = i;
        while (str[j] != ' ' && str[j] != '\0' &&
			str[j] != '<' && str[j] != '>' && str[j] != '|')
            j++;
        return (ft_substr(str, i, j - i));
    }
}

char *last_arg_in_quote(char *str, int i, int j)
{
    if (str[i] == '\'')
    {
        i--;
        while (str[i] != '\'' && i != 0)
            i--;
        return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
    }
    else
    {
        i--;
        while (str[i] != '"' && i != 0)
            i--;
        return (ft_substr(str, i + 1, ft_strlen(str) - i - j));
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
    if (str[i] == '\'' || str[i] == '"')
        return (last_arg_in_quote(str, i, j));
    else
    {
        while (str[i] != ' ' && i != 0 &&
			str[i] != '<' && str[i] != '>' && str[i] != '|')
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
        str[i] = ' ';
        while (str[--i] != '\'' && i != -1)
            str[i] = ' ';
        str[i] = ' ';
    }
    else if (str[i] == '"')
    {
        str[i] = ' ';
        while (str[--i] != '"' && i != -1)
            str[i] = ' ';
        str[i] = ' ';
    }
    else
    {
        while (str[i] != ' ' && i != -1 && str[i] != '<' && str[i] != '>' && str[i] != '|')
            str[i--] = ' ';
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
        str[i] = ' ';
        while (str[++i] != '\'' && str[i] != '\0')
          str[i] = ' ';
        str[i] = ' ';
    }
    else if (str[i] == '"')
    {
        str[i] = ' ';
        while (str[i++] != '"' && str[i] != '\0')
            str[i] = ' ';
        str[i] = ' ';
    }
    else
    {
        while (str[i] != ' ' && str[i] != '\0' && str[i] != '<' && str[i] != '>' && str[i] != '|')
            str[i++] = ' ';
    }
}

int output(char *str, int j)
{
    if (str[j + 1] == '>')
    {
        dynintarray_push(g_data->redirections->type, REDIR_OUT_APPEND);
        dynarray_push(g_data->redirections->file,
            take_next_arg(&str[j + 2]));
        delete_next_arg(str, j + 2);
        str[j] = ' ';
        str[j + 1] = ' ';
    }
    else
    {
        str[j] = ' ';
        while (str[j] == ' ')
            j++;
        if (str[j] == '<' || str[j] == '>')
        {
            printf("minishell: syntax error near unexpected token `%c'\n", str[j]);
            return 258;
        }
        dynintarray_push(g_data->redirections->type, REDIR_OUT);
        dynarray_push(g_data->redirections->file,
            take_next_arg(&str[j]));
        delete_next_arg(str, j);
    }
    return 0;
}

int input(char *str, int j)
{
    if (str[j + 1] == '<')
    {
        dynintarray_push(g_data->redirections->type, REDIR_IN_HERE_DOC);
        dynarray_push(g_data->redirections->file,
        take_next_arg(&str[j + 2]));
        delete_next_arg(str, j + 2);
        str[j] = ' ';
        str[j + 1] = ' ';
    }
    else
    {
        str[j] = ' ';
        while (str[j] == ' ')
            j++;
        if (str[j] == '>' || str[j] == '<')
        {
            printf("minishell: syntax error near unexpected token `%c'\n", str[j]);
            return 258;
        }
        dynintarray_push(g_data->redirections->type, REDIR_IN);
        dynarray_push(g_data->redirections->file,
        take_next_arg(&str[j]));
        delete_next_arg(str, j);
    }
    return 0;
}

int redirections()
{
    int i = 0;
    int j = 0;
    bool in_single_quotes = false;
    bool in_double_quotes = false;
    char **str = g_data->lex->data;
    while (str[i])
    {
        while (str[i][j])
        {
            if (str[i][j] == '|' && !in_single_quotes && !in_double_quotes)
            {
                dynarray_push(g_data->redirections->file, "|");
                dynintarray_push(g_data->redirections->type, PIPE);
                break;
            }
            if (str[i][j] == '\'' && !in_double_quotes)
                in_single_quotes = !in_single_quotes;
            else if (str[i][j] == '"' && !in_single_quotes)
                in_double_quotes = !in_double_quotes;
            else if (str[i][j] == '>' && !in_single_quotes && !in_double_quotes)
            {                
                if (output(str[i], j) == 258)
                    return 258;
            }
            else if (str[i][j] == '<' && !in_single_quotes && !in_double_quotes)
            {
                if (input(str[i], j) == 258)
                    return 258;
            }
            j++;
        }
        j = 0;
        i++;
    }
    return 0;
}
