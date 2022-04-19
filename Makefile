############################
###   Program/s name/s   ###
############################

NAME = minishell

LIBFT_NAME = libft.a

##############################
###   Compiler and flags   ###
##############################

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I ./$(INC_PATH) -I ./$(LIB_PATH)/inc
LIBS = -lreadline

#CFLAGS += -fsanitize=address -g3

#################
###   Paths   ###
#################

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc
LIB_PATH = libft

##################
###   Source   ###
##################

SRC_DIR_BUILT = built-in
SRC_DIR_PARSE = parse
SRC_DIR_INIT = init

SUBSRC_DIR_NAME = $(SRC_DIR_BUILT) \
		  $(SRC_DIR_INIT) \
		  $(SRC_DIR_PARSE)

SRC_DIR_NAME = $(addprefix $(SRC_PATH)/, $(SUBSRC_DIR_NAME))

OBJ_DIR_NAME = $(addprefix $(OBJ_PATH)/, $(SUBSRC_DIR_NAME))

########################
###   Source items   ###
########################

SRC_MAIN = main.c

SRCS_BUILTIN = builtin.c \
	    cd.c \
	    pwd.c \
	    env.c \
	    unset.c \
	    exit.c \
	    utils_unset.c \
	    export.c \
	    utils_export.c \
	    error.c \
	    utils.c \
	    utils_list.c \
	    echo.c

SRCS_PARSE = expansions.c \
	     quote_handling.c \
	     reading.c \
	     reading_utils.c

SRCS_INIT = init_shell.c

SRC_NAME = $(SRC_MAIN) \
	   $(addprefix $(SRC_DIR_BUILT)/, $(SRCS_BUILTIN)) \
	   $(addprefix $(SRC_DIR_INIT)/, $(SRCS_INIT)) \
	   $(addprefix $(SRC_DIR_PARSE)/, $(SRCS_PARSE))

######################
###   Make rules   ###
######################

MAKE = make

##########################
###   Create objects   ###
##########################

OBJ_NAME = $(SRC_NAME:%.c=%.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

################
###   Name   ###
################

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $@ $(LIBS)

##########################
###   Create folders   ###
##########################

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_DIR_NAME)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_NAME): | $(OBJ_PATH)
	mkdir -p $(OBJ_DIR_NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

########################
###   Compile libs   ###
########################

$(LIBFT_NAME):
	$(MAKE) all -sC $(LIB_PATH)
	cp -r $(addprefix $(LIB_PATH)/, $(LIBFT_NAME)) $(LIBFT_NAME)

#######################
###   Other rules   ###
#######################

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) fclean -sC $(LIB_PATH)
	rm $(LIBFT_NAME)
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
