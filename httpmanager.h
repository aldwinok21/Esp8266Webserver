#define ARDUINOJSON_USE_LONG_LONG 1
#include <ESP8266HTTPClient.h>

//Include Arduino Json library
#include <ArduinoJson.h>

const int httpsPort = 443;
// Withings http calls 
WiFiClient wificlient;
//sleep - GET
void call_sleep_summary(String token){
  HTTPClient https;

  WiFiClientSecure wclient;
  wclient.setInsecure();

  Serial.println(" HTTP POST...");
  https.begin(wclient,"https://customaticparts.com/servicePortal/app/api/");
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
  DynamicJsonDocument doc(500);
  
    // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, payload);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    https.end();
    return;
  }
  else{
  }

  /*"
   * 
   * SAMPLE OUTPUT FROM API 
   * {\"wakeupduration\":1680,
   * \"wakeupcount\":3,
   * \"durationtosleep\":1500,
   * \"remsleepduration\":5160,
   * \"durationtowakeup\":0,
   * \"total_timeinbed\":25380,
   * \"total_sleep_time\":23700,
   * \"sleep_efficiency\":0.93000000000000004884981308350688777863979339599609375,
   * \"sleep_latency\":1500,
   * \"wakeup_latency\":0,
   * \"waso\":-7560,
   * \"nb_rem_episodes\":4,
   * \"out_of_bed_count\":3,
   * \"lightsleepduration\":11520,
   * \"deepsleepduration\":7020}"
   */
  long sleepDuration = doc["deepsleepduration"].as<long>();
  int wakeupCount = doc["wakeupcount"].as<int>();
  int snoring = doc["snoring"].as<int>();
  float sleepEff = doc["sleep_efficiency"].as<float>();

    Serial.print("Wake up count: ");
  Serial.println(wakeupCount);
  Serial.print("Sleep Duration: ");
  Serial.println(sleepDuration);
  Serial.print(" Snoring: ");
  Serial.println(snoring);
   Serial.print(" SleepEff: ");
  Serial.println(sleepEff);

    https.end();
  }
