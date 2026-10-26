NAME  = codexion
CFLAGS = -Wall -Wextra -Werror -g #TODO: Remove -g
OBJ_DIR = OBJ
SOURCE_DIR = src
SOURCE = $(shell find $(SOURCE_DIR) -name "*.c" -type f)
OBJECTS := $(SOURCE:$(SOURCE_DIR)/%.c=$(OBJ_DIR)/%.o)

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