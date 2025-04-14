#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GNU_FLAGS "--number-nonblank", "-E", "--number", "--squeeze-blank", "-T"
#define STD_FLAGS 'b', 'e', 'n', 's', 't', 'v'
#define GNU_FLAGS_COUNT 5
#define STD_FLAGS_COUNT 6

typedef struct Flags {
  int b, e, n, s, t, v;
} Flags;

void print_text(const char *, Flags);
void print_char(Flags flags, const char ch);
int is_flag(const char *);
int is_gnu_flag(const char *);
int is_std_flag(const char);
int is_correct(const char *);
int fill_flag(Flags *, const char *);
void set_std(Flags *, const char);
void set_gnu(Flags *, const char *);

#endif
