#pragma once

#include "frame_buffer_config.hpp"


// ピクセルの色を表す構造体、RGB値を8ビットで表現する
struct PixelColor {
  uint8_t r, g, b;
};

// ピクセルを描画するための基底クラス。フレームバッファの設定を保持し、ピクセルの描画を抽象化する
class PixelWriter {
 public:
  PixelWriter(const FrameBufferConfig& config) : config_{config} {
  }
  virtual ~PixelWriter() = default;
  virtual void Write(int x, int y, const PixelColor& c) = 0;

 protected:
  uint8_t* PixelAt(int x, int y) {
    return config_.frame_buffer + 4 * (config_.pixels_per_scan_line * y + x);
  }

 private:
  const FrameBufferConfig& config_;
};

// RGB形式でピクセルを描画するクラス
class RGBResv8BitPerColorPixelWriter : public PixelWriter {
 public:
  using PixelWriter::PixelWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};

// BGR形式でピクセルを描画するクラス
class BGRResv8BitPerColorPixelWriter : public PixelWriter {
 public:
  using PixelWriter::PixelWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};

template <typename T>
struct Vector2D {
  T x, y;

  template <typename U>
  Vector2D<T>& operator +=(const Vector2D<U>& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
};

// 長方形の枠を描画する
void DrawRectangle(PixelWriter& writer, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixelColor& c);

// 長方形を塗りつぶす
void FillRectangle(PixelWriter& writer, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixelColor& c);
