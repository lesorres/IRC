NAME =  irc

SRC = $(wildcard *.cpp)

HEADER = 

#FLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.cpp=.o)

all: $(NAME)
$(NAME): $(OBJ) $(HEADER) 
	@clang++ $(OBJ) $(FLAGS) -o $(NAME) -g
%.o:%.cpp $(HEADER)
	@clang++ $(FLAGS) -c $< -o $(<:.cpp=.o) -g
clean: 
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all

run: 
	@./$(NAME)

rerun: re 
	@./$(NAME)

ip:
	@ipconfig getifaddr en0

.PHONY: clean fclean re run rerun
