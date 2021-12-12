#include "../include/utils.h"

uint32_t extract_tag(uint32_t address, const CacheConfig& cache_config) {
  // TODO
  
  return address >> (32 - cache_config.get_num_tag_bits());
}

uint32_t extract_index(uint32_t address, const CacheConfig& cache_config) {
  // TODO

  // 2^power - 1 gets power 1s 
  uint32_t mask = ((1 << cache_config.get_num_index_bits()) - 1) << cache_config.get_num_block_offset_bits();
  return (mask & address) >> cache_config.get_num_block_offset_bits();
}

uint32_t extract_block_offset(uint32_t address, const CacheConfig& cache_config) { 
  return address % (1 << cache_config.get_num_block_offset_bits());
}
