/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:23:56 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 14:35:27 by jgossard         ###   ########.fr       */
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
	UNKNOWN,
}							t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		type;
	char					*target;
	struct s_redirection	*next;
}							t_redirection;

typedef enum e_quotes
{
	NONE,
	SINGLE,
	DOUBLE,

}							t_quotes;

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
 * 	@param TOKEN_PARENTHESIS_RIGHT Right parenthesis ')'
 *	@param TOKEN_PARENTHESIS_LEFT Left parenthesis '('
 *	@param TOKEN_EXPANSION Word starting with '$' for variable expansion
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
	TOKEN_EXPANSION,
	TOKEN_END_OF_LINE,
	TOKEN_UNKNOWN
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	struct s_token			*next;
}							t_token;

typedef struct s_command
{
	char					**args;
	char					*name;
	t_redirection			*redirection;
}							t_command;

typedef enum e_ast_node_type
{
	AST_SHELL,
	AST_COMMAND_LINE,
	AST_AND_OR_LIST,
	AST_LOGICAL_OR,
	AST_LOGICAL_AND,
	AST_PIPE,
	AST_SIMPLE_COMMAND,
	AST_GROUPED_PIPELINE,
	AST_REDIRECTION,
	AST_ENV_VARIABLE,
	AST_WORD,
	AST_NONE,
}							t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type			type;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
	char *value;                     // to keep?
	t_redirection *redirection_data; // to keep or update with another one?
	t_command *command_data;         // to keep or update with another one?
}							t_ast_node;
typedef struct s_shell
{
	char					*input;
	int						exit_code;
	char					**ev;
	char					**export;
	t_token					*tokens_list;
	struct s_ast_node		*ast_root;
}							t_shell;

#endif
