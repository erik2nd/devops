#include "grep.h"

void process_grep(int argc, char *argv[]) {
  Flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char *files[argc];
  char **patterns = NULL;
  char *regex = NULL;
  int opt = 0, patterns_count = 0, files_count = 0;
  while ((opt = getopt_long(argc, argv, "ivclnhsoe:f:", NULL, NULL)) != -1) {
    set_flag(&flags, &patterns, &patterns_count, files, &files_count, opt);
  }
  if (flags.v || flags.c) flags.o = 0;
  int i = optind;
  int should_name = 0;
  if (!flags.e && !flags.f) {
    patterns = realloc(patterns, (patterns_count + 1) * sizeof(char *));
    patterns[patterns_count++] =
        (char *)malloc((strlen(argv[optind]) + 1) * sizeof(char));
    strcpy(patterns[0], argv[optind]);
    i++;
  }
  int pam = i;
  if (flags.f && !files_exist(files, files_count)) {
    if (regex) free(regex);
    for (int i = 0; i < patterns_count; i++) {
      free(patterns[i]);
    }
    free(patterns);
    return;
  }
  int count_nonflags = 0;
  while (i < argc) {
    count_nonflags++;
    i++;
  }
  i = pam;
  if (flags.f) {
    read_lines_from_file(&patterns, &patterns_count, files, files_count);
  }
  if (count_nonflags > 1) should_name = 1;
  if (patterns != NULL) {
    set_patterns(&regex, patterns, patterns_count);
    for (; i < argc; i++) {
      print_res(&flags, argv[i], regex, should_name);
    }
    if (regex) free(regex);
    for (int i = 0; i < patterns_count; i++) {
      if (patterns[i]) free(patterns[i]);
    }
    if (patterns) free(patterns);
  }
}

void set_flag(Flags *flags, char ***patterns, int *patterns_count, char **files,
              int *files_count, const char ch) {
  switch (ch) {
    case 'e':
      flags->e = 1;
      *patterns =
          (char **)realloc(*patterns, (*patterns_count + 1) * sizeof(char *));
      if (*patterns == NULL) {
        free(*patterns);
        return;
      }
      (*patterns)[*patterns_count] =
          (char *)malloc((strlen(optarg) + 1) * sizeof(char));
      strcpy((*patterns)[(*patterns_count)++], optarg);
      break;
    case 'i':
      flags->i = REG_ICASE;
      break;
    case 'v':
      flags->v = 1;
      break;
    case 'c':
      flags->c = 1;
      break;
    case 'l':
      flags->l = 1;
      break;
    case 'n':
      flags->n = 1;
      break;
    case 'h':
      flags->h = 1;
      break;
    case 's':
      flags->s = 1;
      break;
    case 'f':
      flags->f = 1;
      files[(*files_count)++] = optarg;
      break;
    case 'o':
      flags->o = 1;
      break;
  }
}

void print_res(Flags *flags, const char *path, char *pattern, int name_files) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    if (!flags->s)
      fprintf(stderr, "grep: %s: No such file or directory\n", path);
    return;
  }
  regex_t regex;
  int error = regcomp(&regex, pattern, REG_EXTENDED | flags->i);
  if (error) {
    fprintf(stderr, "Regex compilation error\n");
    fclose(file);
    return;
  }
  char last_ch = '\n';
  int lines_count = 0;
  int matches_count = 0;
  int found_match = 0;
  char *line = NULL;
  size_t buffer_size = 0;
  ssize_t bytes_read;
  while ((bytes_read = getline(&line, &buffer_size, file)) != -1) {
    lines_count++;
    int match = !regexec(&regex, line, 0, NULL, 0);
    if ((match && !flags->v) || (!match && flags->v)) {
      if (flags->c) matches_count++;
      if (flags->l) found_match = 1;
      if (!flags->c && !flags->l)
        print_matches(&(*flags), regex, line, name_files, path, lines_count,
                      &last_ch);
    }
    if (line) free(line);
    line = NULL;
  }
  if (line) free(line);
  if (flags->c && flags->l) {
    if (name_files && !flags->h) printf("%s:", path);
    printf("%d\n", matches_count > 0 ? 1 : 0);
  }
  if (flags->c && !flags->l) {
    if (name_files && !flags->h) printf("%s:", path);
    printf("%d\n", matches_count);
  }
  if (flags->l && found_match) printf("%s\n", path);
  if (last_ch != '\n' && !flags->c && !flags->l) printf("\n");
  regfree(&regex);
  fclose(file);
}

void print_matches(Flags *flags, regex_t regex, char *line, int name_files,
                   const char *path, int lines_count, char *last_ch) {
  if (flags->o) {
    regmatch_t matches;
    int offset = 0;
    while (regexec(&regex, line + offset, 1, &matches, 0) == 0) {
      if (name_files && !flags->h) printf("%s:", path);
      if (flags->n) printf("%d:", lines_count);
      printf("%.*s\n", (int)(matches.rm_eo - matches.rm_so),
             &line[offset + matches.rm_so]);
      offset += matches.rm_eo;
    }
  } else {
    if (name_files && !flags->h) printf("%s:", path);
    if (flags->n) printf("%d:", lines_count);
    printf("%s", line);
    *last_ch = last_character(line);
  }
}

void set_patterns(char **regex, char **patterns, int patterns_count) {
  int total_length = 2;
  for (int i = 0; i < patterns_count; i++) {
    total_length += strlen(patterns[i]);
    if (i < patterns_count - 1) {
      total_length++;
    }
  }
  *regex = (char *)malloc(total_length * sizeof(char));
  (*regex)[0] = '\0';
  for (int i = 0; i < patterns_count; i++) {
    strcat(*regex, patterns[i]);
    if (i < patterns_count - 1) {
      strcat(*regex, "|");
    }
  }
}

void read_lines_from_file(char ***lines, int *numLines, char *filenames[],
                          int numFiles) {
  for (int i = 0; i < numFiles; i++) {
    if (file_empty(filenames[i])) continue;
    FILE *file = fopen(filenames[i], "r");
    char *line = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    while ((bytes_read = getline(&line, &buffer_size, file)) != -1) {
      if (!(line[0] == '\n' && line[1] == '\0'))
        line[strcspn(line, "\n")] = '\0';
      *lines = (char **)realloc(*lines, (*numLines + 1) * sizeof(char *));
      if (*lines == NULL) {
        printf("Memory allocation error\n");
        exit(1);
      }
      (*lines)[*numLines] = (char *)malloc((strlen(line) + 1) * sizeof(char));
      if ((*lines)[*numLines] == NULL) {
        printf("Memory allocation error\n");
        exit(1);
      }
      strcpy((*lines)[*numLines], line);
      (*numLines)++;
    }
    if (line) free(line);
    fclose(file);
  }
}

int files_exist(char **files, int files_count) {
  int res = 1;
  for (int i = 0; i < files_count; i++) {
    FILE *file = fopen(files[i], "r");
    if (file == NULL) {
      fprintf(stderr, "grep: %s: No such file or directory\n", files[i]);
      res = 0;
      break;
    }
    fclose(file);
  }
  return res;
}

int file_empty(const char *path) {
  int res = 0;
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    perror("Ошибка открытия файла");
    return -1;
  }
  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    fclose(file);
    res = 1;
  }
  fclose(file);
  return res;
}

char last_character(const char *str) {
  if (str[0] == '\0') return '\0';

  const char *ptr = str;
  char last_char = *ptr;

  while (*ptr != '\0') {
    last_char = *ptr;
    ptr++;
  }

  return last_char;
}
