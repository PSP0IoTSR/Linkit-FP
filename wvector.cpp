#include <Arduino.h>
#include "wvector.h"
#include "welement.h"

wvector::wvector(){
  wvector(50);
}
wvector::wvector(int maxlen){
  len = maxlen;
  els = new welement[len];
  index = 0;
}
int wvector::length(){
  return index;
}
boolean wvector::push(String k, String v){
  if(index>-1&&index<len){
    welement el(k, v);
    els[index++] = el;
    return true;
  }
  return false;
}
welement wvector::pop(){
  if(index>-1){
    return els[--index];
  }
  return empty;
}
welement wvector::get(int t){
  if(t>-1&&t<index)
    return els[t];
  return empty;
}

void wvector::solve(String url, wvector *query){
//  Serial.println("url: "+url);
  int sp = -1;
  for(int i=0;i<url.length()&&sp==-1;i++)
    if(url[i]=='?')
      sp = i+1;
  if(sp==-1)
    return;
  int s = sp;
  bool full = false;
  for(int i=sp;i<url.length();i++){
    if(url[i]=='&'||url[i]=='\ '){
      String item = url.substring(s, i);
      int split = -1;
      for(int n=0;n<item.length();n++)
        if(item[n]=='=')
          split = n;
//      Serial.println("split: "+String(split)+" to "+String(i));
      if(i!=split){
        full = query->push(item.substring(0, split), item.substring(split+1, item.length()));
      }
      s = i+1;
    }
  }
}
