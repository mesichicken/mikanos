/**
 * @file segment.hpp
 *
 * セグメンテーション用のプログラムを集めたファイル．
 */

#pragma once

#include <array>
#include <cstdint>

// セグメントディスクリプタを表すユニオン。
// ビットフィールドとしても、単一の64ビットデータとしてもアクセス可能。
#include "x86_descriptor.hpp"

union SegmentDescriptor {
  uint64_t data;
  struct {
    uint64_t limit_low : 16; // セグメントの制限(下位ビット)
    uint64_t base_low : 16; // ベースアドレス(下位ビット)
    uint64_t base_middle : 8; // ベースアドレス(中位ビット)
    DescriptorType type : 4; // ディスクリプタタイプ
    uint64_t system_segment : 1; // システムセグメントフラグ
    uint64_t descriptor_privilege_level : 2; // ディスクリプタの特権レベル
    uint64_t present : 1; // セグメントの存在フラグ
    uint64_t limit_high : 4; // セグメントの制限(上位ビット)
    uint64_t available : 1; // 利用可能ビット(カスタム使用)
    uint64_t long_mode : 1; // 長モードフラグ
    uint64_t default_operation_size : 1; // デフォルトのオペレーションサイズ
    uint64_t granularity : 1; // 制限の粒度
    uint64_t base_high : 8; // ベースアドレス(上位ビット)
  } __attribute__((packed)) bits; // パッキング属性を指定

} __attribute__((packed));

void SetCodeSegment(SegmentDescriptor& desc,
                    DescriptorType type,
                    unsigned int descriptor_privilege_level,
                    uint32_t base,
                    uint32_t limit);
void SetDataSegment(SegmentDescriptor& desc,
                    DescriptorType type,
                    unsigned int descriptor_privilege_level,
                    uint32_t base,
                    uint32_t limit);

void SetupSegments();
