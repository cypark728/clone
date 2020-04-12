CC = gcc
CFLAGS = -g -Wall
TARGETS = movie
OBJECTS = movie_main.c movie.o
.SUFFIXEX = .c .o

movie_debug : $(TARGETS)
movie_debug : DEBUGOPTION = -DDEBUG

$(TARGETS) : $(OBJECTS)
	$(CC) $(CFLAGS) $(DEBUGOPTION) -o $@ $^

.c.o :
	$(CC) $(CFLAGS) $(DEBUGOPTION) -c $<

clean :
	rm *.o

cleanx :
	rm *.o movie
