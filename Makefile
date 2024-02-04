SRCDIR := src
BUILDDIR := build
CC := gcc
CFLAGS := -Werror -Wall -Wextra -pedantic -std=gnu89
SRC := $(wildcard $(SRCDIR)/*.c)
HEAD := $(SRCDIR)/header/_sh.h
OBJ := $(addprefix $(BUILDDIR)/, $(patsubst %.c, %.o, $(notdir $(SRC))))
NAME := hsh

all: link

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

link: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

debug: $(OBJ)
	$(CC) $(CFLAGS) $^ -g -o $(NAME)-debug

release: all debug

clean:
	$(RM) -r $(BUILDDIR)

.PHONY: link debug release clean

$(SRC): $(HEAD)
