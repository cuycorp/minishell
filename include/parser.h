/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:00:21 by jgossard          #+#    #+#             */
/*   Updated: 2025/07/01 20:56:05 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

/* ########  PARSER PART  ######## */

t_ast_node		*ft_parser(t_token *token_list);
t_ast_node		*ft_parse_shell(t_token **token_list);
t_ast_node		*ft_parse_and_or_list(t_token **token_list);
t_ast_node		*ft_parse_subshell_group(t_token **token_list);
t_ast_node		*ft_parse_subshell(t_token **token_list);
t_ast_node		*ft_parse_pipeline(t_token **token_list);
t_ast_node		*ft_parse_pipeline_command(t_token **tokens);
t_ast_node		*ft_parse_simple_command(t_token **token_list);

char			*ft_parse_command_word(t_token **token_list);
t_redirection	*ft_parse_redirection(t_token **token_list);
char			*ft_parse_env_variable(t_token **token_list);

/* ########  AST TREE PART  ######## */

t_ast_node		*ft_create_ast_node(t_ast_node_type type);
t_ast_node		*ft_create_simple_command_node(t_command *command);
t_ast_node		*ft_create_redirection_node(t_redirection *redirection);
t_ast_node		*ft_add_ast_node(t_ast_node_type type, t_ast_node *left,
					t_ast_node *right);
t_ast_node_type	ft_get_ast_node_type(t_token_type type);

/* ########  Utils PART  ######## */

int				ft_count_arguments(t_token *token_list);
t_command		*ft_create_and_fill_command(t_token **tokens,
					bool *has_command);
bool			ft_extract_redirections(t_redirection **redirection_list,
					t_token **token_list, bool *has_redirection);
void			ft_advance_token(t_token **token_list);
void			ft_parse_error(const t_token *token, const char *msg);
bool			ft_match_token(t_token **token_list, t_token_type expected);
void			ft_print_ast_node(t_ast_node *node);
void			ft_print_in_tree_form(t_ast_node *node, int level);
#endif
