# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:34:45 by naterrie          #+#    #+#              #
#    Updated: 2023/08/14 17:41:25 by naterrie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLEU := \033[36m
PURPLE := \033[35m
GREEN := \033[32m
RED := \033[31m
RESET := \033[0m
ERASE := \033[2K\033[1A\r

DIR_OBJS :=	.objs/

NAME	=	cub3d

CFLAGS	=	-Wall -Werror -Wextra -I $(INC_DIR) -mlx -lX11 -lXext -lz -lmlx -lm
HEADERS	=	cub3d.h

LIB_DIR	=	libft/
LIB_FILE	= $(addprefix $(LIB_DIR), libft.a)

INC_DIR	=	includes/
INC		=	$(addprefix $(INC_DIR), $(HEADERS))

GNL_DIR =	getnextline/
GNL_SRC =	get_next_line.c \
			get_next_line_utils.c
FILES	+=	$(addprefix $(GNL_DIR), $(GNL_SRC:.c=.o))


PARS_DIR =	src/pars/
PARS_SRC =	pars_char.c \
			parsing.c \
			utils_pars.c
FILES 	+=	$(addprefix $(PARS_DIR), $(PARS_SRC:.c=.o))

DIR_SRCS	=	src/
SRCS 		=	main.c
FILES		+=	$(addprefix $(DIR_SRCS)/, $(SRCS))

OBJS  =	$(addprefix $(DIR_OBJS), $(SRCS:.c=.o)) \
        $(addprefix $(GNL_DIR), $(GNL_SRC:.c=.o)) \
        $(addprefix $(PARS_DIR), $(PARS_SRC:.c=.o))

all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS) $(LIB)
	cc $(CFLAGS) $(OBJS) mlx/libmlx.a $(LIB) -o $(NAME)
	echo "$(GREEN)✅ $(NAME) compilated !"
	@norminette | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(WHITE)"}'

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INC) Makefile
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	cc $(CFLAGS) -c $< -o $@
	printf "$(ERASE)"

$(DIR_OBJS):
	mkdir -p $@

$(LIB): force
	make -C ./$(LIB_DIR)

mlx/libmlx.a:
	make -C ./mlx

clean:
	echo "$(PURPLE)🧹Removing $(NAME).o files !"
	rm -rf $(DIR_OBJS)
	make clean -C ./$(LIB_DIR)

fclean: clean
	echo "$(PURPLE)🧹Removing $(NAME:.a=) !"
	rm -f $(NAME)
	make fclean -C ./$(LIB_DIR)

re: fclean $(NAME)

.PHONY: clean fclean re all

.SILENT:
