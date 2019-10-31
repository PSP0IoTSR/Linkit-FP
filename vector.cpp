#include <Arduino.h>
#include "welement.h"

vector::vector(){
  vector(50);
}

vector::vecotr(int maxlen){
  len = maxlen;
  els = new welement[len];
  index = 0;
}

boolean vector::push(String k, String v){
  if(index>-1&&index<len){
    welement el(k, v);
    els[index++] = el;
    return true;
  }
  return false;
}

welement pop(){
  if(index>-1){
    return els[--index];
  }
  return empty;
}

welement get(int t){
  if(t>-1&&t<index)
    return els[t];
  return empty;
}
