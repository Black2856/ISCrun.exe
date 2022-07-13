#ifndef SECTION_H
#include "stdint.h"
#include "Clock.h"
#include "dataIO.h"

using namespace ev3api;

class Section{
public:
  uint16_t running(uint16_t currentSection); //区画の実行
  virtual void main() = 0; //区画の内容の実行
protected:
  DataIO *dataIO = DataIO::getInstance();

  virtual void entry() = 0; //区画遷移時の初期化
  virtual void condition() = 0; //区画遷移条件
  void transition(const uint16_t sectionID); //区画遷移処理

  bool sectionEntry = false; //区画遷移したかのフラグ
  uint16_t currentSection; //現在の区画番号
  static const uint16_t section; //自身の区画番号
  Clock clock; //区画遷移の時間管理
};

#define SECTION_H
#endif