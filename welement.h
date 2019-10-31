#ifndef __READ_SERVER_H__
#define __READ_SERVER_H__

#include <Arduino.h>


class welement{
public:
  String key, val;
  welement();
  welement(String k, String v);
};

#endif
