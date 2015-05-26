#
# ft_script
#
# Makefile
#

#
# Config
#

# Project name
NAME := ft_script

# Project directories
DIRS := srcs h

# Obj directory
O_DIR := o

# Makefiles to call
LIBS := libft

# Number of threads
THREADS := 1

# C compiler
C_CC := clang

# Linking compiler
LD_CC := clang

# Clang flags
C_FLAGS := -Wall -Wextra -Werror -O2

# Linking flags
LD_FLAGS := -Llibft -lft

# Clang include flags
C_HEADS := -Ilibft -Ih

MAKEMAKE_TMP := tmp_makemake.py

#
# Internal
#

O_FILES := o/srcs/main.o

MSG_0 := printf '\033[0;32m%-13.13s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-13.13s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

o/srcs/main.o: srcs/main.c h/ft_script.h
	@mkdir -p o/srcs 2> /dev/null || true
	@$(MSG_0) $< ; clang $(C_FLAGS) $(C_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p o/srcs $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re

make: fclean
	@curl -f https://raw.githubusercontent.com/Julow/makemake/master/makemake.py > $(MAKEMAKE_TMP)
	@python $(MAKEMAKE_TMP)
	@rm -f $(MAKEMAKE_TMP)
.PHONY: make
