#include <Arduino.h>
#include "welement.h"

welement::welement(){
  welement("", "");
}
welement::welement(String k, String v){
  key = k;
  val = v;
}
