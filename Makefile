#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
BULE = \e[1;34m
YELL = \e[0;33m
TCOL = $(CYAN)
RMD = $(GREEN)successfully $(RED)removed$(NOCOL)
CMP = $(GREEN)successfully compiled$(NOCOL)
ALC = $(YELL)already compiled$(NOCOL)

#----------------------------------------------

CC = cc

RM = /bin/rm -rf

FLAGS = -Wall -Werror -Wextra -g

MLX_FLAGS = -lm -lX11 -lXext

NAME = connect4

GAMEMODE = 0

#paths-----------------------------------------

LIBFT_F = Libft/
MAIN_F = main/
UTS_F = utils/
CN4_F = src/
OBJ_F = obj/
MLX_PATH = minilibx
MLX_ARC = minilibx/libmlx_Linux.a

#libft-----------------------------------------

LIBFT = libft.a

#connect_4-------------------------------------

CN4 = main.c \
	game.c \
	move.c \
	cpu.c \
	cpu_smart.c \
	cpu_smart_2.c \
	status_update.c \
	win_check.c \
	print_mat.c \
	game_mlx.c \
	cpu_mlx.c \
	log_list.c

#utils-----------------------------------------

UTS = err_check.c \
	mat_functions.c \
	mat_chars.c

#prefix----------------------------------------

LIBFT := $(addprefix $(LIBFT_F),$(LIBFT))
UTS := $(addprefix $(UTS_F),$(UTS))
CN4 := $(addprefix $(CN4_F),$(CN4))

SRC = $(UTS) $(CN4)

OBJ = $(SRC:.c=.o)

%.o: %.c
	mkdir -p $(OBJ_F)
	${CC} ${CFLAGS} -D GAMEMODE=$(GAMEMODE) -c $< -o $@

#rules-----------------------------------------

all: $(NAME)

$(NAME): minilibx libcomp $(OBJ)
		$(CC) $(FLAGS) -D GAMEMODE=$(GAMEMODE) $(OBJ) $(LIBFT) $(MLX_ARC) -o $(NAME) $(MLX_FLAGS)
		echo "$(TCOL)$(NAME) $(CMP)"

setpvp:
	$(eval GAMEMODE := 1)

pvp: fclean setpvp $(NAME)

pve: re

clean:		libclean
		$(RM) $(OBJ)
		$(RM) $(OBJ_F)

fclean:   	libfclean clean
		if [ -f $(NAME) ]; then\
			$(RM) $(NAME);\
			echo "$(TCOL)$(NAME) $(RMD)";\
		fi

libcomp:
		@make -C $(LIBFT_F)

libclean:
		@make clean -C $(LIBFT_F)

libfclean:
		@make fclean -C $(LIBFT_F)

minilibx:
	@make -sC $(MLX_PATH)
	@cp $(MLX_PATH)/mlx.h $(CN4_F)/mlx.h

re: fclean all

.PHONY: $(NAME) all re clean fclean setpvp pvp pve libcomp libclean libfclean minilibx

.SILENT: