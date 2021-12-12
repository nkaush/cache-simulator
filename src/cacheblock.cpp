#include "../include/cacheblock.h"

uint32_t Cache::Block::get_address() const {
  uint32_t addr = _tag << (_cache_config.get_num_index_bits() + _cache_config.get_num_block_offset_bits());
  return addr + (_index << _cache_config.get_num_block_offset_bits());
}
