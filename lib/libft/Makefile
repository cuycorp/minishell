# Directories
SRC_DIR = src
OBJ_DIR = build
INCLUDE_DIR = include

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)

# Input files
FT_IS_DIR		=	ft_is/
FT_LST_DIR		=	ft_lst/
FT_MEM_DIR		=	ft_mem/
FT_PUT_DIR		=	ft_put/
FT_STR_DIR		=	ft_str/
FT_TO_DIR		=	ft_to/
FT_ALLOC_DIR	=	ft_alloc/

FT_IS_FILES		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
					ft_isspace
FT_LST_FILES	=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
					ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize
FT_MEM_FILES	=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy \
					ft_memmove ft_memset
FT_PUT_FILES	=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd
FT_STR_FILES	=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
					ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
					ft_strnstr ft_strrchr ft_strtrim ft_substr ft_strarr_len
FT_TO_FILES		=	ft_atoi ft_atoi_base ft_atol ft_itoa ft_tolower ft_toupper
FT_ALLOC_FILES	=	ft_alloc_struct ft_free_char_tab ft_free_int_tab

SRCS+=$(addprefix $(SRC_DIR)/$(FT_IS_DIR), $(addsuffix .c, $(FT_IS_FILES)))
SRCS+=$(addprefix $(SRC_DIR)/$(FT_LST_DIR), $(addsuffix .c, $(FT_LST_FILES)))
SRCS+=$(addprefix $(SRC_DIR)/$(FT_MEM_DIR), $(addsuffix .c, $(FT_MEM_FILES)))
SRCS+=$(addprefix $(SRC_DIR)/$(FT_PUT_DIR), $(addsuffix .c, $(FT_PUT_FILES)))
SRCS+=$(addprefix $(SRC_DIR)/$(FT_STR_DIR), $(addsuffix .c, $(FT_STR_FILES)))
SRCS+=$(addprefix $(SRC_DIR)/$(FT_TO_DIR), $(addsuffix .c, $(FT_TO_FILES)))
SRCS+=$(addprefix $(SRC_DIR)/$(FT_ALLOC_DIR), $(addsuffix .c, $(FT_ALLOC_FILES)))

# Object files - map sources files to object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output Files
LIBFT_STATIC_LIB = libft.a

# Colors
DEFAULT_COLOR = \033[0;39m
RED_COLOR = \033[0;91m
GREEN_COLOR = \033[0;92m
YELLOW_COLOR = \033[0;93m
BLUE_COLOR = \033[0;94m

# Rules
all: $(LIBFT_STATIC_LIB)

$(LIBFT_STATIC_LIB): $(OBJS)
	@ar rcs $@ $^
	@echo "$(GREEN_COLOR)Compiled: $(DEFAULT_COLOR) libft ✅";

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN_COLOR)Clean: $(DEFAULT_COLOR) libft 🧹"

fclean:
	@if [ -d "$(OBJ_DIR)" ]; then $(MAKE) clean -s; fi
	@rm -f $(LIBFT_STATIC_LIB)
	@echo "$(GREEN_COLOR)Fclean: $(DEFAULT_COLOR) libft 🧹"

re: fclean all

.PHONY: all clean re fclean
