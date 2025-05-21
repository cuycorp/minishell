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
SRC_FILES =	$(SRC_DIR)/get_next_line.c \
			$(SRC_DIR)/get_next_line_utils.c

# Object files - map source files to object files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output Files
GNL_STATIC_LIB = libftgnl.a

# Target executable
EXEC = gnl
MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

# Colors
DEFAULT_COLOR = \033[0;39m
RED_COLOR = \033[0;91m
GREEN_COLOR = \033[0;92m
YELLOW_COLOR = \033[0;93m
BLUE_COLOR = \033[0;94m

# Rules
all: $(LIBFT_STATIC_LIB) $(GNL_STATIC_LIB)

# First ensure libft is built
$(LIBFT_STATIC_LIB):
	@$(MAKE) -C $(LIBFT_DIR) -s || { echo "$(RED_COLOR)Libft build failed!$(DEFAULT_COLOR)"; exit 1; }

# Then build GNL library
$(GNL_STATIC_LIB): $(LIBFT_STATIC_LIB) $(OBJ_FILES)
	@ar rcs $@ $(OBJ_FILES)
	@echo "$(GREEN_COLOR)Compiled: $(DEFAULT_COLOR) get_next_line ✅";

# Compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile main.o separately
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

# Build executable with all dependencies
$(EXEC): $(LIBFT_STATIC_LIB) $(GNL_STATIC_LIB) $(MAIN_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(GNL_STATIC_LIB) $(LIBFT_STATIC_LIB) -o $@ -g3
	@echo "$(GREEN_COLOR)Executable: $(DEFAULT_COLOR)$(EXEC) created!✅"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN_COLOR)Clean: $(DEFAULT_COLOR) get_next_line 🧹"

fclean:
	@if [ -d "$(OBJ_DIR)" ]; then $(MAKE) clean -s; fi
	@rm -f $(GNL_STATIC_LIB) $(EXEC)
	@echo "$(GREEN_COLOR)Fclean: $(DEFAULT_COLOR) get_next_line 🧹"

re: fclean all

# Phony targets
.PHONY: all clean fclean re
