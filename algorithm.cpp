#include <Arduino.h>
#include "algorithm.h"

int power(int a, int n){
  int t = 1;
  for(n;n>0;n--)
    t*=a;
  return t;
}

int crypto(int c, int d, int n){
  int mtmp = 1;
  while(1){
  int m = c, s = 1;
  while(m<n){
    if(s==d)
      return ( mtmp*(m%n) )%n;
    m*=c;
    s++;
  }
  int a = d%s,
      b = d/s;
    mtmp = (mtmp*power(c, a))%n;
    c = m%n;
    d = b;
  }
}

String decrypte(String str, int D, int N){
  char c = ',';
  int len = 1;
  for(int i=0;i<str.length();i++)
    if(str[i]==c)
      len++;
  String cipherText[len];
  int i=0,t=0,n=0;
  for(i,t,n;i<str.length();i++){
    if(str[i]==c){
      cipherText[n++] = str.substring(t, i);
      t = i+1;
    }
  }
  cipherText[n++] = str.substring(t, i);
  for(int i=0;i<len;i++)
    Serial.print(String(cipherText[i].toInt())+" ");
  
  return ";";
}
