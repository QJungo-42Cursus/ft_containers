NAME =     	tests_out
CC =		c++
CFLAGS =	-Wall -Wextra -Werror 
#CFLAGS =	-Wall -Wextra -Werror -std=c++98 -pedantic-errors

RM =		rm -f
GTEST =		/usr/local/lib/libgtest.a

SRCS =		tests/main.cpp \
			tests/vectorTest.cpp \
			tests/pairTest.cpp \
			tests/RedBlackTreeTest.cpp \
			tests/NodeTest.cpp \
			tests/iterator_traitsTest.cpp \

HEADERS =	rbtree/RedBlackTree.h \
			rbtree/Node.h \
			ft_tl/vector.h \
			ft_tl/set.h \
			ft_tl/stack.h \
			ft_tl/map.h \
			ft_tl/iterator_traits.h \
			ft_tl/pair.h \

%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -c $< -o $@

%.h.gch: %.h
	$(CC) $(CFLAGS) $< -o $@

OBJS =		$(SRCS:.cpp=.o)
HEADERS_OBJS =	$(HEADERS:.h=.h.gch)

PCH = pch.h.gch

all: $(NAME)

$(NAME): build
	./$(NAME)

$(PCH):
	$(CC) $(CFLAGS) pch.h -o $(PCH)

build: $(PCH) $(HEADERS_OBJS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(GTEST)

clean:
	@$(RM) $(OBJS) $(HEADERS_OBJS)

fclean: clean
	@$(RM) $(NAME) $(PCH)

re: fclean build

#### Specific tests ####
# STL
vector: build
	./$(NAME) "--gtest_filter=*VectorTest.*"

map: build
	./$(NAME) "--gtest_filter=*MapTest.*"

stack: build
	./$(NAME) "--gtest_filter=*StackTest.*"

set: build
	./$(NAME) "--gtest_filter=*SetTest.*"

# Other
pair: build # includes the make_pair test
	./$(NAME) "--gtest_filter=*PairTest.*"

iterator_traits: build
	./$(NAME) "--gtest_filter=*IteratorTraitsTest.*"

reverse_iterator: build
	./$(NAME) "--gtest_filter=*ReverseIteratorTest.*"

enable_if: build
	./$(NAME) "--gtest_filter=*EnableIfTest.*"

is_integral: build
	./$(NAME) "--gtest_filter=*IsIntegralTest.*"

equal: build
	./$(NAME) "--gtest_filter=*EqualTest.*"

lexicographical_compare: build
	./$(NAME) "--gtest_filter=*LexicographicalCompareTest.*"

# Mine
rbtree: build
	./$(NAME) "--gtest_filter=*RedBlackTreeTest.*"

node: build
	./$(NAME) "--gtest_filter=*NodeTest.*"

.PHONY: all clean fclean re build vector map stack set pair make_pair iterator_traits reverse_iterator enable_if is_integral equal lexicographical_compare rbtree node
