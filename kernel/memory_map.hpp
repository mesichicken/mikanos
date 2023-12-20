#pragma once
#include <stdint.h>

// メモリマップ構造体の定義
// UEFIからシステムのメモリマップを取得するために使用する
struct MemoryMap {
  unsigned long long buffer_size; // バッファのサイズ
  void* buffer; // メモリマップを格納するバッファ
  unsigned long long map_size; // メモリマップ全体のサイズ
  unsigned long long map_key; // メモリマップのキー
  unsigned long long descriptor_size; // メモリディスクリプタのサイズ
  uint32_t descriptor_version; // メモリディスクリプタのバージョン
};

struct MemoryDescriptor {
  uint32_t type;
  uintptr_t physical_start;
  uintptr_t virtual_start;
  uint64_t number_of_pages;
  uint64_t attribute;
};

#ifdef __cplusplus
enum class MemoryType {
  kEfiReservedMemoryType,
  kEfiLoaderCode,
  kEfiLoaderData,
  kEfiBootServicesCode,
  kEfiBootServicesData,
  kEfiRuntimeServicesCode,
  kEfiRuntimeServicesData,
  kEfiConventionalMemory,
  kEfiUnusableMemory,
  kEfiACPIReclaimMemory,
  kEfiACPIMemoryNVS,
  kEfiMemoryMappedIO,
  kEfiMemoryMappedIOPortSpace,
  kEfiPalCode,
  kEfiPersistentMemory,
  kEfiMaxMemoryType
};

inline bool operator==(uint32_t lhs, MemoryType rhs) {
  return lhs == static_cast<uint32_t>(rhs);
}

inline bool operator==(MemoryType lhs, uint32_t rhs) {
  return rhs == lhs;
}

// メモリタイプが使用可能かどうかを判定する
inline bool IsAvailable(MemoryType memory_type) {
  return memory_type == MemoryType::kEfiBootServicesCode ||
         memory_type == MemoryType::kEfiBootServicesData ||
         memory_type == MemoryType::kEfiConventionalMemory;
}

const int kUEFIPageSize = 4096; // UEFIのページサイズ
#endif