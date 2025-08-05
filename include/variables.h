/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:37:20 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/01 10:48:38 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

extern int	g_exit_code;

/* PROMPT */

# define PROMPT ":Oh-My-Shell >$ "

/* BUILT-INS Variable */

# define ECHO_BUILTIN "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

/* Command Operator */

# define PIPE '|'
# define LOGICAL_OR "||"
# define AMPERSAND_OPERATOR '&'
# define LOGICAL_AND "&&"
# define INPUT_REDIRECT '<'
# define OUTPUT_REDIRECT '>'
# define HERE_DOC "<<"
# define OUTPUT_APPEND ">>"
# define EQUAL_SIGN '='
# define SLASH_CHARACTER '/'
# define SLASH_STRING "/"

/* Variables */

# define PATH "PATH"
# define EQUAL_SIGN_LEN 1

/* Pipe end code */

# define READ_END 0
# define WRITE_END 1

/* FILE PERMISSION */
// Standard file permissions (0644 or rw-r--r--)
# define STANDARD_FILE_PERMISSIONS 0644

/* EXIT CODE */

# define EXIT_PERMISSION_DENIED 126
# define EXIT_COMMAND_NOT_FOUND 127

#endif
