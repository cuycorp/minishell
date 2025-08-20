/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:23:56 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/20 15:45:16 by jgossard         ###   ########.fr       */
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
	int						heredoc_fd;
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
	// AST_SHELL,
	// AST_COMMAND_LINE,
	// AST_AND_OR_LIST,
	// AST_GROUPED_PIPELINE,
	// AST_ENV_VARIABLE,
	// AST_WORD,
	AST_LOGICAL_AND,
	AST_LOGICAL_OR,
	AST_PIPE,
	AST_REDIRECTION,
	AST_SIMPLE_COMMAND,
	AST_NONE,
}							t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type			type;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
	char 					*value;
	t_redirection 			*redirection_data;
	t_command 				*command_data;
}							t_ast_node;

typedef struct s_exec_context
{
	// pid_t	*pids;
	// int		last_pid;
	// int		pid_count;
	// int		command_count;
	int		input_fd;
	int		output_fd;
	int		last_exit_code;
}	t_exec_context;

typedef struct s_wildcard_context
{
	DIR				*directory;
	struct dirent	*entry;
	char			**matches;
	unsigned int	match_count;
	char			*pattern;
	char			*directory_part;
	char			*basename_part;
}	t_wildcard_context;

typedef struct s_shell
{
	char				*input;
	char				*prompt;
	char				**ev;
	char				**export;
	t_token				*tokens_list;
	t_ast_node			*ast_root;
	t_exec_context		*context;
	t_wildcard_context	*wildcard;
	int					exit_code;
	bool				has_raised_error;
	char				*error_message;
	t_redirection		*last_redirection;
}	t_shell;

#endif
