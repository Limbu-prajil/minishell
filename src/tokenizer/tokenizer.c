#include "../../includes/tokenizer.h"
#include "../../includes/env.h"

static void	handle_spec_or_word(const char *input, size_t *i, t_token **tokens)
{
	if (ft_isschar(input[*i]))
		handle_special(input, i, tokens);
	else
		handle_word(input, i, tokens);
	(*i)++;
}

static int	handle_quotes(const char *input, size_t *i, t_token **tokens)
{
	if (input[*i] == '\'')
	{
		if (!handle_single_quote(input, i, tokens))
		{
			free_tokens(*tokens);
			return (0);
		}
	}
	else if (input[*i] == '"')
	{
		if (!handle_double_quote(input, i, tokens))
		{
			free_tokens(*tokens);
			return (0);
		}
	}
	return (1);
}

///helper slice for var expansion///

static char *slice(int i, char *str)
{
    int j = i;
    char *res;
    int len;
    while (str[j])
    {
        len++;
        j++;
    }
    res = malloc(len + 1);
    j = 0;
    while(str[i])
    {
        res[j] = str[i];
        j++;
        i++;
    }
    res[j] = '\0';
    return res;
}
////////////

static void	handle_normal_word(const char *input, size_t *i, t_token **tokens, t_env *env_list)
{
	size_t	start = *i;
	char	*token_val;
	char	quote;

	while (input[*i] && !ft_isspace(input[*i]))
	{
		if (input[*i] == '=' && (input[*i + 1] == '"' || input[*i + 1] == '\''))
		{
			quote = input[*i + 1];
			*i += 2;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] == quote)
				(*i)++;
			break;
		}
		(*i)++;
	}
	/////////////////////handle $sihn expansion/////////////////////
	token_val = ft_strndup(&input[start], *i - start);
	printf("\n\n\n");
	printf("token_val: %s\n", token_val);
	int j = 0;
	//int k = 0;
	while (token_val[j])
	{
		if (token_val[j] == '$')
			break;
		j++;
	}
	j++;
	printf("index j: %d", j);
	char *key = slice(j, token_val);
	printf("key: %s and value: %s\n", key, get_env_value(env_list, key));
	if (!get_env_value(env_list, key))
		add_token(tokens, create_token(TOKEN_WORD, token_val));
	else
		add_token(tokens, create_token(TOKEN_WORD, get_env_value(env_list, key)));
	free(token_val);
}

t_token	*tokenize(const char *input, t_env *env_list)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (!ft_isschar(input[i]) && input[i] != '\'' && input[i] != '"')
			handle_normal_word(input, &i, &tokens, env_list);
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (!handle_quotes(input, &i, &tokens))
				return (NULL);
		}
		else
			handle_spec_or_word(input, &i, &tokens);
	}
	return (tokens);
}
