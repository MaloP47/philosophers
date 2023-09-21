# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 14:03:32 by mpeulet           #+#    #+#              #
#    Updated: 2023/09/21 16:39:04 by mpeulet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors / base 16 / Bright

DEF_COLOR		= \033[0;39m
GREY			= \033[0;90m
RED				= \033[0;91m
GREEN			= \033[0;92m
YELLOW			= \033[0;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m

#Colors / Perso / Bright

ORANGE			= \033[38;5;214m

#Variables

NAME			= philo
CC				= cc
FLAGS			= -Wall -Werror -Wextra -pthread #-g3 -O2 -fsanitize=thread
RM				= rm -rf
TXT				= *txt
VCF				= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
ERR				= 2>> error.txt
MESS			= 3>> message.txt
AR				= ar rcs
NORM			= ./includes
INCLUDE			= 	-I ./includes/

#Sources

OBJ_DIR_P 		= obj/
SRC_DIR_P		= src/
SRC_FUNCTIONS_P	= clean_exit parsing_printing philosopher philosopher_bis routine utils 

PHIL_SRC		= $(addprefix $(SRC_DIR_P), $(addsuffix .c, $(SRC_FUNCTIONS_P)))
PHIL_OBJ		= $(addprefix $(OBJ_DIR_P), $(addsuffix .o, $(SRC_FUNCTIONS_P)))

IFMAKE_DIR_P	= .cache_exists

all:			$(NAME)

$(IFMAKE_DIR_P):
					@mkdir -p $(OBJ_DIR_P)

$(OBJ_DIR_P)%.o: $(SRC_DIR_P)%.c | $(IFMAKE_DIR_P)
					@echo "$(ORANGE)Loading... $< $(DEF_COLOR)"
					@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(PHIL_OBJ)
					@echo "$(GREY)Compiling philo...$(DEF_COLOR)"
					@$(CC) $(FLAGS) -o $(NAME) src/main.c $(PHIL_OBJ) $(INCLUDE)
					@echo "$(GREEN)philo ready.$(DEF_COLOR)"

clean:
					@echo "$(MAGENTA)philo objects files cleaned!$(DEF_COLOR)"
					@$(RM) $(OBJ_DIR_P)
					
fclean:			clean
					@echo "$(RED)philo removed.$(DEF_COLOR)"
					@$(RM) $(NAME)
					@$(RM) $(TXT)

re:				fclean all
					@echo "$(BLUE)Cleaned and rebuilt everything for philo$(DEF_COLOR)"

norm:
					@norminette $(SRC_DIR_P) $(NORM) | grep -A1 -B1 Error | grep -v 'OK!' || true
					@echo "$(RED)Norminet $(ORANGE)the $(YELLOW)cat $(GREEN)says$(CYAN): $(RED)M$(ORANGE)e$(YELLOW)o$(GREEN)w$(CYAN) !$(BLUE)!$(MAGENTA)!$(DEF_COLOR)"

.PHONY: all clean fclean re norm