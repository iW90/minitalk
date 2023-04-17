# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 19:58:12 by inwagner          #+#    #+#              #
#    Updated: 2023/04/16 20:46:08 by inwagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES
NAME	:=	ft_printf.a
FLAG	:=	-Wall -Wextra -Werror
HDR		:=	-I ./includes/
SRC		:=	./srcs/
OSRC	:=	./objs/
FTS 	:=	ft_printf_aux.c ft_printf.c
OBJS	:=	$(FTS:%.c=$(OSRC)%.o)

all: $(NAME)

# Compile Objects
$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

# Make Objects
$(OSRC)%.o: $(SRC)%.c
	@mkdir -p objs
	@cc $(CFLAG) $(HDR) -c $< -o $@

clean:
	@[ -d $(OSRC) ] && rm -rf $(OSRC) || [ -f Makefile ]

fclean:	clean
	@[ -f ./$(NAME) ] && rm $(NAME) && echo $(NAME) cleaned ||  [ -f Makefile ]

re: fclean all

.PHONY: all clean fclean re
