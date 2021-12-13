#include "worm_wrapper.hpp"

extern "C" void *create_tree() {
  return reinterpret_cast<void *>(new worm_wrapper<string_key *, char *>());
}