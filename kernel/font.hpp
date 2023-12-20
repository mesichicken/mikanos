#pragma once

#include <cstdint>
#include "graphics.hpp"

// フォントを描画するクラス
void WriteAscii(PixelWriter& writer, int x, int y, char c, const PixelColor& color);

// 文字列を描画するクラス
void WriteString(PixelWriter& writer, int x, int y, const char* s, const PixelColor& color);