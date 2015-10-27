#include <iostream>
#include <stdint.h>
#include <sstream>
#include <stdlib.h>

#include "masstree/mtIndexAPI.hh"

#define TEST_SIZE 255

typedef mt_index<Masstree::default_table> btree_type;

int main() {
  btree_type btree;
  btree.setup(8, 8, false);

  uint64_t key = 1;
  uint64_t value = 1;

  while (key < TEST_SIZE) {
    uint64_t* key_ptr = &key;
    uint64_t* value_ptr = &value;
    if (!btree.put_uv((const char*)key_ptr, 8, (const char*)value_ptr, 8)) {
      std::cout << "INSERT FAIL\n";
      return -1;
    }
    key += 2;
    value += 2;
  }

  key = 1;
  while (key < TEST_SIZE) {
    uint64_t* key_ptr = &key;
    Str val;
    if (!btree.get((const char*)key_ptr, 8, val)) {
      std::cout << "READ FAIL " << key << "\n";
      //return -1;
    }
    std::cout << *(reinterpret_cast<const uint64_t*>(val.s)) << " ";
    key += 2;
  }

  std::cout << "\n===========================================================================\n";

  key = 2;
  value = 2;
  while (key < TEST_SIZE) {
    uint64_t* key_ptr = &key;
    uint64_t* value_ptr = &value;
    if (!btree.put_uv((const char*)key_ptr, 8, (const char*)value_ptr, 8)) {
      std::cout << "INSERT FAIL\n";
      //return -1;
    }
    key += 2;
    value += 2;
  }

  key = 1;
  while (key < TEST_SIZE) {
    uint64_t* key_ptr = &key;
    Str val;
    if (!btree.get((const char*)key_ptr, 8, val)) {
      std::cout << "READ FAIL " << key << "\n";
      //return -1;
    }
    std::cout << *(reinterpret_cast<const uint64_t*>(val.s)) << " ";
    key++;
  }

  key = 1;
  value = 1;
  while (key < TEST_SIZE) {
    uint64_t* key_ptr = &key;
    uint64_t* value_ptr = &value;
    if (btree.put_uv((const char*)key_ptr, 8, (const char*)value_ptr, 8)) {
      std::cout << "DUPLICATE CHECK FAIL " << key << "\n";
      //return -1;
    }
    key += 1;
    value += 1;
  }

  std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

  key = 1;
  uint64_t* key_ptr = &key;
  Str val;
  if (!btree.get_upper_bound_or_equal((const char*)key_ptr, 8)) {
    std::cout << "SCAN FAIL " << key << "\n";
    //return -1;
  }
  for (int i = 1; i < TEST_SIZE; i++) {
    if (!btree.get_next(val)) {
      std::cout << "SCAN FAIL\n";
      //return -1;
    }
    std::cout << *(reinterpret_cast<const uint64_t*>(val.s)) << " ";
  }

  std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

  key = 1;
  while (key < TEST_SIZE) {
    uint64_t* key_ptr = &key;
    if (!btree.remove((const char*)key_ptr, 8)) {
      std::cout << "DELETE FAIL key = " << key << "\n";
      //return -1;
    }
    key += 2;
  }

  key = 1;
  key_ptr = &key;
  if (!btree.get_upper_bound_or_equal((const char*)key_ptr, 8)) {
    std::cout << "SCAN FAIL " << key << "\n";
    //return -1;
  }
  for (int i = 0; i < TEST_SIZE/2; i++) {
    if (!btree.get_next(val)) {
      std::cout << "SCAN FAIL\n";
      //return -1;
    }
    std::cout << *(reinterpret_cast<const uint64_t*>(val.s)) << " ";
  }

  std::cout << "\n";

  return 0;
}
