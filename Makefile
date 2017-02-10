##
## Makefile for  in /home/descam_d/workspace/cpp_nanotekspice
##
## Made by Corentin Descamps
## Login   <descam_d@epitech.net>
##
## Started on  Mon Feb  8 12:01:38 2016 Corentin Descamps
## Last update Sat Apr  2 16:16:33 2016 Wasta-Geek
##

NAME	=	arcade

MAIN	=	main.cpp \
		core/DLLoader.cpp \
		core/Errors.cpp \
		core/Core.cpp \

OBJ	=	$(MAIN:.cpp=.o)

CC	=	g++

INC	=	-I ./include

CPPFLAGS	+= -W -Wall -Wextra $(INC) -std=c++11 -fPIC -g

all:		$(NAME)
		make -C ./lib/Caca/ || make -C ./games
		make -C ./lib/Sfml/ || make -C ./games
		make -C ./lib/Opengl/ || make -C ./games
		make -C ./games

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) -ldl

clean:
		rm -rf $(OBJ)
		make clean -C ./lib/Caca/
		make clean -C ./lib/Sfml/
		make clean -C ./lib/Opengl/
		make clean -C ./games

fclean:		clean
		rm -rf $(NAME)
		make fclean -C ./lib/Caca/
		make fclean -C ./lib/Sfml/
		make fclean -C ./lib/Opengl/
		make fclean -C ./games

re:		fclean all
