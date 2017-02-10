##
## Makefile for  in /home/descam_d/workspace/cpp_nanotekspice
##
## Made by Corentin Descamps
## Login   <descam_d@epitech.net>
##
## Started on  Mon Feb  8 12:01:38 2016 Corentin Descamps
## Last update Sun Apr  3 14:56:07 2016 Antoine Lempereur
##

NAME	=	../lib_arcade_opengl.so

SRC	=	src/DispOpengl.cpp \
		src/MediaHandler.cpp \
		../Common/src/AModule.cpp \
		../Common/src/ADisplay.cpp \
		../../games/Map.cpp \
		../Common/src/Menu.cpp \
		../../core/Core.cpp \
		../../core/Errors.cpp \
		../../games/Score.cpp	\
		src/Ressources.cpp \
		src/ModuleSfml.cpp \

OBJ	=	$(SRC:.cpp=.o)

CC	=	g++

INC	=	-I ./../../include -I ./../Sfml/SFML/ -I./include -I. -I./../Common/include

CPPFLAGS	+= -W -Wall -Wextra $(INC) -std=c++11 -fPIC -g
CPPFLAGS        += -L./SFML -lsfml-graphics  -lsfml-window -lsfml-system -lsfml-audio -ldl -rdynamic -DSFML_STATIC -lGL -lGLEW

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CPPFLAGS) -shared -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
