#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>

#include "webpage.h";
#include "httpmanager.h";
// Wifi Name
#define ssid "Aldwinok"
// Wifi Password
#define password "twoguysbuilders"

ESP8266WebServer server(80);

String deviceConnected = "";
String tokenRecieved = "";
String tokenRefresh = "";


String header;
unsigned long currentTime = millis();

//Return Webpage data
void webpage(){
 
    Serial.println("A client has connected... \n");
  server.send(200,"text/html",pageData(WiFi.localIP()));
}

// Update Token for Withings...
void set_token(){
  Serial.println("Incoming token request..");
  if(server.hasArg("token") && server.arg("token") != NULL){
    tokenRecieved = server.arg("token");
    server.send(200,"text/plain","{'success':1}");
    Serial.println("Token Value :" + tokenRecieved);
    }
    else{
      Serial.println("Client Invalid Request.");
          server.send(400,"text/plain","400: Invalid Request");

    }
}

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  Serial.begin(115200);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.print("IP ADDRESS ");
  Serial.println(WiFi.localIP());
  Serial.println("DateTime : " + currentTime);

  server.on("/",webpage);
  server.on("/setToken",HTTP_POST,set_token);
  server.begin();
}

// the loop function runs over and over again forever
void loop() {
  if(WiFi.status() == WL_CONNECTED){
    
    
  server.handleClient();
  if(tokenRecieved != ""){
    call_sleep_summary(tokenRecieved);
    delay(5000);
    }
  }
  else{
    Serial.println("Failed connecting to WiFi");
  }
}
