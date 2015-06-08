CC=gcc
CFLAGS = -g -Wall
TARGET = ncwebserver
SOURCES = $(wildcard src/*.c)

all: $(TARGET)

clean:
	$(RM) $(TARGET)

$(TARGET):
	cc $(SOURCES) -o ncwebserver