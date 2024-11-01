# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 12:12:14 by sbruma            #+#    #+#              #
#    Updated: 2024/11/01 15:14:10 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME			= libft.a

# ANSI Colors
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
WHITE			= \033[0;37m
BLACK			= \033[0;30m
CYAN			= \033[0;36m
YELLOW			= \033[0;33m
RED				= \033[0;31m
GREEN			= \033[0;32m
NC				= \033[0m

# Directories
INC				= inc/
SRC_DIR			= src/
OBJ_DIR			= obj/

# Compielr and Flags
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -I
RM				= rm -f
AR				= ar rcs

# Source Files
FTPSC_DIR		=	$(SRC_DIR)ft_piscine/ft_fibonacci.c \
					$(SRC_DIR)ft_piscine/ft_find_next_prime.c \
					$(SRC_DIR)ft_piscine/ft_is_prime.c \
					$(SRC_DIR)ft_piscine/ft_iterative_factorial.c \
					$(SRC_DIR)ft_piscine/ft_iterative_power.c \
					$(SRC_DIR)ft_piscine/ft_recursive_factorial.c \
					$(SRC_DIR)ft_piscine/ft_recursive_power.c \
					$(SRC_DIR)ft_piscine/ft_sqrt.c \
					$(SRC_DIR)ft_piscine/ft_range.c \
					$(SRC_DIR)ft_piscine/ft_ultimate_range.c \
					$(SRC_DIR)ft_piscine/ft_rev_int_tab.c \
					$(SRC_DIR)ft_piscine/ft_sort_int_tab.c \
					$(SRC_DIR)ft_piscine/ft_swap.c

FTIS_DIR		=	$(SRC_DIR)ft_is/ft_isalnum.c \
					$(SRC_DIR)ft_is/ft_isalpha.c \
					$(SRC_DIR)ft_is/ft_isascii.c \
					$(SRC_DIR)ft_is/ft_isdigit.c \
					$(SRC_DIR)ft_is/ft_isprint.c \
					$(SRC_DIR)ft_is/ft_isspace.c

FTMEM_DIR		=	$(SRC_DIR)ft_mem/ft_bzero.c \
					$(SRC_DIR)ft_mem/ft_calloc.c \
					$(SRC_DIR)ft_mem/ft_memchr.c \
					$(SRC_DIR)ft_mem/ft_memcmp.c \
					$(SRC_DIR)ft_mem/ft_memcpy.c \
					$(SRC_DIR)ft_mem/ft_memmove.c \
					$(SRC_DIR)ft_mem/ft_memset.c \
					$(SRC_DIR)ft_mem/ft_realloc.c

FTPUT_DIR		=	$(SRC_DIR)ft_put/ft_putchar_fd.c \
					$(SRC_DIR)ft_put/ft_putchar.c \
					$(SRC_DIR)ft_put/ft_putendl_fd.c \
					$(SRC_DIR)ft_put/ft_putnbr_base.c \
					$(SRC_DIR)ft_put/ft_putnbr_fd.c \
					$(SRC_DIR)ft_put/ft_putstr_fd.c  \
					$(SRC_DIR)ft_put/ft_putstr.c

FTTO_DIR		=	$(SRC_DIR)ft_to/ft_atoi.c \
					$(SRC_DIR)ft_to/ft_itoa.c \
					$(SRC_DIR)ft_to/ft_tolower.c \
					$(SRC_DIR)ft_to/ft_toupper.c \
					$(SRC_DIR)ft_to/ft_utoa_base.c \
					$(SRC_DIR)ft_to/ft_utoa.c \
					$(SRC_DIR)ft_to/ft_atol.c

FTSTR_DIR		=	$(SRC_DIR)ft_str/ft_split.c \
					$(SRC_DIR)ft_str/ft_strcat.c \
					$(SRC_DIR)ft_str/ft_strchr.c \
					$(SRC_DIR)ft_str/ft_strcmp.c \
					$(SRC_DIR)ft_str/ft_strcpy.c \
					$(SRC_DIR)ft_str/ft_strdup.c \
					$(SRC_DIR)ft_str/ft_striteri.c \
					$(SRC_DIR)ft_str/ft_strjoin.c \
					$(SRC_DIR)ft_str/ft_strlcat.c \
					$(SRC_DIR)ft_str/ft_strlcpy.c \
					$(SRC_DIR)ft_str/ft_strlen.c \
					$(SRC_DIR)ft_str/ft_strmapi.c \
					$(SRC_DIR)ft_str/ft_strncpy.c \
					$(SRC_DIR)ft_str/ft_strndup.c \
					$(SRC_DIR)ft_str/ft_strnlen.c \
					$(SRC_DIR)ft_str/ft_strnstr.c \
					$(SRC_DIR)ft_str/ft_strrchr.c \
					$(SRC_DIR)ft_str/ft_strstr.c \
					$(SRC_DIR)ft_str/ft_strtrim.c \
					$(SRC_DIR)ft_str/ft_substr.c \
					$(SRC_DIR)ft_str/ft_strncmp.c

FTLST_DIR		=	$(SRC_DIR)ft_lst/ft_lstadd_back.c \
					$(SRC_DIR)ft_lst/ft_lstadd_front.c \
					$(SRC_DIR)ft_lst/ft_lstclear.c \
					$(SRC_DIR)ft_lst/ft_lstdelone.c \
					$(SRC_DIR)ft_lst/ft_lstiter.c \
					$(SRC_DIR)ft_lst/ft_lstlast.c \
					$(SRC_DIR)ft_lst/ft_lstmap.c \
					$(SRC_DIR)ft_lst/ft_lstnew.c \
					$(SRC_DIR)ft_lst/ft_lstsize.c 

FTPRINTF_DIR	=	$(SRC_DIR)ft_printf/ft_printf.c \
					$(SRC_DIR)ft_printf/for_udecimal.c \
					$(SRC_DIR)ft_printf/for_string.c \
					$(SRC_DIR)ft_printf/for_pointer.c \
					$(SRC_DIR)ft_printf/for_idecimal.c \
					$(SRC_DIR)ft_printf/for_hex.c	\
					$(SRC_DIR)ft_printf/for_char.c 

GNL_DIR			=	$(SRC_DIR)get_next_line/get_next_line.c \
					$(SRC_DIR)get_next_line/get_next_line_utils.c

# Concatenate all source files
SRC 			= $(FTIS_DIR) $(FTMEM_DIR) $(FTPUT_DIR) $(FTTO_DIR) $(FTTO_DIR) $(FTSTR_DIR) $(FTLST_DIR) $(FTPRINTF_DIR) $(FTPSC_DIR) $(GNL_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# Build rules
all: 			$(NAME)

$(NAME): 		$(OBJ)
				@echo "$(RED)𝘾𝙍𝙀𝘼𝙏𝙄𝙉𝙂 𝙇𝙄𝘽𝙁𝙏$(NC)"
				@$(AR) $(NAME) $(OBJ) &
				@pid=$$!; \
				for i in 1 2 3; do \
					sleep 1; \
					if [ $$i -eq 1 ]; then \
						echo "$(RED).$(NC)"; \
					elif [ $$i -eq 2 ]; then \
						echo "$(YELLOW).$(NC)"; \
					elif [ $$i -eq 3 ]; then \
						echo "$(GREEN).$(NC)"; \
					fi; \
				done; \
				wait $$pid; \
				echo "$(GREEN)𝘾𝙍𝙀𝘼𝙏𝙄𝙊𝙉 𝙎𝙐𝘾𝘾𝙀𝙎𝙎𝙁𝙐𝙇$(NC)"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)
				@$(RM) .cache_exists
				@echo "$(CYAN)𝘾𝙇𝙀𝘼𝙉𝙄𝙉𝙂$(NC)"

fclean: 		clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re