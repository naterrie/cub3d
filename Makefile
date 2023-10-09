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

HEADERS	=	cub3d.h\
			pars.h\

CFLAGS	=	-Wall -Werror -Wextra -I $(INC_DIR) -I $(GNL_DIR) -g3

MLXFLAGS	= -L ./mlx -lmlx -lXext -lX11 -lm -lbsd

LIB_DIR	=	libft/
LIBFT	= $(addprefix $(LIB_DIR), libft.a)


INC_DIR	=	includes/
INC		=	$(addprefix $(INC_DIR), $(HEADERS))

GNL_DIR =	getnextline/
GNL_SRC =	get_next_line.c \
			get_next_line_utils.c
INC_GNL	=	get_next_line.h
INC		+=	$(addprefix $(GNL_DIR), $(INC_GNL))

OBJS	=	$(addprefix $(DIR_OBJS), $(GNL_SRC:.c=.o))

DIR_SRCS	=	src/

FILES		=	main.c

PARS_DIR =	pars/
PARS_SRC =	pars_char.c \
			pars_texture.c \
			parsing.c \
			utils_pars.c \
			check_texture.c

FILES	+=	$(addprefix $(PARS_DIR), $(PARS_SRC))

GAME_DIR =	game/
GAME_SRC =	start_game.c \
			utils_game.c \
			minimap_full.c \
			minimap_player.c \
			draw_utils.c \
			movement.c

FILES	 +=	$(addprefix $(GAME_DIR), $(GAME_SRC))

OBJS	+=	$(addprefix $(DIR_OBJS), $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(DIR_OBJS) mlx/libmlx.a $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(MLXFLAGS)
	echo "$(GREEN)✅ $(NAME) compilated !"
	@norminette src/ | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(WHITE)"}'

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c $(INC) Makefile
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	cc $(CFLAGS) -c $< -o $@
	printf "$(ERASE)"

$(DIR_OBJS)%.o: $(GNL_DIR)%.c $(INC) Makefile
	echo "$(GREEN)⏳ Making $(NAME)"
	printf "$(BLEU) ⮡ Making $(RESET)$@$(RED)"
	cc $(CFLAGS) -c $< -o $@
	printf "$(ERASE)"

mlx/libmlx.a:
	make -C mlx

$(DIR_OBJS):
	mkdir -p $@$(PARS_DIR) $@$(GAME_DIR)

$(LIBFT): force
	make -C libft

force :

clean:
	echo "$(PURPLE)🧹Removing $(NAME).o files !"
	rm -rf $(DIR_OBJS)
	make clean -C mlx/
	make clean -C ./$(LIB_DIR)

fclean: clean
	echo "$(PURPLE)🧹Removing $(NAME:.a=) !"
	rm -f $(NAME)
	make fclean -C ./$(LIB_DIR)

re: fclean $(NAME)

.PHONY: clean fclean re all

.SILENT: