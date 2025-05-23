/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:23:56 by jgossard          #+#    #+#             */
/*   Updated: 2025/05/23 17:20:46 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_redirection_type
{
	REDIRECT_IN, //<
	REDIRECT_OUT, // >
	APPEND_OUT, // >>
	HEREDOC, // <<
}	t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type	type;
	char				*target;
}	t_redirection;

/**
 * @brief Token types for the lexical analyzer in the shell
 * 	@param WORD A normal word (e.g., command name or argument)
 * 	@param PIPE Pipe character '|'
 * 	@param REDIRECT_IN Input redirection '<'
 * 	@param REDIRECT_OUT Output redirection '>'
 * 	@param APPEND_OUT Append output '>>'
 * 	@param HEREDOC Heredoc '<<'
 * 	@param LOGICAL_AND '&&'
 * 	@param LOGICAL_OR '||'
 * 	@param END_OF_LINE End of line
 * 	@param UNKNOWN Anything that doesn't match a specific token type
 */
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND_OUT,
	HEREDOC,
	LOGICAL_AND,
	LOGICAL_OR,
	END_OF_LINE,
	UNKNOWN
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
}	t_token;

typedef struct s_command
{
	char			**args;
	char			*command;
	t_redirection	*redirection
}	t_command;


typedef struct s_shell
{
	char		*input;
	t_token		**tokens;
	t_command	**commands; // [cmd1, cmd2]
}	t_shell;

#endif
