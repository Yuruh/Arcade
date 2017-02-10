##
## Makefile for  in /home/descam_d/workspace/cpp_nanotekspice
##
## Made by Corentin Descamps
## Login   <descam_d@epitech.net>
##
## Started on  Mon Feb  8 12:01:38 2016 Corentin Descamps
## Last update Sat Mar 19 20:42:38 2016 Antoine Lempereur
##

NAME	=	../lib_arcade_sfml.so

SRC	=	src/DispSfml.cpp \
		src/MediaHandler.cpp \
		../Common/src/AModule.cpp \
		src/ModuleSfml.cpp \
		../Common/src/ADisplay.cpp \
		../../games/Map.cpp \
		../Common/src/Menu.cpp \
		../../core/Core.cpp \
		../../core/Errors.cpp \
		../../games/Score.cpp	\

OBJ	=	$(SRC:.cpp=.o)

CC	=	g++

INC	=	-I ./../../include -I ./SFML/ -I./include -I. -I./../Common/include

CPPFLAGS	+= -W -Wall -Wextra $(INC) -std=c++11 -fPIC -g
CPPFLAGS        += -L./SFML -lsfml-graphics  -lsfml-window -lsfml-system -lsfml-audio -ldl -rdynamic -DSFML_STATIC

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CPPFLAGS) -shared -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
