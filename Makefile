# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 23:57:50 by jyriarte          #+#    #+#              #
#    Updated: 2025/01/21 16:31:12 by jyriarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT_PATH=libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBFT_FLAG= -L$(LIBFT_PATH) -lft

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH) -I.

SOURCES = src/pipex.c src/pipex_utils.c src/get_full_path.c src/pipe_cmd.c \
		  src/here_doc.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAG)
	@echo "$(NAME) OK!"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@  

bonus: all

all: $(NAME)

clean:
	@$(RM) $(OBJECTS) 
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH) clean

fclean: clean
	@$(RM) $(NAME) 
	@$(RM) $(LIBFT)

re: fclean all

.PHONY: all re clean fclean bonus message
