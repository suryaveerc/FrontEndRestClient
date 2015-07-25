CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall
DEBUG = -g
OBJS = RepositoryAccessClient.o RepositoryHandler.o Util.o
EXEC = WSClient
LIBS = -lcurl

WSClient : $(OBJS)
	gcc $(OBJS) $(LFLAGS) $(LIBS) -o WSClient


RepositoryAccessClient.o : RepositoryAccessClient.c RepositoryAccessClient.h
	gcc $(CFLAGS) RepositoryAccessClient.c

RepositoryHandler.o : RepositoryHandler.c Util.h Common.h
	gcc $(CFLAGS) RepositoryHandler.c

Util.o : Util.c Util.h Common.h
	gcc $(CFLAGS) Util.c

clean:
	\rm *.o *~ WSClient
