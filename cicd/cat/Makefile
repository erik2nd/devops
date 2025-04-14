CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TARGET = ../cat/s21_cat
SOURCES = cat.c s21_cat_main.c
OBJECTS = $(SOURCES:.c=.o)

all: s21_cat

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) -o $(TARGET)

rebuild: clean all

s21_cat: $(TARGET)
	rm -rf $(OBJECTS)
	
test: s21_cat
	sh test.sh

	
	
