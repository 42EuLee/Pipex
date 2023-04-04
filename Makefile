
NAME	= peepex

CC		= gcc -Wall -Wextra -Werror

SRCS_DIR	= ./src
OBJS_DIR 	= ./obj
GNL_DIR		= ./get_next_line

SRCS		= utils.c initializer.c join_key_value.c executor.c
SRCS_GNL	= get_next_line.c get_next_line_utils.c

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)
GNL_OBJS	= $(SRCS_GNL:%.c=$(OBJS_DIR)/%.o)

RM		= rm -rf

LIB			= -Llibft -lft

INCLUDES	= -Iincludes -Ilibft -Iget_next_line

all:	$(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) main.c libft/libft.a 
	@$(CC) main.c $(OBJS) $(GNL_OBJS) $(INCLUDES) $(LIB) -o $@
	@echo "$(GREEN)Compiled $@ successfully $(RESET)"

libft/libft.a :
	@make bonus -C libft

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(INCLUDES) -c $< -o $@


clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(RED)Removed $(NAME) .obj$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@ make fclean -C libft
	@echo "$(RED)Removed $(NAME)$(RESET)"

re: fclean all

.PHONY: all fclean clean re

# Colors are great!
# Formats are greater!
# https://misc.flogisoft.com/bash/tip_colors_and_formatting
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[033m
BLUE	= \033[034m
PINK	= \033[035m
TEAL	= \033[036m
WHITE	= \033[037m
RESET	= \033[0m # No Color