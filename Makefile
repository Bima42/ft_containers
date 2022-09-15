NAME = containers

SRCS =	src/main.cpp \
		src/tests_map.cpp \
		src/tests_vector.cpp \
		src/tests_stack.cpp

CC = g++-11
FLAGS = -Wall -Wextra -Werror -pedantic -g
CPP_FLAGS = #-std=c++98

OBJS = $(SRCS:.cpp=.o)

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)

%.o: %.cpp
			@echo $(Y)Compiling [$<]...$(X)
			@$(CC) $(FLAGS) $(CPP_FLAGS) -c $< -o $@
			@printf $(UP)$(CUT)

$(NAME) :	$(OBJS)
			@echo $(Y)Compiling [$(SRCS)]...$(X)
			@echo $(G)Finished [$(SRCS)]$(X)
			@echo
			@echo $(Y)Compiling [$(NAME)]...$(X)
			@$(CC) $(FLAGS) $(CPP_FLAGS) -o $(NAME) $(OBJS)
			@echo $(G)Finished [$(NAME)]$(X)

clean:
			@rm -rf $(OBJS)
			@echo $(R)Removed [$(OBJS)]$(X)

fclean: clean
			@rm -rf $(NAME)
			@echo $(R)Removed [$(NAME)]$(X)

re : fclean all

.PHONY: all clean fclean re
