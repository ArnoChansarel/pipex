# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arnalove <arnalove@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 12:04:10 by arnalove          #+#    #+#              #
#   Updated: 2023/01/05 14:56:43 by arnalove         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#TARGET
NAME = pipex

#ARGUMENTS
CC = gcc
FLAGS = -Wall -Werror -Wextra 
#SEG = -fsanitize=address -g

#PIPEX FILES
SRC_PATH = ./srcs/
SRC = 	pipex \
		parsing \
		children \
		utils
C_FILES = $(addprefix $(SRC_PATH), $(SRC:=.c))
OBJ = $(addprefix $(SRC_PATH), $(SRC:=.o))

#PIPEX BONUS FILES
SRC_PATH_BONUS = ./srcs_bonus/
SRC_BONUS = pipex_bonus \
			parsing_bonus \
			children_bonus \
			utils_bonus
C_FILES_BONUS = $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS:=.c))
OBJ_BONUS = $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS:=.o))

#LIBFT
LBFT_PATH = ./libft/
LBFT = 	ft_split \
		ft_strlcpy \
		ft_strjoin \
		ft_strlen \
		ft_substr \
		ft_strncmp \
		ft_strnstr
LBFT_FILES = $(addprefix $(LBFT_PATH), $(LBFT:=.c))
LBFT_OBJ = $(addprefix $(LBFT_PATH), $(LBFT:=.o))

#RULES
all: $(NAME)

$(NAME): $(OBJ) $(LBFT_OBJ)
	@ $(CC) $(FLAGS) $(OBJ) $(LBFT_OBJ) -o $(NAME)

bonus: $(OBJ_BONUS) $(LBFT_OBJ)
	@ $(CC) $(FLAGS) $(OBJ_BONUS) $(LBFT_OBJ) -o $(NAME)

.c.o:
	@ $(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(LBFT_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re