NAME    = cub3D

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iminilibx-linux
MLX_LNK = -Lminilibx-linux -lmlx -lXext -lX11 -lm
MLX_LIB = minilibx-linux/libmlx.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS = \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/args1.c \
    $(SRC_DIR)/flood1.c \
    $(SRC_DIR)/flood2.c \
    $(SRC_DIR)/map1.c \
    $(SRC_DIR)/map2.c \
    $(SRC_DIR)/minilib1.c \
    $(SRC_DIR)/minilib2.c \
    $(SRC_DIR)/minilib3.c \
    $(SRC_DIR)/minilib4.c \
    $(SRC_DIR)/parsing1.c \
    $(SRC_DIR)/parsing2.c \
    $(SRC_DIR)/parsing3.c \
    $(SRC_DIR)/parsing4.c \
    $(SRC_DIR)/parsing5.c \
    $(SRC_DIR)/parsing6.c \
    $(SRC_DIR)/raycast1.c \
    $(SRC_DIR)/raycast2.c \
    $(SRC_DIR)/raycast3.c \
    $(SRC_DIR)/utils1.c \
    $(SRC_DIR)/utils2.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(MLX_LIB):
	@make -C minilibx-linux

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(OBJS) $(MLX_LNK) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re