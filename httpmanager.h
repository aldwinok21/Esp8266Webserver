#define ARDUINOJSON_USE_LONG_LONG 1
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//Include Arduino Json library
#include <ArduinoJson.h>

// Withings http calls 
WiFiClient wificlient;
//sleep - GET
void call_sleep_summary(String token){
  HTTPClient https;
  Serial.println(" HTTP POST...");
  https.begin(wificlient,"http://192.168.0.122/troubleshoot/troubleshoot/app/api/");
    https.addHeader("Content-Type",  "application/x-www-form-urlencoded");

    //create json request
    /*JSON format for the customaticparts api:
     * {
     *  'request_type': (String) sleep_summary,sleep_get,
     *  'token': (String) token,
     *  'starting_date': (Integer) 1,
     *  }
     *  
     * 
    */
    

    
    String payload_data = "request_type=sleep_summary&token="+token+"&starting_date=2";
    delay(500);
    int httpCode = https.POST(payload_data);
    String payload = https.getString();

    Serial.println(httpCode);
    Serial.println(payload);

  /* Deserialized the json object*/
  // Change Memory size if json data is too large.
  StaticJsonDocument<800> doc;
    String json = payload;

    // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    https.end();
    return;
  }
  else{
  }
  int sleepDuration = doc["asleepduration"];
  int snoring = doc["snoring"];
  int sleepScore = doc["sleep_score"];
  int sleepEff = doc["sleep_efficiency"];

  Serial.println("")
  
 Serial.println(doc);

    https.end();
  }
