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
LDFLAGS			=	-lreadline -lncurses #-fsanitize=address -g
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
EXEC_DIR		= execution/
BUILTIN_DIR		= builtins/
PARS_DIR		= parsing/
OTH_DIR			= other/
OBJ_DIR			= obj/

EXEC_FILES		= $(SRC_DIR)$(EXEC_DIR)commands/1_commands.c \
				  $(SRC_DIR)$(EXEC_DIR)commands/2_builtins.c \
				  $(SRC_DIR)$(EXEC_DIR)pipes/1_execute.c \
				  $(SRC_DIR)$(EXEC_DIR)pipes/2_process.c \
				  $(SRC_DIR)$(EXEC_DIR)pipes/3_helper.c \
				  $(SRC_DIR)$(EXEC_DIR)redirections/1_handle_redir.c \
				  $(SRC_DIR)$(EXEC_DIR)redirections/2_here_doc.c \
				  $(SRC_DIR)$(EXEC_DIR)redirections/3_redir_utils.c \
				  $(SRC_DIR)$(EXEC_DIR)env_utils.c \
				  $(SRC_DIR)$(EXEC_DIR)execute_ast.c \
				  $(SRC_DIR)$(EXEC_DIR)find_path.c \
				  $(SRC_DIR)$(EXEC_DIR)logical.c \

PARS_FILES		= $(SRC_DIR)$(PARS_DIR)init_data/1_init.c \
			 	  $(SRC_DIR)$(PARS_DIR)init_data/2_env_list.c \
				  $(SRC_DIR)$(PARS_DIR)init_data/3_exp_utils.c \
			 	  $(SRC_DIR)$(PARS_DIR)split_input/split_input.c \
			 	  $(SRC_DIR)$(PARS_DIR)split_input/special_char.c \
				  $(SRC_DIR)$(PARS_DIR)split_input/quote_handling.c \
				  $(SRC_DIR)$(PARS_DIR)split_input/expansion/1_copy_expand.c \
				  $(SRC_DIR)$(PARS_DIR)split_input/expansion/2_get_len.c \
				  $(SRC_DIR)$(PARS_DIR)split_input/expansion/3_get_fill.c \
			 	  $(SRC_DIR)$(PARS_DIR)split_input/list/1_token_parse.c \
				  $(SRC_DIR)$(PARS_DIR)split_input/list/2_list_utils.c \
				  $(SRC_DIR)$(PARS_DIR)build_ast/build_ast.c \
				  $(SRC_DIR)$(PARS_DIR)build_ast/commands.c \
				  $(SRC_DIR)$(PARS_DIR)build_ast/op_and_or.c \
				  $(SRC_DIR)$(PARS_DIR)build_ast/op_pipe.c \
				  $(SRC_DIR)$(PARS_DIR)build_ast/op_redirection.c \

BUILTIN_FILES   = $(SRC_DIR)$(BUILTIN_DIR)echo.c \
				  $(SRC_DIR)$(BUILTIN_DIR)pwd.c \
				  $(SRC_DIR)$(BUILTIN_DIR)cd.c \
				  $(SRC_DIR)$(BUILTIN_DIR)cd_utils.c \
				  $(SRC_DIR)$(BUILTIN_DIR)export.c \
				  $(SRC_DIR)$(BUILTIN_DIR)unset.c \
				  $(SRC_DIR)$(BUILTIN_DIR)env.c \
				  $(SRC_DIR)$(BUILTIN_DIR)exit.c \

OTH_FILES		= $(SRC_DIR)$(OTH_DIR)signal.c \
				  $(SRC_DIR)$(OTH_DIR)cleanup.c \
				  $(SRC_DIR)$(OTH_DIR)free.c \
				  $(SRC_DIR)$(OTH_DIR)user_input.c \
				  $(SRC_DIR)$(OTH_DIR)syntax.c \


SRC	= $(PARS_FILES) $(EXEC_FILES) $(BUILTIN_FILES) $(OTH_FILES) $(SRC_DIR)main.c
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)/$(LIBFT)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_PATH)/$(LIBFT) $(LDFLAGS)

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