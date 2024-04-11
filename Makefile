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

all : $(NAME_C) $(NAME_P)

SRCO_P = $(SRCS_P:.c=.o)
SRCO_E = $(SRCS_E:.c=.o)
SRCO_U = $(SRCS_U:.c=.o)

$(NAME_B) :$(SRCO_E) $(SRCO_U)
	gcc -o $(NAME_C) $(SRCO_E) $(SRCO_U)

$(NAME_P) : $(SRCO_P) $(SRCO_E) $(SRCO_U)
	gcc -o $(NAME_P) $(SRCO_P) $(SRCO_E) $(SRCO_U)

%.o : %.c
	gcc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO_A)
	/bin/rm -f $(SRCO_C)
	/bin/rm -f $(SRCO_P)
	/bin/rm -f $(SRCO_I)
	/bin/rm -f $(SRCO_E)
	/bin/rm -f $(SRCO_U)

fclean : clean
	/bin/rm -f $(SRCO_A)
	/bin/rm -f $(NAME_C)
	/bin/rm -f $(NAME_P)
	/bin/rm -f $(SRCO_I)
	/bin/rm -f $(SRCO_E)
	/bin/rm -f $(SRCO_U)

re :
	make fclean
	make