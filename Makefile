NAME= sand

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

SOURCES= new_main.c game_loop.c sdl_functions.c
INCLUDES= sand.h
OBJ_NAME = $(SOURCES:.c=.o)

INC = $(addprefix $(INC_PATH), $(INCLUDES))
SRC = $(addprefix $(SRC_PATH), $(SOURCES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAG = -Wall -Wextra -fsanitize=address

all:
	make $(NAME)

$(NAME): $(OBJ) Makefile
	gcc $(FLAG) -o ${NAME} $(OBJ) -I . -lSDL2 -Wl,-rpath=/usr/local/lib -lSDL2_image

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	gcc $(FLAG) -g -I $(INC_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf ${NAME}

re: fclean all
