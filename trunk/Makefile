CC=g++
CFLAGS=-Wall -g 
INCPATH=-I/usr/local/include
LIBPATH=-L/usr/local/lib
LIBS=-levent
OBJS=evpp_main.o evpp_query.o

all: test

test: ${OBJS}
	${CC} ${CFLAGS} ${INCPATH} ${LIBPATH} ${OBJS} ${LIBS} -o $@

clean:
	-rm -f *.o test

.cc.o:
	$(CC) $(CFLAGS) ${INCPATH} -c $<
