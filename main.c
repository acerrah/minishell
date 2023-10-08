#include "minishell.h"

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

int main(int ac, char **av, char **env){

    if (ac != 1 || av[1] != NULL || env[0] == NULL)
        return (0);

    //lexer
    char **test = lexer("ls -l | cat -e");
    for(int i = 0; test[i] != NULL; i++){
        char **splt = ft_split(test[i], ' ');
        for(int j = 0; splt[j] != NULL; j++){
            printf("'%s'\n", splt[j]);
        }
    }

    return 0;
}