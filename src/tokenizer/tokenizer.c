#include "../../includes/tokenizer.h"

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

static void	handle_normal_word(const char *input, size_t *i, t_token **tokens)
{
	size_t	start = *i;
	char	*val;
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
	val = ft_strndup(&input[start], *i - start);
	add_token(tokens, create_token(TOKEN_WORD, val));
	free(val);
}

t_token	*tokenize(const char *input)
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
			handle_normal_word(input, &i, &tokens);
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
