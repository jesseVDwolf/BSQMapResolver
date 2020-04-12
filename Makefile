NAME = bsq

SRCDIR = srcs

HEADDIR = includes

SRC = $(SRCDIR)/ft.c \
	  $(SRCDIR)/grid.c \
	  $(SRCDIR)/map.c \
	  $(SRCDIR)/main.c

OBJ = ft.o \
	  grid.o \
	  map.o \
	  main.o

all : $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c -I$(HEADDIR) $(SRC)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
