# **********************************************************************#
#																		#
#						ft_containers: TESTS							#
#																		#
# ********************************************************************* #

EXECUTABLE_NAME = test_ft_containers

# ********************************************************************* #

CC = clang++

CFLAGS = \
	-Wall -Wextra -Werror \
	-std=c++98 \
	-Wc++98-compat \
	-pedantic

# ********************************************************************* #
# project-specific (setup):

ENTRY_POINT = main.cpp

FT_LIB_DIR = ../src/

CLASSES = \
	TestClass

OTHER_CPPFILES = \
	tests_vector.cpp \
	tests_stack.cpp \
	tests_type_traits_and_utils.cpp \
	tests_map.cpp \

FT_LIB_TEMPLATES = \
	type_traits.hpp \
	iterator.hpp \
	algorithm.hpp \
	utility.hpp \
	vector.hpp \
	stack.hpp \
	rb_tree.hpp \
	map.hpp \
	set.hpp

OTHER_HEADERS = \
	ANSIpalette.h \
	testing.hpp \
	
# ********************************************************************* #
# internal setup:
# (Classes must have .cpp/.hpp extension to be compiled)

CLASS_CPP := $(addsuffix .cpp, $(CLASSES))
CLASS_HPP := $(addsuffix .hpp, $(CLASSES))

FT_LIB_LOCATED_HPPS = $(addprefix $(FT_LIB_DIR), $(FT_LIB_TEMPLATES))

SOURCES = $(CLASS_CPP) $(ENTRY_POINT) $(OTHER_CPPFILES)
HEADER_DEPS = $(CLASS_HPP) $(FT_LIB_LOCATED_HPPS) $(OTHER_HEADERS)

# ********************************************************************* #
# compile all:

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(SOURCES) $(HEADER_DEPS)
	@ echo "\033[38;5;37m =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
	@ $(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -DSTD=0 -DDBG=0
	@ echo "\033[0m"

.PHONY = clean

clean:
	@ rm -rf $(EXECUTABLE_NAME)

fclean: clean
	@ rm -f $(EXECUTABLE_NAME)
	@ rm -rf *.dSYM

ffclean: fclean
	@ rm -rf std_container ft_container ./std_compare/*.out

re: fclean all

# --------------------------------------------------------------------- #
#debug & compare to std

std: $(SOURCES) $(HEADER_DEPS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -DSTD=1

std_dbg: $(SOURCES) $(HEADER_DEPS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -DSTD=1 -DDBG

dbg: fclean $(SOURCES) $(HEADER_DEPS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -DDBG

sani: fclean $(SOURCES) $(HEADER_DEPS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -g3 -fsanitize=address

sani_std: $(SOURCES) $(HEADER_DEPS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -DSTD=1 -g3 -fsanitize=address

comp:
	./std_compare/compare.sh

main1:
	clang++ main1.cpp -o ft_container
	clang++ main1.cpp -o std_container -DSTD
	./ft_container > ./std_compare/main1_ft.out
	./std_container > ./std_compare/main1_std.out
	diff ./std_compare/main1_ft.out ./std_compare/main1_std.out

main2:
	clang++ main2.cpp -o ft_container
	clang++ main2.cpp -o std_container -DSTD
	./ft_container > ./std_compare/main2_ft.out
	./std_container > ./std_compare/main2_std.out
	diff ./std_compare/main2_ft.out ./std_compare/main2_std.out
