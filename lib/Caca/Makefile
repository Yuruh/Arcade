##
## Makefile for  in /home/descam_d/workspace/cpp_nanotekspice
##
## Made by Corentin Descamps
## Login   <descam_d@epitech.net>
##
## Started on  Mon Feb  8 12:01:38 2016 Corentin Descamps
## Last update Fri Mar 18 17:00:12 2016 Corentin Descamps
##

NAME	=	../lib_arcade_libcaca.so

SRC	=	src/DispCaca.cpp \
		src/ModuleCaca.cpp \
		../Common/src/AModule.cpp \
		../Common/src/ADisplay.cpp \
		../../games/Map.cpp \
		../Common/src/Menu.cpp \
		../../core/Core.cpp \
		../../core/Errors.cpp \
		../../games/Score.cpp	\

OBJ	=	$(SRC:.cpp=.o)

CC	=	g++

INC	=	-I ./../../include -I ./libcaca/ -I ./include -I ./../Common/include

CPPFLAGS	+= -W -Wall -Wextra $(INC) -std=c++11 -fPIC -g
CPPFLAGS        += -L./libcaca/ -lcaca

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(CPPFLAGS) -shared -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all
