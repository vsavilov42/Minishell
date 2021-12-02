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

CFLAGS += -O3

CFLAGS += -fsanitize=address -g3

#################
###   Paths   ###
#################

SRC_PATH = src

OBJ_PATH = obj

INC_PATH = inc

LIB_PATH = libft

########################
###   Source items   ###
########################

SRCS_NAME = main.c

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

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
		$(CC) $(CFLAGS) -c $< -o $@

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
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_NAME)

#######################
###   Other rules   ###
#######################

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) fclean -sC $(LIB_PATH)
	rm $(NAME)
	rm $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re
