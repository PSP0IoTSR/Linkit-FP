#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <Arduino.h>
#include <welement.h>

class vector{
public:
  int len, index;
  vector();
  vector(int maxlen);
  int length();
  boolean push(){String k, String v};
  welement pop();
  welement get(int t);
private:
  welement empty;
};

#endif
