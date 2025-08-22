################################# DIRECTORIES ##################################
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
LIB_DIR = lib

################################## LIBRAIRIES ##################################
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_STATIC_LIB = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = $(LIB_DIR)/ft_printf
FT_PRINTF_STATIC_LIB = $(FT_PRINTF_DIR)/libftprintf.a

GNL_DIR = $(LIB_DIR)/get_next_line
GNL_STATIC_LIB = $(GNL_DIR)/libftgnl.a

LIBS =	$(FT_PRINTF_STATIC_LIB) \
		$(GNL_STATIC_LIB) \
		$(LIBFT_STATIC_LIB)

############################### COMPILER & FLAGS ###############################
CC = cc
IFLAGS =	-I $(LIBFT_DIR)/include \
			-I $(FT_PRINTF_DIR)/include \
			-I $(GNL_DIR)/include \
			-I $(INCLUDE_DIR)
LDFLAGS = -lreadline -lncurses
GFLAG = -g3
CFLAGS = -Wall -Werror -Wextra $(IFLAGS)

############################# INPUT & OBJECT FILES #############################
SRC_FILES = ${SRC_DIR}/shell/ft_handle_history.c \
${SRC_DIR}/shell/ft_handle_shell.c \
${SRC_DIR}/shell/ft_process_input.c \
${SRC_DIR}/shell/ft_reset_shell.c \
${SRC_DIR}/shell/ft_set_prompt.c \
${SRC_DIR}/shell/ft_shell_loop.c \
${SRC_DIR}/utils/memory/ft_close_program.c \
${SRC_DIR}/utils/memory/ft_free_command.c \
${SRC_DIR}/utils/memory/ft_free_redirection.c \
${SRC_DIR}/utils/memory/ft_free_ast_tree.c \
${SRC_DIR}/utils/memory/ft_close_heredoc_fd.c \
${SRC_DIR}/utils/memory/ft_free_wildcard_context.c \
${SRC_DIR}/utils/memory/ft_free_exec_context.c \
${SRC_DIR}/utils/memory/ft_safe_close_and_reset_fd.c \
${SRC_DIR}/utils/memory/ft_clear_memory.c \
${SRC_DIR}/utils/memory/ft_free_tree.c \
${SRC_DIR}/utils/validation/ft_validate_args.c \
${SRC_DIR}/utils/validation/ft_len_table.c \
${SRC_DIR}/utils/debugging/ft_print_table.c \
${SRC_DIR}/utils/string/ft_strings_utils.c \
${SRC_DIR}/utils/token/ft_stringify_token_type.c \
${SRC_DIR}/utils/token/ft_token_type_utils.c \
${SRC_DIR}/utils/token/ft_stringify_node_type.c \
${SRC_DIR}/utils/token/ft_stringify_redirection_type.c \
${SRC_DIR}/utils/environment/ft_get_env_value.c \
${SRC_DIR}/utils/environment/ft_split_env_value.c \
${SRC_DIR}/utils/ft_utils.c \
${SRC_DIR}/utils/system/ft_get_basename_part.c \
${SRC_DIR}/utils/system/ft_get_directory_part.c \
${SRC_DIR}/builtins/function_export/ft_print_export.c \
${SRC_DIR}/builtins/function_export/ft_replace_var_definition.c \
${SRC_DIR}/builtins/function_export/ft_evaluate_var_creation.c \
${SRC_DIR}/builtins/function_export/ft_function_export.c \
${SRC_DIR}/builtins/function_export/ft_is_valid_var_name.c \
${SRC_DIR}/builtins/function_export/ft_set_var_definition.c \
${SRC_DIR}/builtins/function_unset/function_unset.c \
${SRC_DIR}/builtins/function_unset/ft_unset_var.c \
${SRC_DIR}/builtins/function_cd/ft_save_wd.c \
${SRC_DIR}/builtins/function_cd/ft_update_path.c \
${SRC_DIR}/builtins/function_cd/function_cd.c \
${SRC_DIR}/builtins/function_cd/get_new_dir.c \
${SRC_DIR}/builtins/function_env.c \
${SRC_DIR}/builtins/function_echo.c \
${SRC_DIR}/builtins/ft_validate_command.c \
${SRC_DIR}/builtins/function_exit/ft_atoll.c \
${SRC_DIR}/builtins/function_exit/function_exit.c \
${SRC_DIR}/builtins/function_pwd.c \
${SRC_DIR}/expansion_n_removal/quote_removal/ft_quote_removal.c \
${SRC_DIR}/expansion_n_removal/quote_removal/ft_quote_removal_heredoc.c \
${SRC_DIR}/expansion_n_removal/quote_removal/here_doc/ft_char_2_str.c \
${SRC_DIR}/expansion_n_removal/quote_removal/here_doc/ft_expand_heredoc_delimiter.c \
${SRC_DIR}/expansion_n_removal/quote_removal/here_doc/ft_is_valid_delimiter_token.c \
${SRC_DIR}/expansion_n_removal/quote_removal/here_doc/ft_remove_quote.c \
${SRC_DIR}/expansion_n_removal/quote_removal/here_doc/ft_remove_quotes_of_token_word.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_locate_var.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_evaluate_var_expansion.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_append_char.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_expand_var.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_fill_expanded_variables.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_handle_dollar_cases.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_handle_double_quotes.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_handle_single_quote.c \
${SRC_DIR}/expansion_n_removal/expansion/ft_is_valid_start.c \
${SRC_DIR}/expansion_n_removal/ft_expansion_n_removal.c \
${SRC_DIR}/expansion_n_removal/ft_retokenize.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_append_to_string_array.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_check_wildcard_pattern.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_expand_wildcard_for_redirection.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_process_entry.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_replace_current_token_with_matches.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_resolve_wildcard_pattern.c \
${SRC_DIR}/expansion_n_removal/wildcard/ft_expand_wildcards_in_token_list.c \
${SRC_DIR}/initializer/ft_create_command.c \
${SRC_DIR}/initializer/ft_create_redirection.c \
${SRC_DIR}/initializer/ft_create_wildcard_context.c \
${SRC_DIR}/initializer/ft_create_exec_context.c \
${SRC_DIR}/initializer/ft_init_shell.c \
${SRC_DIR}/lexer/token/ft_add_token.c \
${SRC_DIR}/lexer/token/ft_add_token_from_range.c \
${SRC_DIR}/lexer/token/ft_free_tokens_list.c \
${SRC_DIR}/lexer/token/ft_print_token_list.c \
${SRC_DIR}/lexer/token/ft_create_token.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_single_quote.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_end_of_line.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_log_operator.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_parenthesis.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_redirection.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_unknown.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_mixed_word.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_semicolon.c \
${SRC_DIR}/lexer/tokenize/ft_tokenize_expansion.c \
${SRC_DIR}/lexer/ft_verify_balanced_quotes.c \
${SRC_DIR}/lexer/ft_tokenizer.c \
${SRC_DIR}/parser/ast_tree/ft_create_ast_node.c \
${SRC_DIR}/parser/ast_tree/ft_create_redirection_node.c \
${SRC_DIR}/parser/ast_tree/ft_create_simple_command_node.c \
${SRC_DIR}/parser/ast_tree/ft_get_ast_node_type.c \
${SRC_DIR}/parser/ast_tree/ft_add_ast_node.c \
${SRC_DIR}/parser/ft_parser.c \
${SRC_DIR}/parser/parser_rule/ft_parse_command_word.c \
${SRC_DIR}/parser/parser_rule/ft_parse_env_variable.c \
${SRC_DIR}/parser/parser_rule/ft_parse_redirection.c \
${SRC_DIR}/parser/parser_rule/ft_parse_shell.c \
${SRC_DIR}/parser/parser_rule/ft_parse_subshell.c \
${SRC_DIR}/parser/parser_rule/ft_parse_subshell_group.c \
${SRC_DIR}/parser/parser_rule/ft_parse_and_or_list.c \
${SRC_DIR}/parser/parser_rule/ft_parse_pipeline_command.c \
${SRC_DIR}/parser/parser_rule/ft_parse_pipeline.c \
${SRC_DIR}/parser/parser_rule/ft_parse_simple_command.c \
${SRC_DIR}/parser/utils/ft_count_arguments.c \
${SRC_DIR}/parser/utils/ft_create_and_fill_command.c \
${SRC_DIR}/parser/utils/ft_extract_redirections.c \
${SRC_DIR}/parser/utils/ft_parser_utils.c \
${SRC_DIR}/parser/utils/ft_append_remaining_arguments.c \
${SRC_DIR}/exec/builtins/ft_is_child_builtin.c \
${SRC_DIR}/exec/builtins/ft_is_parent_builtin.c \
${SRC_DIR}/exec/builtins/ft_exec_child_builtin.c \
${SRC_DIR}/exec/builtins/ft_exec_parent_builtin.c \
${SRC_DIR}/exec/errors/ft_error_failed_to_pipe.c \
${SRC_DIR}/exec/errors/ft_error_failed_waitpid.c \
${SRC_DIR}/exec/errors/ft_error_command_not_found.c \
${SRC_DIR}/exec/errors/ft_error_failed_to_fork.c \
${SRC_DIR}/exec/execution/ft_exec_node_recursive.c \
${SRC_DIR}/exec/execution/ft_exec_external_command.c \
${SRC_DIR}/exec/execution/ft_exec_heredoc.c \
${SRC_DIR}/exec/execution/ft_exec_logical_and.c  \
${SRC_DIR}/exec/execution/ft_exec_logical_or.c \
${SRC_DIR}/exec/execution/ft_exec_pipe_node.c \
${SRC_DIR}/exec/execution/ft_exec_redirections.c \
${SRC_DIR}/exec/execution/ft_exec_simple_command.c  \
${SRC_DIR}/exec/io/ft_prepare_command_input.c \
${SRC_DIR}/exec/io/ft_prepare_command_io.c \
${SRC_DIR}/exec/io/ft_prepare_command_outputs.c \
${SRC_DIR}/exec/io/ft_process_heredocs.c \
${SRC_DIR}/exec/utils/ft_exit_child.c \
${SRC_DIR}/exec/utils/close_fds/ft_close_pipe_fds.c \
${SRC_DIR}/exec/utils/close_fds/ft_close_unused_heredoc_fds.c \
${SRC_DIR}/exec/utils/close_fds/ft_handle_dup2_and_close_fd.c \
${SRC_DIR}/exec/utils/close_fds/ft_reset_context_fds.c \
${SRC_DIR}/exec/utils/path/ft_get_command_path.c \
${SRC_DIR}/exec/utils/path/ft_handle_path_search.c \
${SRC_DIR}/exec/utils/ft_apply_dup2.c \
${SRC_DIR}/exec/utils/ft_count_executable_nodes.c \
${SRC_DIR}/exec/ft_run_command_tree.c \
${SRC_DIR}/main.c \
${SRC_DIR}/signals/ft_ctrl_d.c \
${SRC_DIR}/signals/ft_ctrl_slash.c \
${SRC_DIR}/signals/ft_set_signal_child.c \
${SRC_DIR}/signals/ft_restore_signal_parent_heredoc.c \
${SRC_DIR}/signals/ft_restore_signal_parent_simple_command.c \
${SRC_DIR}/signals/ft_set_signal_parent.c \
${SRC_DIR}/signals/ft_signal_child_heredoc.c \
${SRC_DIR}/signals/ft_ctrl_c.c \

# Remove main.c from SRC_FILES to create a list of common files
COMMON_FILES = $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))
COMMON_OBJ_FILES = $(COMMON_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Object files - map source files to object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Output Files
MINISHELL_STATIC_LIB = libminishell.a

VALG_FLAG	= valgrind --leak-check=full --show-leak-kinds=all \
				--track-origins=yes --track-fds=yes --trace-children=yes \
				--suppressions=./readline.supp

################################## EXECUTABLE ##################################
EXEC = minishell
MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(BUILD_DIR)/main.o

#################################### COLORS ####################################
DEFAULT_COLOR = \033[0;39m
RED_COLOR = \033[0;91m
GREEN_COLOR = \033[0;92m
YELLOW_COLOR = \033[0;93m
BLUE_COLOR = \033[0;94m

#################################### RULES #####################################
all: $(EXEC)

$(LIBS):
	@$(MAKE) -C $(LIB_DIR) -s

$(MINISHELL_STATIC_LIB): $(COMMON_OBJ_FILES)
	@ar rcs $@ $^
	@echo "$(GREEN_COLOR)Compiled: $(DEFAULT_COLOR) $(MINISHELL_STATIC_LIB) ✅";

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW_COLOR)Compiling: $(DEFAULT_COLOR) $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(LIBS) $(MINISHELL_STATIC_LIB) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(MINISHELL_STATIC_LIB) $(LIBS) $(LDFLAGS) -o $@
	@echo "$(GREEN_COLOR)Executable: $(DEFAULT_COLOR)$(EXEC) created!✅"

# TODO: fix relinking on debugger and valgrind rules
# TODO: to delete this rule
debugger: CFLAGS += $(GFLAG)
debugger: fclean $(EXEC)

# TODO: fix relinking on debugger and valgrind rules
valgrind: $(EXEC)
	$(VALG_FLAG) ./$(EXEC)


debug:
	@echo "$(BLUE_COLOR)SRC_FILES: $(DEFAULT_COLOR) $(SRC_FILES)"
	@echo "$(BLUE_COLOR)OBJ_FILES: $(DEFAULT_COLOR) $(OBJ_FILES)"
	@echo "$(BLUE_COLOR)COMMON_FILES: $(DEFAULT_COLOR) $(COMMON_FILES)"
	@echo "$(BLUE_COLOR)COMMON_OBJ_FILES: $(DEFAULT_COLOR) $(COMMON_OBJ_FILES)"

help:
	@echo "Available commands:"
	@echo "$(YELLOW_COLOR)make$(DEFAULT_COLOR)		- Build the executable"
	@echo "$(YELLOW_COLOR)make clean$(DEFAULT_COLOR)	- Remove object files"
	@echo "$(YELLOW_COLOR)make fclean$(DEFAULT_COLOR)	- Remove object files and the executables"
	@echo "$(YELLOW_COLOR)make re$(DEFAULT_COLOR)		- Rebuild everything"
	@echo "$(YELLOW_COLOR)make debug$(DEFAULT_COLOR)	- Show debug info"
	@echo "$(YELLOW_COLOR)make help$(DEFAULT_COLOR)		- Show this help message"

clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN_COLOR)Clean: $(DEFAULT_COLOR) minishell 🧹"

fclean: clean
	@rm -f $(MINISHELL_STATIC_LIB) $(EXEC)
	@$(MAKE) fclean -C $(LIB_DIR) -s
	@echo "$(GREEN_COLOR)Fclean: $(DEFAULT_COLOR) minishell 🧹"

re: fclean all

# TODO: add debugger and valrgind to list of .PHONY
.PHONY: all clean fclean re debug help debugger valgrind
