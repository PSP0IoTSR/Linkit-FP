#ifndef __WVECTOR_H__
#define __WVECTOR_H__

#include <Arduino.h>
#include "welement.h"

class wvector{
public:
  int len, index;
  welement *els;
  wvector();
  wvector(int maxlen);
  void solve(String url, wvector *query);
  int length();
  boolean push(String k, String v);
  welement pop();
  welement get(int t);
private:
  welement empty;
};

#endif
