# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 16:56:48 by vsavilov          #+#    #+#              #
#    Updated: 2021/11/16 11:39:26 by vsavilov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##############################
###   Compiler and flags   ###
##############################

CC = gcc

CFLAGS = -Wall -Werror -Wextra

CFLAGS += -I ./$(INCDIR)

########################
###   Source items   ###
########################

SRCS_NAME = ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_isalpha.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c	 \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_strchr.c \
		ft_strlcpy.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_itoa.c \
		ft_substr.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_split.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c


#######################
###   Directories   ###
#######################

SRCDIR = src

OBJDIR = obj

INCDIR = inc

############################
###   Program/s name/s   ###
############################

NAME = libft.a

#################################
###   Rules can be executed   ###
#################################

all: $(NAME)

##########################
###   Create objects   ###
##########################

SRCS = $(addprefix $(SRCDIR)/, $(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(OBJS_NAME))

#######################
###   Objects dir   ###
#######################

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
		@mkdir -p $(OBJDIR) 2> /dev/null

#####################
###   Compile.o   ###
#####################

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

#######################
###   Other rules   ###
#######################

.PHONY: all clean fclean re

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
