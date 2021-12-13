#pragma once

#include <cstdint>
#include <map>

/*Variable length key*/
struct string_key {
  int length;  // key length
  char key[0]; // string
};

template <class T, class P> class Tree;

extern "C" void *create_tree();

// used to define the interface of all benchmarking trees
template <class T, class P> class Tree {
public:
  typedef std::pair<T, P> V;
  virtual void bulk_load(const V[], int) = 0;
  virtual bool insert(const T &, const P &) = 0;
  virtual bool search(const T &, P *) const = 0;
  virtual bool erase(const T &) = 0;
  virtual bool update(const T &, const P &) = 0;
  // Return #keys really scanned
  virtual int range_scan_by_size(const T &, uint32_t, V *&result) = 0;

  // Do most initialization work here
  Tree<T, P> *create_tree() { return nullptr; }

  void print_min_max() {}

  virtual void get_depth_info() = 0;
};