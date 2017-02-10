##
## Makefile for  in /home/wasta-geek/rendu/CPP/cpp_arcade/games
## 
## Made by Wasta-Geek
## Login   <ducate_c@epitech.net>
## 
## Started on  Tue Mar 15 16:20:32 2016 Wasta-Geek
## Last update Sun Apr  3 13:47:15 2016 Wasta-Geek
##

NAME1	=	lib_arcade_snake.so

NAME2	=	lib_arcade_solarfox.so

SRC1	=	Map.cpp		\
		Snake.cpp	\
		Score.cpp	\
		Play_Snake.cpp	\

SRC2	=	Map.cpp		\
		Score.cpp	\
		SolarFox.cpp	\
		Enemy.cpp	\
		Play_Solarfox.cpp	\

OBJ1	=	$(SRC1:.cpp=.o)

OBJ2	=	$(SRC2:.cpp=.o)

CC	=	g++

INC	=	-I ./../include

CPPFLAGS	+= -W -Wall -Wextra $(INC) -std=c++11 -fPIC -g

all:		$(NAME1) $(NAME2)

$(NAME1):	$(OBJ1)
		$(CC) $(OBJ1) $(CPPFLAGS) -shared -o $(NAME1)

$(NAME2):	$(OBJ2)
		$(CC) $(OBJ2) $(CPPFLAGS) -shared -o $(NAME2)

clean:
		rm -rf $(OBJ1) $(OBJ2)

fclean:		clean
		rm -rf $(NAME1) $(NAME2)

re:		fclean all
