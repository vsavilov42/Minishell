############################
###   Program/s name/s   ###
############################

NAME = minishell

LIBFT_NAME = libft.a

##############
###   OS   ###
##############

UNAME_S := $(shell uname -s)

##############################
###   Compiler and flags   ###
##############################

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFLAGS += -I ./$(INC_PATH) -I ./$(LIB_PATH)/inc

#CFLAGS += -fsanitize=address -g3

#################
###   Paths   ###
#################

SRC_PATH = src

OBJ_PATH = obj

INC_PATH = inc

LIB_PATH = libft

#######################
###   Directories   ###
#######################

SRC_DIR_LEXER =	lexer
SRC_DIR_EXEC =	exec
SRC_DIR_PARSER = parser
SRC_DIR_BUILTIN = built-in
SRC_DIR_UTILS = utils

OBJ_DIR_ALL =	$(SRC_DIR_LEXER) \
		$(SRC_DIR_PARSER) \
		$(SRC_DIR_EXEC) \
		$(SRC_DIR_BUILTIN) \
		$(SRC_DIR_UTILS)

OBJ_DIR = $(addprefix $(OBJ_PATH)/, $(OBJ_DIR_ALL))

########################
###   Source items   ###
########################

SRCS_MAIN =		main.c

SRCS_EXEC =		command_analyze.c

SRCS_LEXER =	reading.c		reading_utils.c		quote_handling.c \
		expansions.c

SRCS_PARSER =	parse.c			remove_quotes.c		parse_utils.c

SRCS_BUILTIN =	builtin.c		cd.c			pwd.c \
		env.c			unset.c			exit.c \
		unset_utils.c		export.c		export_utils.c	\
		error.c			echo.c \

SRCS_UTILS =	utils.c			utils2.c		signals.c \
		free_all.c		envlst.c 		envlst2.c \
		init_shell.c		get_env.c \

SRCS_NAME =	$(SRCS_MAIN) \
		$(addprefix $(SRC_DIR_LEXER)/, $(SRCS_LEXER)) \
		$(addprefix $(SRC_DIR_EXEC)/, $(SRCS_EXEC)) \
		$(addprefix $(SRC_DIR_PARSER)/, $(SRCS_PARSER)) \
		$(addprefix $(SRC_DIR_BUILTIN)/, $(SRCS_BUILTIN)) \
		$(addprefix $(SRC_DIR_UTILS)/, $(SRCS_UTILS))

######################
###   Make rules   ###
######################

MAKE = make

##########################
###   Create objects   ###
##########################

OBJS_NAME = $(SRCS_NAME:%.c=%.o)

SRCS = $(addprefix $(SRC_PATH)/, $(SRCS_NAME))

OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME))

#################################
###   Rules can be executed   ###
#################################

all: $(NAME)

## Object dir

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR): | $(OBJ_PATH)
	mkdir -p $(OBJ_DIR)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2> /dev/null

########################
###   Compile libs   ###
########################

$(LIBFT_NAME):
	$(MAKE) all -sC $(LIB_PATH)
	cp -r $(addprefix $(LIB_PATH)/, $(LIBFT_NAME)) $(LIBFT_NAME)

######################
###   Compile .o   ###
######################

$(NAME): $(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_NAME) -lreadline

############################
###   Sanitize (Linux)   ###
############################
ifeq ($(UNAME_S),Linux)
sanitize: CFLAGS += -lreadline -pedantic -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null
endif
ifeq ($(UNAME_S),Darwin)
sanitize: CFLAGS += -pedantic -g3 -fsanitize=address
endif
sanitize: $(NAME)

#######################
###   Other rules   ###
#######################

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(LIBFT_NAME)

fclean: clean
	$(MAKE) fclean -sC $(LIB_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
