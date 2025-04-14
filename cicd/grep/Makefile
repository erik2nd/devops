CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TARGET = ../grep/s21_grep
SOURCES = grep.c s21_grep_main.c
OBJECTS = $(SOURCES:.c=.o)

all: s21_grep

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

s21_grep: $(TARGET)
	rm -rf $(OBJECTS)
	
test: s21_grep
	sh test.sh
	
	
	
