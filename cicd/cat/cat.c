#include "cat.h"

void print_text(const char *path, Flags flags) {
  FILE *file;
  file = fopen(path, "r");
  if (file == NULL) {
    printf("cat: %s: No such file or directory\n", path);
    return;
  }
  int line_number = 1;
  int empty_line = 0;
  int prev_ch = '\n';
  int ch = ' ';
  while ((ch = fgetc(file)) != EOF) {
    if (flags.s && ch == '\n' && prev_ch == '\n' && empty_line) continue;
    empty_line = ch == '\n' && prev_ch == '\n' ? 1 : 0;
    if (((flags.n && !flags.b) || (flags.b && ch != '\n')) && prev_ch == '\n')
      printf("%6d\t", line_number++);
    if (flags.e && ch == '\n') {
      printf("$");
    }
    if (flags.t && ch == '\t') {
      printf("^I");
      prev_ch = ch;
      continue;
    }
    if (flags.v) {
      if (ch > 127 && ch < 160) printf("M-^");
      if ((ch < 32 && ch != '\n' && ch != '\t') || ch == 127) printf("^");
      if ((ch < 32 || (ch > 126 && ch < 160)) && ch != '\n' && ch != '\t')
        ch = ch > 126 ? ch - 128 + 64 : ch + 64;
    }
    printf("%c", ch);
    prev_ch = ch;
  }
  fclose(file);
}

void print_char(Flags flags, const char ch) {
  static int line = 1;
  if (flags.n) {
    printf("%6d ", line);
    line++;
  }
  if (ch == '\t' && flags.t) {
    printf("^I");
  } else if (ch == '\n' && flags.e)
    printf("$\n");
  else
    putchar(ch);
}

int is_flag(const char *arg) { return arg[0] == '-'; }

int is_gnu_flag(const char *arg) {
  return (strlen(arg) > 1 && arg[0] == '-' && arg[1] == '-') ||
         strcmp(arg, "-E") == 0 || strcmp(arg, "-T") == 0;
}

int is_correct(const char *str) {
  int res = 0;
  const char *gnu_flags[] = {GNU_FLAGS};
  for (int i = 0; i < GNU_FLAGS_COUNT; i++) {
    if (strcmp(str, gnu_flags[i]) == 0) {
      res = 1;
      break;
    }
  }
  return res;
}

int is_std_flag(const char ch) {
  int res = 0;
  const char std_flags[] = {STD_FLAGS};
  for (int i = 0; i < STD_FLAGS_COUNT; i++) {
    if (ch == std_flags[i]) {
      res = 1;
      break;
    }
  }
  return res;
}

int fill_flag(Flags *flags, const char *arg) {
  int res = 1;
  if (is_gnu_flag(arg)) {
    if (is_correct(arg)) {
      set_gnu(flags, arg);
    } else
      res = 0;
  } else {
    for (int i = 1; arg[i] != '\0'; i++) {
      if (!is_std_flag(arg[i])) {
        res = 0;
        break;
      }
      set_std(flags, arg[i]);
    }
  }
  return res;
}

void set_std(Flags *flags, const char ch) {
  switch (ch) {
    case 'b':
      flags->b = 1;
      break;
    case 'e':
      flags->e = 1;
      flags->v = 1;
      break;
    case 'n':
      flags->n = 1;
      break;
    case 's':
      flags->s = 1;
      break;
    case 't':
      flags->t = 1;
      flags->v = 1;
      break;
    case 'v':
      flags->v = 1;
      break;
  }
}

void set_gnu(Flags *flags, const char *str) {
  if (strcmp(str, "--number-nonblank") == 0) flags->b = 1;
  if (strcmp(str, "-E") == 0) flags->e = 1;
  if (strcmp(str, "--number") == 0) flags->n = 1;
  if (strcmp(str, "--squeeze-blank") == 0) flags->s = 1;
  if (strcmp(str, "-T") == 0) flags->v = 1;
}
