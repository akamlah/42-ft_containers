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

CLASSES = \

INTERFACES = \

OTHER_CPPFILES = \

TEMPLATES_HPP = \
	vector.hpp \

OTHER_HEADERS = \
	ANSIpalette.h \

# ********************************************************************* #
# internal setup:
# (Classes must have .cpp/.hpp extension to be compiled)

CLASS_CPP := $(addsuffix .cpp, $(CLASSES))
CLASS_HPP := $(addsuffix .hpp, $(CLASSES))

INTERFACES_HPP := $(addsuffix .hpp, $(INTERFACES))

SOURCES = $(CLASS_CPP) $(ENTRY_POINT) $(OTHER_CPPFILES)
HEADER_DEPS = $(CLASS_HPP) $(INTERFACES_HPP) $(TEMPLATES_HPP) $(OTHER_HEADERS)

# ********************************************************************* #
# compile:

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): fclean $(SOURCES) $(HEADER_DEPS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NAME) $(SOURCES) -DSTD=0 -DDBG=0

.PHONY = clean

clean:
	@ rm -rf $(EXECUTABLE_NAME)

fclean: clean
	@ rm -f $(EXECUTABLE_NAME)
	@ rm -rf *.dSYM

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

comp:
	./std_compare/compare.sh