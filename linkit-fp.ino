#include <LWiFi.h>
#include "wvector.h"
#include "welement.h"
#include "algorithm.h"

const int pemkey = 53, modulus = 45173;
char ssid[] = "pornhub";
char pass[] = "pornhub.com";
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

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
  pinMode(LED_BUILTIN, OUTPUT);
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
    wvector query(10);
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
          query.solve(url, &query);
          Serial.println("parameter length: "+String(query.len));
          for(int i=0;i<query.length();i++){
            String plainText = decrypte(query.get(i).val, pemkey, modulus);
            query.set(i, plainText);
            Serial.println(String(i)+" - key: "+query.get(i).key+", value: "+query.get(i).val);
          }
          welement obj;

          Serial.println("length: "+String(query.length()));
          for(int i=0;i<query.length();i++){
            Serial.println(obj.key);
          }
          
          String action = query.get("action").val;
          if(action=="開"||action=="on"){
            Serial.println("light been turn on!!");
            digitalWrite(LED_BUILTIN, HIGH);
          }else if(action=="關"||action=="off"){
            Serial.println("now, light been turn off");
            digitalWrite(LED_BUILTIN, LOW);
          }else{
            Serial.println("action: "+action);  
          }
          Serial.println(query.get("action").val+": "+query.get("turn").val);
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
//          client.println("Refre/sh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<body>");
          client.println(url);
          client.println("<h1>"+query.get("action").val+": "+query.get("turn").val+"</h1>");
          client.println("</body>");
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
