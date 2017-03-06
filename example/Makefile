
CC = gcc
TARGET = v4l2

INCLUDEDIR = -I../include
INCLUDEDIR += -I/usr/local/include
CFLAGS = -Wall -Wextra -ggdb -O0 -D_GNU_SOURCE -fgnu89-inline $(INCLUDEDIR)

LIBS = -lv4l2 -lcollections

OBJS = example.o

$(TARGET): $(OBJS)
		$(CC) -o $(TARGET) $(OBJS) $(LIBS)

clean:
		rm -rf $(OBJS) $(TARGET)

purge: clean $(TARGET)

