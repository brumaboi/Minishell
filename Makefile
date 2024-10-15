# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 11:33:14 by marvin            #+#    #+#              #
#    Updated: 2024/10/09 11:33:14 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LDFLAGS			=	-lreadline -lncurses #-fsanitize=address
RM				=	rm -f
AR				=	ar rcs

BLUE			= \033[0;34m
PURPLE			= \033[0;35m
WHITE			= \033[0;37m
BLACK			= \033[0;30m
CYAN			= \033[0;36m
YELLOW			= \033[0;33m
RED				= \033[0;31m
GREEN			= \033[0;32m
NC				= \033[0m

LIBFT_PATH		= ./libft
LIBFT			= libft.a
INC				= inc/
SRC_DIR			= src/
# EXEC_DIR		= execution/
PARS_DIR		= parsing/
OBJ_DIR			= obj/

# EXEC_FILES		= $(SRC_DIR)$(EXEC_DIR) #name of file
# 				  $(SRC_DIR)$(EXEC_DIR) #name of file
# 				  $(SRC_DIR)$(EXEC_DIR) #name of file

PARS_FILES		= $(SRC_DIR)$(PARS_DIR) init_data_1.c \
			 	  $(SRC_DIR)$(PARS_DIR) init_data_2.c \
			 	  $(SRC_DIR)$(PARS_DIR) split_input_1.c \
			 	  $(SRC_DIR)$(PARS_DIR) split_input_2.c \
				  $(SRC_DIR)$(PARS_DIR) split_input_3.c \
			 	  $(SRC_DIR)$(PARS_DIR) split_input_4.c \

SRC	= $(PARS_FILES) $(SRC_DIR)main.c
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)/$(LIBFT)
			@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LIBFT_PATH)/$(LIBFT)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(LIBFT_PATH)/$(LIBFT) : 
	@make -C $(LIBFT_PATH) > /dev/null 2>&1

clean :
	@$(RM) -f $(OBJ)
	@$(RM) -rf $(OBJ_DIR)
	@make -C $(LIBFT_PATH) clean

fclean : clean
	@$(RM) -f $(NAME)
	@make -C $(LIBFT_PATH) fclean > /dev/null 2>&1

re : clean fclean all