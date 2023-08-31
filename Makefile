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

NAME	=	cub3D

CFLAGS	=	-Wall -Werror -Wextra -I $(INC_DIR) -g3
HEADERS	=	cub3d.h

MLXFLAGS	= -L ./mlx -lmlx -lXext -lX11 -lm -lbsd

LIB_DIR	=	libft/
LIBFT	= $(addprefix $(LIB_DIR), libft.a)

INC_DIR	=	includes/
INC		=	$(addprefix $(INC_DIR), $(HEADERS))

GNL_DIR =	getnextline/
GNL_SRC =	get_next_line.c \
			get_next_line_utils.c

FILES	+=	$(addprefix $(GNL_DIR), $(GNL_SRC:.c=.o))


PARS_DIR =	src/pars/
PARS_SRC =	pars_char.c \
			pars_texture.c \
			parsing.c \
			utils_pars.c \
			check_texture.c

GAME_DIR =	src/game/
GAME_SRC =	start_game.c \
			utils_game.c \
			minimap_full.c \
			minimap_player.c \
			draw_utils.c \
			movement.c

FILES 	+=	$(addprefix $(PARS_DIR), $(PARS_SRC:.c=.o))


DIR_SRCS	=	src/
SRCS 		=	main.c

FILES		+=	$(addprefix $(DIR_SRCS), $(SRCS:.c=.o))


OBJS	=	$(addprefix $(DIR_SRCS), $(SRCS:.c=.o)) \
			$(addprefix $(GNL_DIR), $(GNL_SRC:.c=.o)) \
			$(addprefix $(PARS_DIR), $(PARS_SRC:.c=.o)) \
			$(addprefix $(GAME_DIR), $(GAME_SRC:.c=.o))


all: $(NAME)

$(NAME): $(LIBFT) $(DIR_OBJS) mlx/libmlx.a $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(MLXFLAGS)
	echo "$(GREEN)✅ $(NAME) compilated !"
	@norminette src/ | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(WHITE)"}'

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INC) Makefile | libft $(LIBFT)
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	cc $(CFLAGS) -c $< -o $@
	printf "$(ERASE)"

mlx/libmlx.a:
	make -C mlx

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT): force
	make -C libft

force :

clean:
	echo "$(PURPLE)🧹Removing $(NAME).o files !"
	rm -rf $(DIR_OBJS)
	rm -rf getnextline/*.o
	rm -rf src/pars/*.o
	rm -rf src/game/*.o
	rm -rf src/*.o
	make clean -C mlx/
	make clean -C ./$(LIB_DIR)

fclean: clean
	echo "$(PURPLE)🧹Removing $(NAME:.a=) !"
	rm -f $(NAME)
	make fclean -C ./$(LIB_DIR)

re: fclean $(NAME)

.PHONY: clean fclean re all

.SILENT:
