# Macross

#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g -std=c++11

# define the C source files
SRCS = ejercicio1.cpp 

#librerias personales

LIBS= dijstra.cpp 

# define the C object files 
OBJS = $(SRCS:.c=.o)

OBJLIBS = $(LIBS:.c=.o)

# define the executable file 
MAIN = problema1

CPP=g++
FLAGS= -std=c++11
TIEMPO=tiempo.cpp
	
.PHONY: depend clean all

all:	$(MAIN)
		@echo compilando todos
		g++ $(FLAGS) $(TIEMPO) $(LIBS) -o $(basename $(TIEMPO))
		
$(MAIN):	$(OBJS) $(OBJLIBS)
		$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(OBJLIBS) $(LFLAGS)


.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN) $(tiempo)
