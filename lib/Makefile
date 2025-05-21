################################# DIRECTORIES ##################################
LIB_DIR = .
TMP_DIR = $(LIB_DIR)/.temp

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

#################################### COLORS ####################################
DEFAULT_COLOR = \033[0;39m
RED_COLOR = \033[0;91m
GREEN_COLOR = \033[0;92m
YELLOW_COLOR = \033[0;93m
BLUE_COLOR = \033[0;94m

#################################### RULES #####################################
all: $(LIBS)

$(LIBFT_STATIC_LIB): $(LIBFT_DIR)/Makefile
	@if [ ! -f "$@" ]; then \
		$(MAKE) -C $(LIBFT_DIR) -s || { echo "$(RED_COLOR)Libft build failed!$(DEFAULT_COLOR)"; exit 1; }; \
	fi

$(FT_PRINTF_STATIC_LIB): $(FT_PRINTF_DIR)/Makefile
	@if [ ! -f "$@" ]; then \
		$(MAKE) -C $(FT_PRINTF_DIR) -s || { echo "$(RED_COLOR)libftprintf build failed!$(DEFAULT_COLOR)"; exit 1; }; \
	fi

$(GNL_STATIC_LIB): $(GNL_DIR)/Makefile
	@if [ ! -f "$@" ]; then \
		$(MAKE) -C $(GNL_DIR) -s || { echo "$(RED_COLOR)libftgnl build failed!$(DEFAULT_COLOR)"; exit 1; }; \
	fi

clean:
	@$(MAKE) clean -C $(LIBFT_DIR) -s
	@$(MAKE) clean -C $(FT_PRINTF_DIR) -s
	@$(MAKE) clean -C $(GNL_DIR) -s

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) -s
	@$(MAKE) fclean -C $(FT_PRINTF_DIR) -s
	@$(MAKE) fclean -C $(GNL_DIR) -s

re: fclean all

.PHONY: all clean fclean re
