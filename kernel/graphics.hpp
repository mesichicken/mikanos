#pragma once

#include "frame_buffer_config.hpp"


// ピクセルの色を表す構造体、RGB値を8ビットで表現する
struct PixelColor {
  uint8_t r, g, b;
};

// 2つのピクセルの色が等しいかどうかを判定する
inline bool operator==(const PixelColor& lhs, const PixelColor& rhs) {
  return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

// 2つのピクセルの色が異なるかどうかを判定する
inline bool operator!=(const PixelColor& lhs, const PixelColor& rhs) {
  return !(lhs == rhs);
}

// ピクセルを描画するための基底クラス。フレームバッファの設定を保持し、ピクセルの描画を抽象化する
class PixelWriter {
 public:
  virtual ~PixelWriter() = default;
  virtual void Write(int x, int y, const PixelColor& c) = 0;
  virtual int Width() const = 0;
  virtual int Height() const = 0;
};

// フレームバッファに対する書き込みを行うクラス
class FrameBufferWriter : public PixelWriter {
  public:
    FrameBufferWriter(const FrameBufferConfig& config) : config_(config) {
    }
    virtual ~FrameBufferWriter() = default;
    virtual int Width() const override { return config_.horizontal_resolution; }
    virtual int Height() const override { return config_.vertical_resolution; }

    protected:
      uint8_t* PixelAt(int x, int y) {
        return config_.frame_buffer + 4 * (config_.pixels_per_scan_line * y + x);
      }

    private:
      const FrameBufferConfig& config_;
};

// RGB形式でピクセルを描画するクラス
class RGBResv8BitPerColorPixelWriter : public FrameBufferWriter {
 public:
  using FrameBufferWriter::FrameBufferWriter;
  virtual void Write(int x, int y, const PixelColor& c) override;
};

// BGR形式でピクセルを描画するクラス
class BGRResv8BitPerColorPixelWriter : public FrameBufferWriter {
 public:
  using FrameBufferWriter::FrameBufferWriter;
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

const PixelColor kDesktopBGColor{45, 118, 237};
const PixelColor kDesktopFGColor{255, 255, 255};

void DrawDesktop(PixelWriter& writer);