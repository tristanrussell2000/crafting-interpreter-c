CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g
TARGET = bin/clox
LDFLAGS = 

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,bin/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

bin/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)


