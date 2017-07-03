NAME	= fdf

INCL	= -I./libft/includes \
			-I./mlx \
			-I./fdf.h

SFILE	= fdf.c \
			fdf_window.c \
			fdf_draw.c \
			fdf_hook.c \
			fdf_color.c

SRC		= $(addprefix $(SDIR), $(SFILE))
SDIR	= ./

LFILE	= ./libft/libft.a \
			./mlx/libmlx.a
LIB		= -L./libft -lft \
			-L./mlx -lmlx
LDIR	= ./libft

OFILE	= $(SRC:.c=.o)
OBJ		= $(addprefix $(ODIR), $(OFILE))
ODIR	= ./obj/

CC		= gcc
FLAG	= -Wall -Wextra -Werror
FRAME	= -framework OpenGL -framework AppKit
RM		= rm -rf
MC		= make -C

all: $(LIB) $(NAME)

lib: $(LIB)

$(LIB):
	@$(MC) $(LDIR)
	@$(MC) ./mlx

$(ODIR)%.o: %.c
	@$(CC) -c $(FLAG) $(INCL) -c $< -o $@

ofile:
	@mkdir -p $(ODIR)

$(NAME): ofile $(OBJ)
	@$(CC) -o $(NAME) $(FRAME) $(OBJ) $(LIB)

clean:
	@$(MC) $(LDIR) clean
	@$(RM) ./mlx/*.o
	@$(RM) $(ODIR)

fclean: clean
	@$(RM) $(LFILE)
	@$(RM) $(NAME)

re: fclean all
