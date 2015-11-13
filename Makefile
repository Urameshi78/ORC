PROJECT = ocr

CXX = c++

SRCS_DIR = sources
INC_DIR = includes

SRCS = $(shell find $(SRCS_DIR) -name "*.cpp")
OBJS		= $(SRCS:.cpp=.o)

INCLUDES 	= -I ./includes
CXXFLAGS 	= -g -Wall -std=c++11 $(INCLUDES)
LIBS 			= `pkg-config opencv --libs`

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CXX) -o  $(PROJECT) $(OBJS) $(LIBS)


clean:
	rm -fr $(OBJS)

fclean: clean
	rm -fr build/$(PROJECT)

re: fclean all

run : $(PROJECT)
	./$(PROJECT) sets/training_sets training_set.text training_set.text
