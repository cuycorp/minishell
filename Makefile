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
# TODO: Update SRC_FILES
SRC_FILES =	$(shell find $(SRC_DIR) -type f -name "*.c")

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
VALGRIND = valgrind

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
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(MINISHELL_STATIC_LIB) $(LIBS) $(LDFLAGS) $(GFLAG) -o $@
	@echo "$(GREEN_COLOR)Executable: $(DEFAULT_COLOR)$(EXEC) created!✅"

# TODO: fix relinking on debugger and valgrind rules
# TODO: to delete this rule
debugger:
	$(CC) $(CFLAGS) -g3 $(SRC_FILES) $(MINISHELL_STATIC_LIB) $(LIBS) $(LDFLAGS) -o $(EXEC)

# TODO: fix relinking on debugger and valgrind rules
$(VALGRIND):
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
.PHONY: all clean fclean re debug help
