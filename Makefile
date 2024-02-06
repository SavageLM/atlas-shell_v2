CC := gcc
CFLAGS := -Werror -Wall -Wextra -pedantic -std=gnu89

INCDIR := include
SRCDIR := src
BUILDDIR := build

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(addprefix $(BUILDDIR)/, $(patsubst %.c, %.o, $(notdir $(SRC))))
HEAD := $(INCDIR)/_sh.h

NAME := hsh

all: link

$(BUILDDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -I$(INCDIR) $< -o $@

link: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

debug: $(OBJ)
	$(CC) $(CFLAGS) $^ -g -o $(NAME)-debug

release: all debug

clean:
	$(RM) -r $(BUILDDIR)

.PHONY: link debug release clean

$(SRC): $(HEAD)
