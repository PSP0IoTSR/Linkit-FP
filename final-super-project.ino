#include <LWiFi.h>

char ssid[] = "TELDAP-2";
char pass[] = "TELDAP4F";
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);
class welement{
  public:
    String key, val;
    welement(){welement("", "");}
    welement(String k, String v){
      key = k;
      val = v;
    }
};
class vector{
  public:
    int len, index;
    welement *els;
    vector(){vector(50);}
    vector(int inlen){len=inlen;els = new welement[len];index = 0;}
    int length(){return index;}
    boolean push(String k, String v){
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
  private:
    welement empty;
};

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial); //Waitting Serial port connect

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    if(status != WL_CONNECTED)
      Serial.println("connect fail, try to reconnect");
  }
  server.begin();
  printWifiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client try to request");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean endline = false;
    String url = "";
    vector query(10);
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if(!endline){
          url+=c;
          if(c=='\r'||c=='\n')
            endline = true;
        }else{
        }
        Serial.write(c);
        //Serial.println("----------------");
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          solve(url, &query);
          Serial.println("parameter length: "+String(query.len));
          for(int i=0;i<query.length();i++)
            Serial.println(String(i)+" - key: "+query.get(i).key+", value: "+query.get(i).val);
          welement obj;
          for(int i=0;i<query.index;i++){
            Serial.println(obj.key);
          }
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println(url);
          // output the value of each analog input pin
          for (int analogChannel = A0; analogChannel <= A3; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
void solve(String url, vector *query){
  Serial.println("url: "+url);
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


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
