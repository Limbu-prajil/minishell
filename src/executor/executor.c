#include "../../includes/executor.h"


int is_builtin(const char *cmd)
{
    if (isstrequal(cmd, "echo") 
    || isstrequal(cmd, "cd") 
    || isstrequal(cmd, "pwd") 
    || isstrequal(cmd, "export") 
    || isstrequal(cmd, "unset")
    || isstrequal(cmd, "env")
    || isstrequal(cmd, "exit"))
        return (1);
    else
        return (0);
}

int execute_builtin(t_ast *node, t_env **env_list)
{
    (void)env_list;
    char **args;
    int status;

    args = node->args;
    status = 0;
    if (isstrequal(args[0], "echo"))
        status = builtin_echo(args);
    else if (isstrequal(args[0], "pwd"))
        status = builtin_pwd();
    else if (isstrequal(args[0], "cd"))
        status = builtin_cd(args, *env_list);
    else if (isstrequal(args[0], "env"))
        status = builtin_env(*env_list, args);
    else if (isstrequal(args[0], "export"))
        status = builtin_export(args, env_list);
    /* else if (isstrequal(args[0], "unset"))
        status = builtin_unset(args);
    else if (isstrequal(args[0], "exit"))
        status = builtin_exit(args);  */
    return (status);
}
void execute_ast(t_ast *ast, t_env **env_list)
{
    if (!ast)
        return ;
    if (ast->type == NODE_COMMAND)
    {
        if (!ast->args || !ast->args[0])
            return ;
        if (is_builtin(ast->args[0]))
        {
            execute_builtin(ast, env_list);
        }
        else
            return ;//execute_command(ast);
    }
}