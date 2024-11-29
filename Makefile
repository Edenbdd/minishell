# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smolines <smolines@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 09:42:50 by smolines          #+#    #+#              #
#    Updated: 2024/11/29 13:23:22 by smolines         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME			= minishell

#CC          	= cc

#CFLAGS      	= -Wall -Wextra -Werror -g3 libft/

#HEADER_FILES	= minishell.h

#HEADER			= -I./include

#SRC_PATH		= src/

#OBJ_PATH		= obj/

#RM 				= rm -rf

#SRCS = 
	
#SRCS_ALL = ${SRCS} 

#OBJS = $(addprefix ${OBJ_PATH}, ${SRCS:.c=.o})

#OBJS_ALL = ${SRCS_ALL:.c=.o}

#all: $(NAME)

#$(NAME) : ${OBJS}
#	make -C libft
#	${CC} ${CFLAGS} $^ -L libft -l ft -o ${NAME} ${OBJS}  ${HEADER}
	

#${OBJ_PATH}%.o:	${SRC_PATH}%.c
#	@mkdir -p $(dir $@)
#	${CC} ${CFLAGS} ${HEADER} -c $< -o $@

#clean:
#	rm -rf ${OBJ_PATH}
#	make clean -C libft

#fclean: clean
#	rm -rf $(NAME)
#	make fclean -C libft

#re: fclean all

#norm:
#	@norminette $(SRC_PATH)/ include/ | awk '/'Error'/ {print; found=1} END {if (!found) print "\033[0;35mNorm O.K.\033[0m"}'

NAME			= minishell

CC          	= cc
CFLAGS      	= -Wall -Wextra -Werror -g3 -I./include

HEADER_FILES	= include/minishell.h
HEADER			= -I./include

SRC_PATH		= src/
OBJ_PATH		= obj/

RM 				= rm -rf

# Tous les fichiers sources (ajuster si nécessaire)
SRCS 			= 	main.c\
					parsing.c\
					init.c\
					oplist_token.c\
					free.c\
					error.c\
					

SRCS_ALL 		= $(addprefix $(SRC_PATH), $(SRCS))

# Objets correspondants
OBJS 			= $(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

# Règle principale
all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $^ -L libft -lft -lreadline -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	$(RM) $(OBJ_PATH)
	@make clean -C libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

# Norminette
norm:
	@norminette $(SRC_PATH) $(HEADER_FILES) | awk '/Error/ {print; found=1} END {if (!found) print "\033[0;35mNorm O.K.\033[0m"}'




