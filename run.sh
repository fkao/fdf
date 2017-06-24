gcc -c fdf.c fdf_tools.c -I./libft.h -I./fdf.h -I./mlx
gcc fdf.o fdf_tools.o -L. -lft -L./mlx -lmlx -framework OpenGL -framework AppKit
rm -rf *.o
