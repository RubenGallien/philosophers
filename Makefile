NAME = philo

SRC_DIR	= src
OBJ_DIR = obj

SRCS	=	philo.c \
			parsing.c \
			init.c \
			utils.c

SRCS	:= $(SRCS:%=$(SRC_DIR)/%)
OBJS	=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -pthread
CPPFLAGS	= -I include  -I/usr/include

RM			= rm -f
RMDIR		= rmdir
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBNAME) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
		$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) $(OBJS); \
		$(RMDIR) $(OBJ_DIR); \
	fi


fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
.SILENT: