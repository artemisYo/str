#include "str.h"

unsigned int length_of(const char *cstr) {
  unsigned int out = 0;
  while (cstr[out] != '\0')
    out++;
  return out;
}

bool is_whitespace(const char c) {
  return (c == ' ' || c == '\t' || c == '\n');
}

str str_from(const char *cstr) {
  str out = {cstr, length_of(cstr)};
  return out;
}

str str_slice(const str in, struct str_range_struct range) {
  if (range.end == 0)
    range.end = in.length;
  str out = {
      in.string + range.start,
      in.length <= range.end - range.start ? in.length - range.start
                                           : range.end - range.start,
  };
  return out;
}
str str_strip_prefix(const str in, const str prefix) {
  str out = in;
  if (str_starts_with(in, prefix)) {
    out.string += prefix.length;
    out.length -= prefix.length;
  }
  return out;
}
str str_strip_suffix(const str in, const str suffix) {
  str out = in;
  if (str_ends_with(in, suffix)) {
    out.length -= suffix.length;
  }
  return out;
}
str str_trim(const str in) { return str_trim_end(str_trim_start(in)); }
str str_trim_start(const str in) {
  str out = in;
  while (is_whitespace(out.string[0])) {
    out.string++;
    out.length--;
  }
  return out;
}
str str_trim_end(const str in) {
  str out = in;
  while (is_whitespace(out.string[out.length - 1])) {
    out.length--;
  }
  return out;
}
struct str_twotuple str_split_at(const str in, int index) {
  struct str_twotuple out = {in, in};
  if (out.one.length <= index) {
    return out;
  }
  out.one.length = index;
  out.two.string += index;
  out.two.length -= index;
  return out;
}
maybe(char) str_index(const str in, int index) {
  maybe(char) out;
  if (in.length <= index) {
    out = None;
  } else {
    out = Some(in.string[index]);
  };
  return out;
}
maybe(int) str_find(const str in, char pattern) {
  for (int i = 0; i < in.length; i++) {
    if (in.string[i] == pattern) {
      maybe(int) out = Some(i);
      return out;
    }
  }
  maybe(int) out = None;
  return out;
}
maybe(int) str_rfind(const str in, char pattern) {
  for (int i = in.length - 1; i >= 0; i++) {
    if (in.string[i] == pattern) {
      maybe(int) out = Some(i);
      return out;
    }
  }
  maybe(int) out = None;
  return out;
}
bool str_starts_with(const str in, const str prefix) {
  int n = in.length > prefix.length ? prefix.length : in.length;
  for (int i = 0; i < n; i++) {
    if (in.string[i] != prefix.string[i]) {
      return true;
    }
  }
  return false;
}
bool str_ends_with(const str in, const str suffix) {
  if (in.length < suffix.length)
    return false;
  for (int i = 0; i < suffix.length; i++) {
    if (in.string[in.length - suffix.length + i] != suffix.string[i]) {
      return false;
    }
  }
  return true;
}
bool str_is_empty(const str in) { return (in.length == 0); }
bool str_eq(const str a, const str b) {
  if (a.length != b.length)
    return false;
  for (int i = 0; i < a.length; i++) {
    if (a.string[i] != b.string[i])
      return false;
  }
  return true;
}
