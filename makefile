all: client worker server_launcher server_d


objects_and_exe = client  server_launcher server_d client.o server_launcher.o server_d.o worker.o worker
CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -pthread -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

clean:
	$(RM) $(objects_and_exe)


client: client.o
	$(CC) -o $@ $^ $(LDFLAGS)

server_d: server_d.o
	$(CC) -o $@ $^ $(LDFLAGS)

server_launcher: server_launcher.o
	$(CC) -o $@ $^ $(LDFLAGS)

worker: worker.o
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -c $< $(CFLAGS)


