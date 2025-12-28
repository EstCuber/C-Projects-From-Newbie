#include "../small-string-opt/small_string_opt.h"

void test_print() {
  unsigned short count_tests = 255;
  String test_string1;
  String test_string2;
  String test_string3;
  string_from_s(&test_string1, "Hello, my friend!");
  string_from_s(&test_string2,
                "hello mister johnson! "
                "jegr;lshdjfg;lskdjfg;dlfjkgs;dfjg;lsdfkjgsdl;kfjg;sdhfjlghs;"
                "dfhgjs;ldjfhg");
  string_from_s(&test_string3, "Hi!");
  for (unsigned short i = 0; i < count_tests; i++) {
    string_print(&test_string1);
    string_print(&test_string2);
    string_print(&test_string3);
  }

  string_free(&test_string1);
  string_free(&test_string2);
  string_free(&test_string3);
}

int main(void) {
  test_print();
  return 0;
}
