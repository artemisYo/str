#include <stdio.h>
#include <stdlib.h>
#define def_maybe(x)                                                           \
  struct maybe_##x {                                                           \
    short dis;                                                                 \
    x val;                                                                     \
  };                                                                           \
  inline int x##_is_some(struct maybe_##x a) { return a.dis; }                 \
  inline int x##_is_none(struct maybe_##x a) { return !a.dis; }                \
  inline x x##_unwrap(struct maybe_##x a) {                                    \
    if (x##_is_none(a)) {                                                      \
      printf("[%s : %i] Tried to unwrap 'maybe' of type '%s' and failed!\n",   \
             __FILE__, __LINE__, #x);                                          \
      exit(1);                                                                 \
    }                                                                          \
    return a.val;                                                              \
  }
#define maybe(x) struct maybe_##x
#define Some(x)                                                                \
  (struct maybe_##x) { 1, x }
#define None                                                                   \
  (struct maybe_##x) { 0 }
