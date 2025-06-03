/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:23:56 by jgossard          #+#    #+#             */
/*   Updated: 2025/06/02 12:14:25 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/**
 * @brief Types of redirection for input and output operations
 * 	@param REDIRECT_IN Input redirection '<'
 * 	@param REDIRECT_OUT Output redirection '>'
 * 	@param APPEND_OUT Append output '>>'
 * 	@param HEREDOC Heredoc redirection '<<'
 */
typedef enum e_redirection_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND_OUT,
	HEREDOC,
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type	type;
	char				*target;
}	t_redirection;

/**
 * @brief Token types for the lexical analyzer in the shell
 * 	@param TOKEN_WORD A normal word (e.g., command name or argument)
 * 	@param TOKEN_DOUBLE_QUOTED_WORD A double-quoted word
 * 	@param TOKEN_SINGLE_QUOTED_WORD A single-quoted word
 * 	@param TOKEN_PIPE Pipe character '|'
 * 	@param TOKEN_REDIRECT_IN Input redirection '<'
 * 	@param TOKEN_REDIRECT_OUT Output redirection '>'
 * 	@param TOKEN_APPEND_OUT Append output '>>'
 * 	@param TOKEN_HEREDOC Heredoc '<<'
 * 	@param TOKEN_LOGICAL_AND '&&'
 * 	@param TOKEN_LOGICAL_OR '||'
 * 	@param TOKEN_END_OF_LINE End of line
 * 	@param TOKEN_UNKNOWN Anything that doesn't match a specific token type
 */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_DOUBLE_QUOTED_WORD,
	TOKEN_SINGLE_QUOTED_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_LOGICAL_AND,
	TOKEN_LOGICAL_OR,
	TOKEN_PARENTHESIS_RIGHT,
	TOKEN_PARENTHESIS_LEFT,
	TOKEN_END_OF_LINE,
	TOKEN_UNKNOWN
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}	t_token;

typedef struct s_command
{
	char				**args;
	char				*command;
	t_redirection		*redirection;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char		*input;
	t_token		*tokens_list;
	t_command	*commands; // [cmd1, cmd2]
}	t_shell;

#endif
