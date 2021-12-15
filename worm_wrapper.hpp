#pragma once
#include "lib.h"

#include "kv.h"
#include "tree.h"
#include "wh.h"
#include <iostream>
#include <map>

// used to define the interface of all benchmarking trees
template <class T, class P> class worm_wrapper : public Tree<T, P> {
public:
  typedef std::pair<T, P> V;

  worm_wrapper() {
    printf("start invoke constructor\n");
    my_tree = wh_create();
    printf("end invoke constructor\n");
  }

  void bulk_load(const V bulk_arr[], int num) {
    struct wormref *ref = wh_ref(my_tree);
    for (int i = 0; i < num; ++i) {
      wh_put(ref, bulk_arr[i].first->key, bulk_arr[i].first->length - 1,
             reinterpret_cast<const void *const>(&bulk_arr[i].second),
             sizeof(bulk_arr[i].second));
    }
    wh_unref(ref);
  }

  bool insert(const T &key, const P &payload) {
    if constexpr (std::is_pointer_v<T>) {
      struct wormref *ref = wh_ref(my_tree);
      auto ret = wh_put(ref, key->key, key->length - 1,
                        reinterpret_cast<const void *const>(&payload),
                        sizeof(payload));
      wh_unref(ref);
      return ret;
    } else {
      std::cout << "The key must be string key in HOT!" << std::endl;
      exit(-1);
    }
  }

  bool search(const T &key, P *payload) const {
    if constexpr (std::is_pointer_v<T>) {
      struct wormref *ref = wh_ref(my_tree);
      u32 len_out;
      auto ret = wh_get(ref, key->key, key->length - 1, payload, 8,
                        &len_out); // r == true, len_out == 6, "world!" in buf
                                   // (without the '\0')
      wh_unref(ref);
      return ret;
    } else {
      std::cout << "The key must be string key in HOT!" << std::endl;
      exit(-1);
    }
  }

  // 0 means no erase, 1 means erase 1
  bool erase(const T &key) { return false; }

  bool update(const T &key, const P &payload) { return false; }

  void print_min_max() {}

  void get_depth_info() {}

  int range_scan_by_size(const T &key, uint32_t to_scan, V *&result = nullptr) {
    return 0;
  }

private:
  struct wormhole *my_tree; // Store the pointer to the tree instance
};