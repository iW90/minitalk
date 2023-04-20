# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 19:33:27 by inwagner          #+#    #+#              #
#    Updated: 2023/04/19 22:15:51 by inwagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAMES
NAME	:=	minitalk
BNAME	:=	minitalk_bonus
SERVER	:=	server
CLIENT	:=	client
BSERVER	:=	server_bonus
BCLIENT	:=	client_bonus
PRINTF	:=	ft_printf.a

# FLAGS
HDR		:=	-I ./includes/
CFLAG	:=	-Wall -Werror -Wextra

# PATHS
SRC		:=	./srcs/
OSRC	:=	./objs/
BSRC	:=	./srcs/bonus/
PSRC	:=	./ft_printf/

# PRINTF
PTF		:=	$(addprefix ${PSRC}, ${PRINTF})

# MANDATORY
SFTS	:=	server.c utils.c
CFTS	:=	client.c utils.c
SOBJ	:=	$(SFTS:%.c=$(OSRC)%.o)
COBJ	:=	$(CFTS:%.c=$(OSRC)%.o)

# BONUS
BSFTS	:=	server_bonus.c utils_bonus.c
BCFTS	:=	client_bonus.c utils_bonus.c
BSOBJ	:=	$(BSFTS:%.c=$(OSRC)%.o)
BCOBJ	:=	$(BCFTS:%.c=$(OSRC)%.o)

# Commands
all: $(NAME)

$(NAME): $(PTF) $(SERVER) $(CLIENT)

bonus: $(BSERVER) $(BCLIENT)

# Compile ft_printf
$(PTF):
	@$(MAKE) -C $(PSRC)

# Compile objects
$(SERVER): $(SOBJ)
	cc $(CFLAG) $(SOBJ) $(PTF) -o $(SERVER)

$(CLIENT): $(COBJ)
	cc $(CFLAG) $(COBJ) $(PTF) -o $(CLIENT)

$(BSERVER): $(BSOBJ)
	cc $(CFLAG) $(BSOBJ) $(PTF) -o $(BSERVER)

$(BCLIENT): $(BCOBJ)
	cc $(CFLAG) $(BCOBJ) $(PTF) -o $(BCLIENT)
	
# Make Objects
$(OSRC)%.o: $(SRC)%.c
	mkdir -p objs
	cc $(CFLAG) $(HDR) -c $< -o $@

$(OSRC)%.o: $(BSRC)%.c
	mkdir -p objs
	cc $(CFLAG) $(HDR) -c $< -o $@

# Cleaners e Remaker
clean:
	@$(MAKE) -C $(PSRC) clean
	@[ -d $(OSRC) ] && rm -rf $(OSRC) && echo objects deleted || [ -f Makefile ]

fclean: clean
	@$(MAKE) -C $(PSRC) fclean
	@[ -f ./$(SERVER) ] && rm $(SERVER) && echo $(SERVER) deleted ||  [ -f Makefile ]
	@[ -f ./$(CLIENT) ] && rm $(CLIENT) && echo $(CLIENT) deleted ||  [ -f Makefile ]
	@[ -f ./$(BSERVER) ] && rm $(BSERVER) && echo $(BSERVER) deleted || [ -f Makefile ]
	@[ -f ./$(BCLIENT) ] && rm $(BCLIENT) && echo $(BCLIENT) deleted || [ -f Makefile ]

re: fclean all

# Recipes
.PHONY: all bonus clean fclean re
