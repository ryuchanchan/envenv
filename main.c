#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *expand_env(char *str)
{
    char *ptr;
    char *result;
    char *env_name;
    char *env_value;
    char *res_ptr;

    ptr = str;
    result = (char*)malloc(strlen(str) + 1);
    res_ptr = result;
    int i = 0;
    while (*ptr != 0)
    {
        if (*ptr == '$')
        {
            if (res_ptr[i++] == '\0')
            {
                perror("Non env");
                exit(1);
            }
            //環境変数名を取得してる
            env_name = res_ptr;
            ptr++;
            while (*ptr && (*ptr != ' ' && *ptr != '\t'))
            {
                res_ptr[i] = ptr[i];
                i++;
            }
            if (env_name != res_ptr)
            {
                env_value = getenv(env_name);
                if (env_name == NULL)
                {
                    perror("getenv");
                    exit(i);
                }
                if (env_value)
                {
                    // 環境変数の値で置換する
                    while (*env_value)
                    {
                        res_ptr[i] = env_value[i];
                        i++;
                    }
                }
            }
        }
        else
            res_ptr[i++] = *ptr++;//文字列出力処理
    }
    return result;
}


int main(int argc, char **argv, char **envp)
{
    char *str;
    char *args[3];
    int i;

    i = 1;
    while (i < argc)
    {
        str = expand_env(argv[i]);
        args[0] = "/bin/echo";
        args[1] = str;
        args[2] = NULL;
        execve(args[0], args, envp);
        // printf("%s ", str);
        free(str);
        i++;
    }
    // printf("\n");
    return 0;
}
