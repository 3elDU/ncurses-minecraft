CC = gcc

LDFLAGS= -lncurses -ltinfo

SOURCES = src/*
OBJECTS = $(SOURCES:.c=.0)
TARGET = ncurses-minecraft

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
