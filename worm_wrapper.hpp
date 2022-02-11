#pragma once
#include "lib.h"

#include "kv.h"
#include "tree_api.h"
#include "wh.h"
#include <iostream>
#include <map>

// used to define the interface of all benchmarking trees
class worm_wrapper : public tree_api {
public:
  worm_wrapper() {
    printf("start invoke constructor\n");
    my_tree = wh_create();
    printf("end invoke constructor\n");
  }

  void bulk_load(char *key[], size_t k_sz[], char *value[], size_t v_sz[],
                 size_t num_kv) {
    for (size_t i = 0; i < num_kv; i++) {
      struct wormref *ref = wh_ref(my_tree);
      auto ret =
          wh_put(ref, key[i], k_sz[i] - 1,
                 reinterpret_cast<const void *const>(value[i]), sizeof(size_t));
      wh_unref(ref);
    }

    struct wormref *ref = wh_ref(my_tree);
    metatable_size(ref);
    wh_unref(ref);
  }

  bool insert(const char *key, size_t key_sz, const char *value,
              size_t value_sz, size_t thread_id) override {
    struct wormref *ref = wh_ref(my_tree);
    auto ret = wh_put(ref, key, key_sz - 1,
                      reinterpret_cast<const void *const>(value), value_sz);
    wh_unref(ref);
    return ret;
  }

  bool find(const char *key, size_t sz, char *value_out,
            size_t thread_id) override {
    struct wormref *ref = wh_ref(my_tree);
    u32 len_out;
    auto ret = wh_get(ref, key, sz - 1, value_out, 8, &len_out);
    wh_unref(ref);
    return ret;
  }

  bool update(const char *key, size_t key_sz, const char *value,
              size_t value_sz, size_t thread_id) override {
    return true;
  }

  bool remove(const char *key, size_t key_sz, size_t thread_id) override {
    return true;
  }

  int scan(const char *key, size_t key_sz, int scan_sz, char *&values_out,
           size_t thread_id) override {

    return 0;
  }

private:
  struct wormhole *my_tree; // Store the pointer to the tree instance
};