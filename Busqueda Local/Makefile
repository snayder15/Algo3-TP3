# Macross
# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g -std=c++11

# define the C source files
SRCS = local_main.cpp 

#librerias personales

LIBS= local.cpp ../Heuristica\ Golosa/heuristicaGolosa.cpp

# define the C object files 
OBJS = $(SRCS:.c=.o)

OBJLIBS = $(LIBS:.c=.o)

# define the executable file 
MAIN = local
	
.PHONY: depend clean all

all:	$(MAIN)
		
$(MAIN):	$(OBJS) $(OBJLIBS)
		$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(OBJLIBS) $(LFLAGS)


.c.o:
		$(CC) $(CFLAGS) -c $<  -o $@

clean:
		$(RM) *.o *~ $(MAIN)