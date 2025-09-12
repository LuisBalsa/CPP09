

NAME = btc
DATAURL = https://cdn.intra.42.fr/document/document/38604/cpp_09.tgz

SRC = main.cpp BitcoinExchange.cpp
DEPS = BitcoinExchange.hpp

VPATH = sources includes
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(SRC:.cpp=.o))
DEPS_PATH = includes/


CC = c++

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98

UP = "\033[A"
CUT = "\033[K"


all: $(NAME) data.csv


$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I $(DEPS_PATH)
	@echo "Compiling" $(NAME) "done"

$(OBJ_PATH)%.o: %.cpp $(DEPS)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) -c $< -o $@ -I $(DEPS_PATH)
	@echo -n $(UP)$(CUT)

data.csv:
	@if [ -f cpp_09.tgz ]; then \
		echo "cpp_09.tgz already exists"; \
	else \
		echo "Downloading cpp_09.tgz..."; \
		wget -q $(DATAURL) || { echo "Failed to download cpp_09.tgz"; exit 0; }; \
	fi; \
	echo -n $(UP)$(CUT); \
	tar --strip-components=1 -xf cpp_09.tgz cpp_09/data.csv; \
	echo "data.csv extracted from ${DATAURL}"; \
	rm -f cpp_09.tgz

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME) data.csv cpp_09.tgz

re: fclean all

.PHONY: all clean fclean re
