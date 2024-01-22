#include "timer.hpp"

namespace {
  const uint32_t kCountMax = 0xffffffffu; // 32bitの最大値 タイマのカウントダウンに使用

  // ローカルAPICのレジスタへのポインタを定義
  volatile uint32_t& lvt_timer = *reinterpret_cast<uint32_t*>(0xfee00320); // 割り込みの発生方法の設定などを行うレジスタ
  volatile uint32_t& initial_count = *reinterpret_cast<uint32_t*>(0xfee00380); // タイマーのカウントダウンを開始する値
  volatile uint32_t& current_count = *reinterpret_cast<uint32_t*>(0xfee00390); // タイマーの現在の値
  volatile uint32_t& divide_config = *reinterpret_cast<uint32_t*>(0xfee003e0); // カウンタの減少スピードを設定するレジスタ
}

// タイマの初期化
void InitializeLAPICTimer() {
  divide_config = 0b1011; // タイマの分周設定を1/1に設定
  lvt_timer = (0b001 << 16) | 32; // タイマのモードをワンショット(一回だけカウントダウン)に設定し、割り込み番号を32に設定
  // 0:単発(oneshot)モード。一回タイムアウトしたらタイマー動作が終了する
  // 1:周期(periodic)モード。タイムアウトするたびにタイマーが再起動する
}

// タイマのカウントダウンを開始する
void StartLAPICTimer() {
  initial_count = kCountMax;
}

// 経過したタイマーの値を返す
uint32_t LAPICTimerElapsed() {
  return kCountMax - current_count;
}

// タイマのカウントダウンを停止する
void StopLAPICTimer() {
  initial_count = 0;
}