#include "minishell.h"

//global data
typedef struct s_data
{
    char **env;
    char **path;
    char **cmd;
    char **args;
    char **redirections;
    char **heredocs;
} t_data;

t_data data;

//lexer that splits the input string into tokens based on pipes and quotes
char **lexer(char *input_str) {
    
    bool in_single_quotes = false;
    bool in_double_quotes = false;
    int last_pipe = 0;
    int pipe_count = 0;
    int i = 0;
    char **rtn;

    //kaç tane pipe var
    while (input_str[i])
    {
        if (input_str[i] == '|' && !in_single_quotes && !in_double_quotes)
            pipe_count++;
        else if (input_str[i] == '\'' && !in_double_quotes) 
            in_single_quotes = !in_single_quotes;

        else if (input_str[i] == '"' && !in_single_quotes)
            in_double_quotes = !in_double_quotes;
        i++;
    }
    //reset quotes and i
    in_single_quotes = false;
    in_double_quotes = false;
    i = 0;
    //  2 * pipe sayısı + 2 yer çünkü pipelar için ayrı bir yer,
    // stringler için ayrı bir yer, NULL için ayrı bir yer açıcaz
    //örn: "ls -l | cat -e" -> <"ls -l">  <"|">  <"cat -e"> <"\0">
    rtn = malloc(sizeof(char *) * (pipe_count * 2 + 2));
    //pipe count sıfırlayıp kullan ki daha az variable kullanalım
    pipe_count = 0;
    while (input_str[i])
    {
        //pipe'taysak aynı zamanda quote içinde değilsek
        if (input_str[i] == '|' && !in_single_quotes && !in_double_quotes)
        {
            //önceki pipe'tan şuanki pipe'a kadar olan kısmı al
            rtn[pipe_count] = ft_substr(input_str, last_pipe, i - last_pipe);
            pipe_count++;
            //pipe'ın kendisini de al
            rtn[pipe_count] = ft_substr(input_str, i, 1);
            pipe_count++;
            //son pipe'ı da güncelle
            //+1 çünkü substr başlangıç noktaları pipedan sonraki karakterden başlıyor
            last_pipe = i + 1;
        }
        //double quote içinde değilsek ve single quote'a denk geldiyse
        else if (input_str[i] == '\'' && !in_double_quotes) 
            in_single_quotes = !in_single_quotes;
        //single quote içinde değilsek ve double quote'a denk geldiyse
        else if (input_str[i] == '"' && !in_single_quotes)
            in_double_quotes = !in_double_quotes;
        //son karaktere geldiysek
        else if (input_str[i + 1] == '\0')
        {
            //son pipe'tan sona kadar olan kısmı al
            rtn[pipe_count] = ft_substr(input_str, last_pipe, i + 1 - last_pipe);
            pipe_count++;
            //NULL'ı da al
            rtn[pipe_count] = NULL;    
        }
        i++;
    }
    return (rtn);
}

//handling redirections and heredocs
void redirections(char **str)
{
    int i = 0;
    int j = 0;
    int h = 0;
    int r = 0;
    while (str[i])
    {
        while (str[i][j])
        {
            if (str[i][j] == '>' || str[i][j] == '<')
            {
                if (str[i][j + 1] == str[i][j])
                {
                    //heredoc
                    if (str[i][j + 2] != '\"' && str[i][j + 2] != '\'')
                        data.heredocs[h] = ft_split(ft_substr(str[i], j + 2, ft_strlen(str[i]) - j - 2), ' ')[0];
                    else
                    {
                        if (str[i][j + 2] == '\"')
                            data.heredocs[h] = ft_split(ft_substr(str[i], j + 3, ft_strlen(str[i]) - j - 3), '\"')[0];
                        else
                            data.heredocs[h] = ft_split(ft_substr(str[i], j + 3, ft_strlen(str[i]) - j - 3), '\'')[0];
                    }
                    h++;
                }
                else
                {
                    //redirection
                    if (str[i][j + 1] != '\"' && str[i][j + 1] != '\'')
                        data.redirections[r] = ft_split(ft_substr(str[i], j + 1, ft_strlen(str[i]) - j - 1), ' ')[0];
                    else
                    {
                        if (str[i][j + 1] == '\"')
                            data.redirections[r] = ft_split(ft_substr(str[i], j + 2, ft_strlen(str[i]) - j - 2), '\"')[0];
                        else
                            data.redirections[r] = ft_split(ft_substr(str[i], j + 2, ft_strlen(str[i]) - j - 2), '\'')[0];
                    }
                    r++;
                }
            }
            j++;
        }
        i++;
    }
}

//strdup but for 2d arrays
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

t_data dup_env(char **env)
{
    t_data data;

    data.env = ft_strdup_2d(env);
    data.path = NULL;
    data.cmd = NULL;
    data.args = NULL;
    data.redirections = NULL;
    data.heredocs = NULL;
    return (data);
}

int main(int ac, char **av, char **env){

    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    data = dup_env(env);
    //lexer test
    char **test = lexer("ls -l | cat -e");
    for(int i = 0; test[i] != NULL; i++){
        char **splt = ft_split(test[i], ' ');
        for(int j = 0; splt[j] != NULL; j++){
            printf("'%s'\n", splt[j]);
        }
    }

    return 0;
}