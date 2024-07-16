# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kufato <kufato@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:21:17 by kufato            #+#    #+#              #
#    Updated: 2024/06/18 15:30:59 by kufato           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############### HOSTTYPE RULE ###############

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

############### ARGUMENTS ###############

LIB_NAME	= libft_malloc.so
NAME		= $(basename $(LIB_NAME))_$(HOSTTYPE).so

SRC_DIR		= srcs
OBJ_DIR		= objs

LIBFT		= lib/libft

############### SOURCES ###############

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g3 -fPIC

SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

############### RULES ###############

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo - Compiling...
	@echo - Compiling libft ...
	@$(MAKE) bonus -s -C $(LIBFT)
	@$(CC) $(CFLAGS) -shared -o $@ $(OBJS) -L$(LIBFT) -lft
	@ln -sf $(NAME) $(LIB_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo - Cleaning...
	@rm -rf $(OBJ_DIR)
	@echo - Cleaning libft...
	@$(MAKE) -s -C $(LIBFT) clean

fclean: clean
	@echo - Cleaning deeper...
	@rm -rf $(NAME) $(LIB_NAME)
	@echo - Cleaning libft.a
	@$(MAKE) -s -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
