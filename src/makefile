src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lGL -lglut -lpng -lz -lm

all : server client

server: server.c
    $(CC) -o $@ $^ $(LDFLAGS)

client: client.c
    $(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
    rm -f $(obj) server client


# CC = gcc
# EXEC1= server
# EXEC2= client

# all : $(EXEC1) $(EXEC2)

# %.o: %.c
# 	$(CC) -o $@ -c $<

# $(EXEC1) : server.o com_functions.o identification.o game.o com_functions.o
# 	$(CC) -o $(EXEC1) server.o com_functions.o identification.o game.o com_functions.o

# $(EXEC2) : client.o com_functions.o identification.o game.o com_functions.o
# 	$(CC) -o $(EXEC2) client.o com_functions.o identification.o game.o com_functions.o

# server.o : server.c
#   $(CC) -o server.o -c server.c

# client.o : client.c
#   $(CC) -o client.o -c client.c

# com_functions.o : com_functions.c
#   $(CC) -o com_functions.o -c com_functions.c

# identification.o : identification.c
#   $(CC) -o identification.o -c identification.c

# game.o : game.c
#   $(CC) -o game.o -c game.c

# com_functions.o : com_functions.c
#   $(CC) -o com_functions.o -c com_functions.c

# clean:
#   rm -rf *.o 
