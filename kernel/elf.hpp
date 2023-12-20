#pragma once

#include <stdint.h>

typedef uintptr_t Elf64_Addr;
typedef uint64_t  Elf64_Off;
typedef uint16_t  Elf64_Half;
typedef uint32_t  Elf64_Word;
typedef int32_t   Elf64_Sword;
typedef uint64_t  Elf64_Xword;
typedef int64_t   Elf64_Sxword;

#define EI_NIDENT 16

// ELFヘッダー
typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf64_Half    e_type; // ファイルの識別情報
  Elf64_Half    e_machine; // ファイルのタイプ(実行可能ファイル、共有ライブリなど)
  Elf64_Word    e_version; // ELFのバージョン
  Elf64_Addr    e_entry; // 実行可能ファイルのエントリポイント(実行開始アドレス)
  Elf64_Off     e_phoff; // プログラムヘッダーテーブルへのオフセット
  Elf64_Off     e_shoff; // セクションヘッダーテーブルへのオフセット
  Elf64_Word    e_flags; // プロセッサ固有のフラグ
  Elf64_Half    e_ehsize; // ELFヘッダーのサイズ
  Elf64_Half    e_phentsize; // プログラムヘッダーエントリのサイズ
  Elf64_Half    e_phnum; // プログラムヘッダーエントリの数
  Elf64_Half    e_shentsize; // セクションヘッダーエントリのサイズ
  Elf64_Half    e_shnum; // セクションヘッダーエントリの数
  Elf64_Half    e_shstrndx; // セクション名を格納するセクションのインデックス
} Elf64_Ehdr;

// プログラムヘッダー
typedef struct {
  Elf64_Word  p_type; // PHDR, LOAD などのセグメント種別
  Elf64_Word  p_flags; // 実行可能、書き込み可能などの属性
  Elf64_Off   p_offset; // ファイル中の位置
  Elf64_Addr  p_vaddr; // 論理アドレス
  Elf64_Addr  p_paddr; // 物理アドレス
  Elf64_Xword p_filesz; // ファイル中のサイズ
  Elf64_Xword p_memsz; // メモリ上でのサイズ
  Elf64_Xword p_align;
} Elf64_Phdr;

// セグメントタイプ定数
#define PT_NULL    0 // 無効なセグメント、通常は使用されない
#define PT_LOAD    1 // メモリにロードされるセグメント、実行可能コードやデータを含むことが多い
#define PT_DYNAMIC 2 // 動的リンク情報を含むセグメント、動的リンカによって処理される
#define PT_INTERP  3 // 動的リンカのパスを指定するセグメント
#define PT_NOTE    4 // 補足情報を含むセグメント。デバッグ情報などに使用される
#define PT_SHLIB   5 // 予約済みで、現在は使用されていない
#define PT_PHDR    6 // ファイル内のプログラムヘッダーテーブル自体を渡すセグメント
#define PT_TLS     7 // スレッドローカルストレージセグメント。TLSを使用する場合に使用される

// 動的リンキング構造体
typedef struct {
  Elf64_Sxword d_tag;
  union {
    Elf64_Xword d_val;
    Elf64_Addr d_ptr;
  } d_un;
} Elf64_Dyn;

// 動的リンキング定数
#define DT_NULL    0
#define DT_RELA    7
#define DT_RELASZ  8
#define DT_RELAENT 9

// 再配置エントリ
typedef struct {
  Elf64_Addr r_offset;
  Elf64_Xword r_info;
  Elf64_Sxword r_addend;
} Elf64_Rela;

// 再配置ヘルパーマクロ
#define ELF64_R_SYM(i)    ((i)>>32)
#define ELF64_R_TYPE(i)   ((i)&0xffffffffL)
#define ELF64_R_INFO(s,t) (((s)<<32)+((t)&0xffffffffL))

#define R_X86_64_RELATIVE 8
