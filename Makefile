# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 14:25:31 by niabraha          #+#    #+#              #
#    Updated: 2024/06/05 16:59:25 by niabraha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

_SRCS_P = pipex.c \
			pipex2.c \
			utils.c \
			utils2.c 
			
SRCS_P_DIR = src

SRCS_P = $(addprefix $(SRCS_P_DIR)/, $(_SRCS_P))

SRCO_P = $(SRCS_P:.c=.o)

FLAG = -g3 -Wall -Wextra -Werror
INC = -I includes/

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NO_COLOR = \033[0m

all : $(NAME)

$(NAME) : $(SRCO_P)
	@cc $(FLAG) -o $(NAME) $(SRCO_P) $(INC)
	@echo "$(GREEN)Make done!$(NO_COLOR)"

%.o : %.c
	@cc $(FLAG) -c -o $@ $< $(INC)

clean :
	@/bin/rm -f $(SRCO_P)
	@echo "$(YELLOW)Make clean done! $(NO_COLOR)"
	

fclean : clean
	@/bin/rm -f $(NAME)
	@echo "$(RED)Make fclean done! $(NO_COLOR)"

re :
	@make fclean
	@make all

.PHONY : all clean fclean re