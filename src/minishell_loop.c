#include "../includes/executor.h"
#include "../includes/minishell.h"
#include "../includes/parser.h"
#include "../includes/tokenizer.h"

static t_ast	*handle_input(void)
{
	t_token	*tokens;
	t_token	*curr;
	t_ast	*ast;
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		exit(0);
	else if (*input)
		add_history(input);
	tokens = tokenize(input);
	if (!tokens)
		return (printf("minishell: tokenize error\n"), free(input), NULL);
	if (is_syntax_error(tokens))
		return (free_tokens(tokens), free(input), NULL);
	curr = tokens;
	while (curr)
	{
		printf("Token: type=%d, value='%s'\n", curr->type, curr->value);
		curr = curr->next;
	}
	ast = parse_tokens(tokens);
	free_tokens(tokens);
	return (ast);
}

void	minishell_loop(t_env *env_list)
{
	t_ast	*ast;

	while (1)
	{
		ast = handle_input();
		if (!ast)
			continue ;
		if (ast)
		{
			print_ast(ast, 2);
			execute_ast(ast, &env_list);
			free_ast(ast);
		}
		// to do execute ast
	}
}
