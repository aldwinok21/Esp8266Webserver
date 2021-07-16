#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>


#include "webpage.h";
#include "httpmanager.h";

#define server_ssid  "ESP8266"
#define server_pass  ""

ESP8266WebServer server(80);

String deviceConnected = "";
String tokenRecieved = "";
String tokenRefresh = "";
String ssid = "";
String password = "";
String statusconnect = "";
String header;
unsigned long currentTime = millis();

//Return Webpage data
void webpage(){
  if(WiFi.status() == WL_CONNECTED){
       server.send(200,"text/html",pageData(WiFi.localIP()));
    }
    else{
         server.send(200,"text/html",wifiPage(WiFi.localIP()));
    }
   delay(1000);
}

//Return Wifi page
void wifipage(){
  server.send(200,"text/html",wifiPage(WiFi.localIP()));
  delay(1000);

}

//Return server info

void wifiInfo(){
  String statusw = "Not Connected";
  if(WiFi.status() == WL_CONNECTED){
    statusw = "Connected";
    
  }
  server.send(200,"json","{\"token\":" +tokenRecieved+",\"ip_address\":"+WiFi.localIP().toString()+", \"status\":"+statusw+",\"w_ssid\":"+server_ssid+",\"apip\":"+WiFi.softAPIP().toString()+",\"c_ssid\":"+ssid+"}");
}

// Update Token for Withings...
void set_token(){
  Serial.println("Incoming token request..");
  if(server.hasArg("token") && server.arg("token") != NULL){
    tokenRecieved = server.arg("token");
    server.send(200,"json","{\"success\":1}");
    }
    else{
      Serial.println("Client Invalid Request.");
    server.send(200,"json","{\"success\":0}");

    }
  delay(1000);
}

//Update Wifi Credentials
void set_wifi_creds(){
    Serial.println("Wifi credential request..");
  if(server.hasArg("user") && server.arg("user") != NULL && server.hasArg("pass") && server.arg("pass") != NULL){
    ssid = server.arg("user");
    password = server.arg("pass");

    // Check if Connected to wifi
    if(wifi_connection()){
          server.send(200,"text/plain","{\"success\":1,\"ip_address\":\""+WiFi.localIP().toString()+"\"}");
          Serial.println("Wifi SSID :" + ssid );
      }
      else{
      Serial.println("Client Invalid Request.");
    server.send(200,"json","{\"success\":0}");
      }
    }
    else{
      Serial.println("Client Invalid Request.");
    server.send(200,"json","{\"success\":0}");

    }

}

// Set up Wifi Access point
void wifi_access_point(){
WiFi.softAP(server_ssid,server_pass);
IPAddress IP = WiFi.softAPIP();


}

// Connect to wifi
bool wifi_connection(){
  //number of reconnecting tries count max 20
  WiFi.begin(ssid,password);
  int tries = 0;
  int max_count = 20;
  
  while(WiFi.status() != WL_CONNECTED and tries < max_count){
    delay(500);
    Serial.print(".");
    tries++;
  }
  
  if(WiFi.status() == WL_CONNECTED){
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.print("IP ADDRESS ");
  Serial.println(WiFi.localIP());
  statusconnect = "connected";
  return true;
  }
  else{
      Serial.println("Failed to connect.");
      statusconnect = "disconnected";
      return false;
  }
}

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  wifi_access_point();

  server.on("/",webpage);
  server.on("/settings",wifipage);

  server.on("/serverInfo",HTTP_POST,wifiInfo);

  server.on("/setToken",HTTP_POST,set_token);
  server.on("/setWifi",HTTP_POST,set_wifi_creds);


  server.begin();

  Serial.println("AP IP address: ");
  Serial.println(WiFi.softAPIP());
}

// the loop function runs over and over again forever
void loop() {
  server.handleClient();
  if(WiFi.status() == WL_CONNECTED){
  if(tokenRecieved != ""){
    // function found in httpmanager.h
    call_sleep_summary(tokenRecieved);
    delay(5000);
    }
  }
  else{
    //Serial.println("Failed connecting to WiFi. Reconnecting...");
    //wifi_connection();
          //wifi_connection();

  }
}
