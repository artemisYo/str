#include "str.c"
#include <pthread.h>
#include <stdbool.h>

bool test_from() {
  char *in = "this is a string";
  str res = str_from(in);
  return res.length == 16 && res.string == in;
}

bool test_slice() {
  str s = str_from("hello world!");
  str sp = str_from("o world");
  struct str_range_struct r = {4, s.length - 1};
  str sn = str_slice(s, r);
  return str_eq(sp, sn);
}

#define TESTCOUNT 2
bool (*tests[TESTCOUNT])() = {test_from, test_slice};
char *test_names[TESTCOUNT] = {"test_from", "test_slice"};

void *run_test(void *test_id) {
  if (tests[(int)test_id]()) {
    pthread_exit(0);
  } else {
    pthread_exit((void *)1);
  }
}

int main() {
  pthread_t threads[TESTCOUNT] = {0};
  for (int i = 0; i < TESTCOUNT; i++) {
    if (pthread_create(threads + i, NULL, run_test, (void *)i) != 0) {
      printf("Failed to create thread for test");
      return 1;
    }
  }
  for (int i = 0; i < TESTCOUNT; i++) {
    int ret = 1;
    pthread_join(threads[i], &ret);
    if (ret != 0) {
      printf("[%s] failed!\n", test_names[i]);
    } else {
      printf("[%s] succeeded!\n", test_names[i]);
    }
  }
  return 0;
}

/* str str_slice(const str in, const struct str_range_struct range); */
/* str str_strip_prefix(const str in, const str prefix); */
/* str str_strip_suffix(const str in, const str suffix); */
/* str str_trim(const str in); */
/* str str_trim_start(const str in); */
/* str str_trim_end(const str in); */
/* struct str_twotuple str_split_at(const str in, int index); */
/* maybe(char) str_index(const str in, int index); */
/* maybe(int) str_find(const str in, char pattern); */
/* maybe(int) str_rfind(const str in, char pattern); */
/* bool str_starts_with(const str in, const str prefix); */
/* bool str_ends_with(const str in, const str suffix); */
/* bool str_is_empty(const str in); */
/* bool str_eq(const str a, const str b); */
