#include "grep.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("n/a");
    return 1;
  }

  process_grep(argc, argv);
  return 0;
}
