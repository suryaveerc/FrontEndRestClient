CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall
DEBUG = -g
OBJS = RepositoryAccessClient.o RepositoryHandler.o cJSON.o Util.o Test.o
EXEC = WSClient
LIBS = -lcurl -lm

all : WSClient

WSClient : $(OBJS)
	gcc $(OBJS) $(LFLAGS) $(LIBS) -o WSClient


RepositoryAccessClient.o : RepositoryAccessClient.c RepositoryAccessClient.h
	gcc $(CFLAGS) RepositoryAccessClient.c

RepositoryHandler.o : RepositoryHandler.c Util.h Common.h
	gcc $(CFLAGS) RepositoryHandler.c

cJSON.o : cJSON.c cJSON.h
	gcc $(CFLAGS) cJSON.c

Util.o : Util.c Util.h Common.h cJSON.h
	gcc $(CFLAGS) Util.c
	
Test.o : Test.c
	gcc $(CFLAGS) Test.c

clean:
	\rm *.o *~ WSClient
