#include "console.hpp"

#include <cstring> // C言語の文字列操作関数のためのヘッダ
#include "font.hpp" // フォント関連の機能を含むヘッダ

// Consoleクラスのコンストラクタ
// writer: ピクセルを描画するためのPixelWriterオブジェクト
// fg_color: テキストの前景色
// bg_color: 背景色
Console::Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color)
    : writer_{writer}, fg_color_{fg_color}, bg_color_{bg_color},
      buffer_{}, cursor_row_{0}, cursor_column_{0} {
}

// 文字列sをコンソールに描画する
void Console::PutString(const char* s) {
  while (*s) { // 文字列の終端に達するまでループ
    if (*s == '\n') { // 改行文字の場合、改行処理を行う
      Newline();
    } else if (cursor_column_ < kColumns - 1) { // 行の終わりでなければ文字を描画
      WriteAscii(writer_, 8 * cursor_column_, 16 * cursor_row_, *s, fg_color_);
      buffer_[cursor_row_][cursor_column_] = *s; // バッファに文字を記録
      ++cursor_column_; // カーソル位置を進める
    }
    ++s; // 次の文字へ
  }
}

// 改行を処理する
void Console::Newline() {
  cursor_column_ = 0; // カーソルの列をリセット
  if (cursor_row_ < kRows - 1) { // 最終行でなければ行を進める
    ++cursor_row_;
    return;
  }

  // 最終行の場合、画面をスクロールさせる
  for (int y = 0; y < 16 * kRows; ++y) {
    for (int x = 0; x < 8 * kColumns; ++x) {
      writer_.Write(x, y, bg_color_); // 背景色で画面を塗りつぶす
    }
  }
  // 上の行の内容を下にコピーして、画面を1行分上にスクロールさせる
  for (int row = 0; row < kRows - 1; ++row) {
    memcpy(buffer_[row], buffer_[row + 1], kColumns + 1);
    WriteString(writer_, 0, 16 * row, buffer_[row], fg_color_);
  }
  // 新しい最終行を空にする
  memset(buffer_[kRows - 1], 0, kColumns + 1);
}
