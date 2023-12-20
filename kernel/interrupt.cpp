/**
 * @file interrupt.cpp
 *
 * 割り込み用のプログラムを集めたファイル．
 */

#include "interrupt.hpp"

std::array<InterruptDescriptor, 256> idt;

// 割り込み記述子の設定を行う
void SetIDTEntry(InterruptDescriptor& desc,
                 InterruptDescriptorAttribute attr,
                 uint64_t offset,
                 uint16_t segment_selector) {
  desc.attr = attr;
  desc.offset_low = offset & 0xffffu;
  desc.offset_middle = (offset >> 16) & 0xffffu;
  desc.offset_high = offset >> 32;
  desc.segment_selector = segment_selector;
}

// 割り込み処理の終了をCPUに通知する
// 0xfee000b0番地に0を書き込むことで通知できる
void NotifyEndOfInterrupt() {
  volatile auto end_of_interrupt = reinterpret_cast<uint32_t*>(0xfee000b0);
  *end_of_interrupt = 0;
}