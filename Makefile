# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 19:33:27 by inwagner          #+#    #+#              #
#    Updated: 2023/04/16 10:14:21 by inwagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAMES
NAME    :=  minitalk
BNAME   :=  minitalk_bonus
SERVER  :=  server
CLIENT  :=  client
BSERVER :=  server_bonus
BCLIENT :=  client_bonus

# FLAGS
HDR     :=  -I ./includes/
CFLAG   :=  -Wall -Werror -Wextra

# PATHS
SRC     :=  ./srcs/
OSRC    :=  ./objs/
BSRC    :=  ./srcs/bonus/

# MANDATORY
SFTS    :=  server.c
CFTS    :=  client.c
SOBJ    :=  $(SFTS:%.c=./objs/%.o)
COBJ    :=  $(CFTS:%.c=./objs/%.o)

# BONUS
BSFTS   :=  server_bonus.c
BCFTS   :=  client_bonus.c
BSOBJ   :=  $(BSFTS:%.c=./objs/%.o)
BCOBJ   :=  $(BCFTS:%.c=./objs/%.o)

# Commands
all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

bonus: $(BSERVER) $(BCLIENT)

# Compile objects
$(SERVER): $(SOBJ)
	cc $(CFLAG) $(SOBJ) -o $(SERVER)

$(CLIENT): $(COBJ)
	cc $(CFLAG) $(COBJ) -o $(CLIENT)

$(BSERVER): $(BSOBJ)
	cc $(CFLAG) $(BSOBJ) -o $(BSERVER)

$(BCLIENT): $(BCOBJ)
	cc $(CFLAG) $(BCOBJ) -o $(BCLIENT)
	
# Make Objects
$(OSRC)%.o: $(SRC)%.c
	mkdir -p objs
	cc $(CFLAG) $(HDR) -c $< -o $@

$(OSRC)%.o: $(BSRC)%.c
	mkdir -p objs
	cc $(CFLAG) $(HDR) -c $< -o $@

# Cleaners e Remaker
clean:
	@[ -d ./objs ] && rm -rf ./objs || [ -f Makefile ]

fclean: clean
	@[ -f ./$(SERVER) ] && rm $(SERVER) && echo $(SERVER) cleaned ||  [ -f Makefile ]
	@[ -f ./$(CLIENT) ] && rm $(CLIENT) && echo $(CLIENT) cleaned ||  [ -f Makefile ]
	@[ -f ./$(BSERVER) ] && rm $(BSERVER) && echo server bonus cleaned || [ -f Makefile ]
	@[ -f ./$(BCLIENT) ] && rm $(BCLIENT) && echo client bonus cleaned || [ -f Makefile ]

re: fclean all

# Recipes
.PHONY: all bonus clean fclean re
