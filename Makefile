CXX		= clang++
NAME		= npuzzle
CXXFLAGS	= -Wall -Wextra -Werror -std=c++17 -O2
CXXFLAGS	+= -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
CXXFLAGS	+= -lsfml-system -lsfml-window -lsfml-graphics

SRC_PATH	= src/

INCLUDES	= -I include/
INCLUDES	+= -I /usr/include/opencv4
INCLUDES	+= -I ~/brew/include/opencv4

OBJ		= main.o			\
		  Croped_image_generator.o	\
		  Graphic_displayer.o		\
		  Solver.o

OBJS=$(addprefix $(SRC_PATH), $(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(SRC_PATH)%.o: $(SRC_PATH)%.cpp Makefile
	$(CXX) $(INCLUDES) -c $< -o $@ -O2

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
