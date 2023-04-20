#include "maybe.h"
#include <stdbool.h>

def_maybe(int);
def_maybe(char);

typedef struct StringSlice str;
struct str_range_struct;
struct str_twotuple;
str str_from(const char *cstr);
str str_slice(const str in, const struct str_range_struct range);
str str_strip_prefix(const str in, const str prefix);
str str_strip_suffix(const str in, const str suffix);
str str_trim(const str in);
str str_trim_start(const str in);
str str_trim_end(const str in);
struct str_twotuple str_split_at(const str in, int index);
maybe(char) str_index(const str in, int index);
maybe(int) str_find(const str in, char pattern);
maybe(int) str_rfind(const str in, char pattern);
bool str_starts_with(const str in, const str prefix);
bool str_ends_with(const str in, const str suffix);
bool str_is_empty(const str in);
bool str_eq(const str a, const str b);

struct StringSlice {
  const char *string;
  unsigned int length;
};
struct str_range_struct {
  int start;
  int end;
};
struct str_twotuple {
  str one;
  str two;
};

const struct StrScope {
  str (*from)(const char *cstr);
  str (*slice)(const str in, const struct str_range_struct range);
  str (*strip_prefix)(const str in, const str prefix);
  str (*strip_suffix)(const str in, const str suffix);
  str (*trim)(const str in);
  str (*trim_start)(const str in);
  str (*trim_end)(const str in);
  struct str_twotuple (*split_at)(const str in, int index);
  maybe(char) (*index)(const str in, int index);
  maybe(int) (*find)(const str in, char pattern);
  maybe(int) (*rfind)(const str in, char pattern);
  bool (*starts_with)(const str in, const str prefix);
  bool (*ends_with)(const str in, const str suffix);
  bool (*is_empty)(const str in);
} Str = {
    str_from,      str_slice,      str_strip_prefix, str_strip_suffix,
    str_trim,      str_trim_start, str_trim_end,     str_split_at,
    str_index,     str_find,       str_rfind,        str_starts_with,
    str_ends_with, str_is_empty,
};
