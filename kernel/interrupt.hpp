/**
 * @file interrupt.hpp
 *
 * 割り込み用のプログラムを集めたファイル．
 */

#pragma once

#include <array>
#include <cstdint>

#include "x86_descriptor.hpp"

// 割り込み記述子の属性を表す構造体
union InterruptDescriptorAttribute {
  uint16_t data;
  struct {
    uint16_t interrupt_stack_table : 3; // 割り込み発生時に使用するスタックの番号(IST)
    uint16_t : 5; // 0で埋める(0,0,0,0,0)
    DescriptorType type : 4; // 割り込み記述子の種類(Type)
    uint16_t : 1; // 0で埋める(0)
    uint16_t descriptor_privilege_level : 2; // 特権レベル(DPL)
    uint16_t present : 1; // 割り込み記述子が有効かどうかを表すフラグ(P)
  } __attribute__((packed)) bits;
} __attribute__((packed));

// 割り込み記述子を表す構造体
// offset_low, offset_middle, offset_high で割り込みハンドラのアドレスを表す
// segment_selector で割り込みハンドラを実行する際に使用するセグメントを表す
struct InterruptDescriptor {
  uint16_t offset_low;
  uint16_t segment_selector;
  InterruptDescriptorAttribute attr;
  uint16_t offset_middle;
  uint32_t offset_high;
  uint32_t reserved;
} __attribute__((packed));

// 割り込み記述子の配列
extern std::array<InterruptDescriptor, 256> idt;

// 割り込み記述子の属性を作成する
constexpr InterruptDescriptorAttribute MakeIDTAttr(
    DescriptorType type,
    uint8_t descriptor_privilege_level,
    bool present = true,
    uint8_t interrupt_stack_table = 0) {
  InterruptDescriptorAttribute attr{};
  attr.bits.interrupt_stack_table = interrupt_stack_table;
  attr.bits.type = type;
  attr.bits.descriptor_privilege_level = descriptor_privilege_level;
  attr.bits.present = present;
  return attr;
}

// 割り込み記述子の設定を行う
void SetIDTEntry(InterruptDescriptor& desc,
                 InterruptDescriptorAttribute attr,
                 uint64_t offset,
                 uint16_t segment_selector);

// 割り込みベクタ番号を表すクラス
class InterruptVector {
 public:
  enum Number {
    kXHCI = 0x40,
  };
};

// 割り込み発生時に保存されるレジスタを表す構造体
struct InterruptFrame {
  uint64_t rip;
  uint64_t cs;
  uint64_t rflags;
  uint64_t rsp;
  uint64_t ss;
};

void NotifyEndOfInterrupt();
