/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgossard <jgossard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:19:47 by jgossard          #+#    #+#             */
/*   Updated: 2025/08/19 18:18:48 by jgossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/* Expansion */

bool	ft_expansion_n_removal(t_shell *data);
bool	ft_retokenize(t_shell *data);

bool	ft_evaluate_var_expansion(t_token **token_list, t_shell *data);
char	*ft_expand_var(char *var_name, t_shell *data);
char	*ft_fill_expanded_variables(char *str, t_shell *data);
char	*ft_handle_dollar_cases(char *str, int *i, char *final, t_shell *data);
char	*ft_extract_single_quoted_str(char *str, int *i);
char	*ft_locate_var(char *str, int *i);
char	*ft_handle_double_quotes(char *str, int *i, char *final, t_shell *data);
char	*ft_append_char(char *str, char c);
bool	ft_is_valid_expansion_start(char c);

/* Quote Removal */

char	*ft_handle_word_quotes(char *str);
bool	ft_quote_removal(t_token **token_list);

/* Quote Removal for Heredoc */

char	*ft_char_2_str(char c); // utils
char	*ft_expand_heredoc_delimiter(char *str, t_token_type type);
bool	ft_is_valid_delimiter_token(t_token_type type);
char	*ft_remove_quote(char *str, char quote);
char	*ft_remove_quotes_of_token_word(char *str);

/* WILDCARD */

char	**ft_resolve_wildcard_pattern(const char *pattern, t_shell *data);
bool	ft_append_to_string_array(char ***array, unsigned int *length,
			const char *str);
bool	ft_check_wildcard_pattern(const char *pattern, const char *str);
bool	ft_expand_wildcards_in_token_list(t_token **tokens, t_shell *data);
t_token	*ft_replace_current_token_with_matches(t_token *current,
			char **matches);
bool	ft_expand_wildcard_for_redirection(t_token *current, t_shell *data);
bool	ft_process_entry(t_wildcard_context *context);

#endif
