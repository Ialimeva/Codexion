NAME		:= 	codexion
CFLAGS		:= 	-Wall -Wextra -Werror -g -pthread #TODO: Remove -g
OBJ_DIR		:= 	OBJ
SOURCE_DIR	:= 	src
FILES 		:=	cleanup.c coder.c coder_routines.c coder_utils.c \
				dongle.c heap.c heap_op.c main.c \
				monitor.c monitor_utils.c parser.c simulation.c utils.c 
SOURCE 		:=	$(addprefix $(SOURCE_DIR)/, $(FILES))
OBJECTS 	:=	$(SOURCE:$(SOURCE_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@echo "Build Successful"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c | $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
