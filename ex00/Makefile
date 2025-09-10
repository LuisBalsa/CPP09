

NAME = easyfind

SRC = main.cpp
DEPS = easyfind.hpp

VPATH = sources includes
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(SRC:.cpp=.o))
DEPS_PATH = includes/


CC = c++

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98

UP = "\033[A"
CUT = "\033[K"


all: $(NAME)


$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I $(DEPS_PATH)
	@echo "Compiling" $(NAME) "done"

$(OBJ_PATH)%.o: %.cpp $(DEPS)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@ -I $(DEPS_PATH)
	@echo -n $(UP)$(CUT)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
