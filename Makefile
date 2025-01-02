# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 09:42:50 by smolines          #+#    #+#              #
#    Updated: 2025/01/02 15:18:55 by aubertra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
					cmd_path.c\
					cmd_test_path.c\
					debug.c\
					env.c\
					errno.c\
					error.c\
					exec.c\
					exec_child.c\
					exec_heredoc_line.c\
					expand.c\
					expand_cut.c\
					expand_heredoc.c\
					expand_replace.c\
					fill_cmd.c\
					fill_cmd_expand.c\
					fill_cmd_args.c\
					free_struct.c\
					free.c\
					handle_heredoc_files.c\
					handle_files.c\
					oplist_cmd.c\
					oplist_env.c\
					oplist_manager.c\
					oplist_token.c\
					parsing_dir.c\
					parsing_heredoc.c\
					parsing_operators.c\
					parsing_spaces_symbols.c\
					parsing_utils.c\
					parsing_utils2.c\
					parsing.c\
					builtin/parsing_builtin.c\
					builtin/env_builtin.c\
					builtin/env_builtin_args.c\
					builtin/oplist_export.c\
					builtin/export_builtin.c\

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




