#ifndef GREP_H
#define GREP_H

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLAGS 'e', 'i', 'v', 'c', 'l', 'n', 'h', 's', 'f', 'o'
#define FLAGS_COUNT 10

typedef struct Flags {
  int e, i, v, c, l, n, h, s, f, o;
} Flags;

void process_grep(int argc, char *argv[]);
void set_flag(Flags *, char ***, int *, char **, int *, const char);
void print_res(Flags *, const char *, char *, int);
void print_matches(Flags *, regex_t, char *, int, const char *, int, char *);
void set_patterns(char **, char **, int);
void read_lines_from_file(char ***, int *, char **, int);
int files_exist(char **, int);
int file_empty(const char *);
char last_character(const char *);

#endif
