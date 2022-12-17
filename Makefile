NAME =     	tests_out
CC =		c++
CFLAGS =	-Wall -Wextra -Werror 
#CFLAGS =	-std=c++98 -Wall -Wextra -Werror 
RM =		rm -f
GTEST =		/usr/local/lib/libgtest.a

SRCS =		tests/RedBlackTreeTest.cpp \
			tests/NodeTest.cpp \
			tests/vectorTest.cpp \
			tests/pairTest.cpp \
			tests/main.cpp

HEADERS =	rbtree/RedBlackTree.h \
			rbtree/Node.h \
			ft_tl/vector.h \
			ft_tl/set.h \
			ft_tl/stack.h \
			ft_tl/map.h \
			ft_tl/pair.h

OBJS =		$(SRCS:.cpp=.o)

# permet de recompiler les fichiers .o si les headers ont ete modifies
# TODO trouver une solution pour ne pas recompiler les fichiers .o qui ne dependent pas des headers
%.o: %.cpp Makefile $(HEADERS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

all: $(NAME)

$(NAME): build
	./$(NAME)


build: ft_tl/pair.h $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(GTEST)


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
