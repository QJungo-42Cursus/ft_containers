NAME =     	tests_out
CC =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98
RM =		rm -f
GTEST =		/usr/local/lib/libgtest.a

SRCS =		rbtree/NodeTest.cpp tests/main.cpp

OBJS =		$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): build
	./$(NAME)

build: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(GTEST)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
