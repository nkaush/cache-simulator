#include "simplecache.h"
#include <cstdio>

int main() {
  SimpleCache sc(3, 2); // Create 3-way set associative cache with 2 sets
  char a[4] = { 'a', 'b', 'c', 'd' };
  sc.insert(0xf00d, 1, a); // store store ['a', 'b', 'c', 'd'] into a cache block with set index 1 and tag 0xf00d
  sc.insert(0xf00e, 1, a);
  sc.insert(0xf00f, 1, a);
  sc.insert(0xd00f, 1, a); // overwrite index=1 tag=0xfood
  sc.insert(0xd00f, 0, a);

  printf("0x%x\n", sc.find(0xf00d, 1, 0)); //0xdeadbeef, since tag 0xfood got overwritten
  printf("0x%x\n", sc.find(0xf00e, 1, 0)); // 'a' = 0x61
  printf("0x%x\n", sc.find(0xf00f, 1, 1)); // 'b' = 0x62
  printf("0x%x\n", sc.find(0xd00f, 1, 2)); // 'c' = 0x63
  printf("0x%x\n", sc.find(0xd00f, 0, 3)); // 'd' = 0x64
}
