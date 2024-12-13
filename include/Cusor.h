#ifndef CURSOR_H_
#define CURSOR_H_

struct Cursor{
  int x, y;
  void reset(){
    x = 0, y = 10;
  }
  void nextLine(){
    y += 10;
  }
};

#endif