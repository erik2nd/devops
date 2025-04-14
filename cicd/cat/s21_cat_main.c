#include "cat.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("n/a");
    return 1;
  }
  Flags flags = {0, 0, 0, 0, 0, 0};
  int index = 0;
  int correct = 1;
  for (int i = 1; i < argc; i++) {
    if (is_flag(argv[i])) {
      if (!fill_flag(&flags, argv[i])) {
        correct = 0;
        break;
      }
      index++;
    } else
      break;
  }
  if (correct) {
    for (int i = index + 1; i < argc; i++) {
      print_text(argv[i], flags);
    }
  }
  return 0;
}
