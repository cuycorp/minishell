# Directories
SRC_DIR = src
OBJ_DIR = build
INCLUDE_DIR = include
LIB_DIR = ../

# Libraries
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_STATIC_LIB = $(LIBFT_DIR)/libft.a

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_DIR)/include -I $(INCLUDE_DIR)

# Input Files
SRC_FILES = $(SRC_DIR)/formatters/ft_format_char_bonus.c \
			$(SRC_DIR)/formatters/ft_format_number_bonus.c \
			$(SRC_DIR)/formatters/ft_format_string_bonus.c \
			$(SRC_DIR)/formatters/ft_format_pointers_bonus.c \
			$(SRC_DIR)/utils/ft_formatters_utils_bonus.c \
			$(SRC_DIR)/utils/ft_flags_setters_bonus.c \
			$(SRC_DIR)/utils/ft_flags_checkers_bonus.c \
			$(SRC_DIR)/utils/ft_number_utils_bonus.c \
			$(SRC_DIR)/utils/ft_putnbr.c \
			$(SRC_DIR)/utils/ft_string_utils.c \
			$(SRC_DIR)/parsers/ft_parse_specifier.c \
			$(SRC_DIR)/parsers/ft_parse.c \
			$(SRC_DIR)/parsers/ft_parse_flags_bonus.c \
			$(SRC_DIR)/printers/ft_print_char.c \
			$(SRC_DIR)/printers/ft_print_number.c \
			$(SRC_DIR)/printers/ft_print_pointer.c \
			$(SRC_DIR)/printers/ft_print_string.c \
			$(SRC_DIR)/ft_printf.c \
# Object files - map source files to object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output Files
FT_PRINTF_STATIC_LIB = libftprintf.a

# Target executable
EXEC = tester
MAIN_SRC = $(SRC_DIR)/tester/main.c
MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Colors
DEFAULT_COLOR = \033[0;39m
RED_COLOR = \033[0;91m
GREEN_COLOR = \033[0;92m
YELLOW_COLOR = \033[0;93m
BLUE_COLOR = \033[0;94m

# Rules
all: $(LIBFT_STATIC_LIB) $(FT_PRINTF_STATIC_LIB)

# First ensure libft is built
$(LIBFT_STATIC_LIB):
	@$(MAKE) -C $(LIBFT_DIR) -s || { echo "$(RED_COLOR)Libft build failed!$(DEFAULT_COLOR)"; exit 1; }

# Then build ft_printf library
$(FT_PRINTF_STATIC_LIB): $(LIBFT_STATIC_LIB) $(OBJ_FILES)
	@ar rcs $@ $^
	@echo "$(GREEN_COLOR)Compiled: $(DEFAULT_COLOR) ft_printf ✅";

# compile .c file into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# Build executable with all dependencies
$(EXEC): $(LIBFT_STATIC_LIB) $(FT_PRINTF_STATIC_LIB) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(FT_PRINTF_STATIC_LIB) $(LIBFT_STATIC_LIB) -o $@ -g3
	@echo "$(GREEN_COLOR)Executable: $(DEFAULT_COLOR)$(EXEC) created!✅"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN_COLOR)Clean: $(DEFAULT_COLOR) ft_printf 🧹"

fclean:
	@if [ -d "$(OBJ_DIR)" ]; then $(MAKE) clean -s; fi
	@rm -f $(FT_PRINTF_STATIC_LIB) $(EXEC)
	@echo "$(GREEN_COLOR)Fclean: $(DEFAULT_COLOR) ft_printf 🧹"

re: fclean all

# Phony targets
.PHONY: all clean fclean re
