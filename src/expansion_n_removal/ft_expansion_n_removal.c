/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_n_removal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:40:17 by mcamaren          #+#    #+#             */
/*   Updated: 2025/07/22 12:40:21 by mcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_debugging_print_tokens(t_shell *data, char *str)
{
	printf("-----------------%s-----------------\n", str);
	ft_print_tokens_list(data);
	printf("------------------------------------------\n");
}

// TODO: not clear what the function does
static void	ft_end_if_malloc_failure(char *prompt, t_token **token_list,
		t_shell *data, bool (*f)(t_token **, t_shell *))
{
	if (f && !f(token_list, data))
		return (free(prompt), ft_close_program(data, EXIT_FAILURE));
}


/*todo : remove prints*/
void	ft_expansion_n_removal(char *prompt, t_shell *data)
{
	ft_tokenizer(data->input, data);
	ft_debugging_print_tokens(data, "TOKENIZED");
	ft_end_if_malloc_failure(prompt, &data->tokens_list, data,
		ft_evaluate_var_expansion);
	ft_debugging_print_tokens(data, "EXPANDED");
	ft_end_if_malloc_failure(prompt, &data->tokens_list, data, ft_retokenize);
	ft_debugging_print_tokens(data, "RETOKENIZED");
	ft_end_if_malloc_failure(prompt, &data->tokens_list, data,
		ft_quote_removal);
	ft_debugging_print_tokens(data, "QUOTE REMOVAL");
}

