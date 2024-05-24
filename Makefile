NAME_B = bonus
NAME_P = pipex

_SRCS_P = pipex.c

_SRCS_E = checking_errors.c 

_SRCS_U = ft_split.c \
			ft_strncmp.c \
			ft_strjoin.c \
			ft_calloc.c \
			ft_strlen.c \
			ft_bzero.c 


SRCS_P_DIR = src
SRCS_E_DIR = errors
SRCS_U_DIR = utils

SRCS_P = $(addprefix $(SRCS_P_DIR)/, $(_SRCS_P))
SRCS_E = $(addprefix $(SRCS_E_DIR)/, $(_SRCS_E))
SRCS_U = $(addprefix $(SRCS_U_DIR)/, $(_SRCS_U))

SRCO_P = $(SRCS_P:.c=.o)
SRCO_E = $(SRCS_E:.c=.o)
SRCO_U = $(SRCS_U:.c=.o)

FLAG = -Wall -Wextra -Werror
INC = -I includes/

all : $(NAME_P)

SRCO_P = $(SRCS_P:.c=.o)
SRCO_E = $(SRCS_E:.c=.o)
SRCO_U = $(SRCS_U:.c=.o)

$(NAME_P) : $(SRCO_P) $(SRCO_E) $(SRCO_U)
	cc -o $(NAME_P) $(SRCO_P) $(SRCO_E) $(SRCO_U)

%.o : %.c
	cc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO_P)
	/bin/rm -f $(SRCO_E)
	/bin/rm -f $(SRCO_U)

fclean : clean
	/bin/rm -f $(NAME_P)
	/bin/rm -f $(SRCO_P)
	/bin/rm -f $(SRCO_E)
	/bin/rm -f $(SRCO_U)

re :
	make fclean
	make

.PHONY: all clean fclean re