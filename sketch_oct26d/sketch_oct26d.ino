#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>

// const char* ssid = "TP-Link_5708";
const char* ssid = "H5Tech";
// const char* password = "93970105";
const char* password = "hostel5tech";
const int num = 10;
const int buttonPins[num] = {19,12,27,25,33,32,4,5,18,23};
int lastState[num] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
const int confirmButtonPin = 14;  
int lastConfirmState = HIGH;
const int resetButtonPin = 13; 
int lastResetState = HIGH;
int count = 0;
int time_taken = 0;


LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
  // lcd.begin();
  // lcd.backlight();
  // lcd.setCursor(0,0);
  // lcd.print("ShrikantKiMaa");
  Serial.begin(9600);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  delay(100);
  for (int i = 0; i < num; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(confirmButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
}

void loop() {
  lcd.setCursor(7, 1);
  if(time_taken<10){
    lcd.print("0");
    lcd.print(time_taken);
  }
  else
    lcd.print(time_taken);
  for (int i = 0; i < num; i++) {
    if(count == 2)
      break;
    if (digitalRead(buttonPins[i]) == LOW && lastState[i]==HIGH) {
      lastState[i] = LOW;
      count++;
      handleNumberButtonPress(i);
    }
    else if(digitalRead(buttonPins[i]) == HIGH && lastState[i]==LOW){
      lastState[i] = HIGH;
    }
  }

  if (digitalRead(confirmButtonPin) == LOW && lastConfirmState == HIGH) {
    lastConfirmState = LOW;
    handleConfirmButtonPress();
  }
  else if(digitalRead(confirmButtonPin) == HIGH && lastConfirmState==LOW){
      lastConfirmState = HIGH;
    }

  if (digitalRead(resetButtonPin) == LOW && lastResetState == HIGH) {
    lastResetState = LOW;
    handleResetButtonPress();
  }
  else if(digitalRead(resetButtonPin) == HIGH && lastResetState==LOW){
      lastResetState = HIGH;
    }
}

void handleNumberButtonPress(int number) {
  Serial.print("Button Pressed: ");
  Serial.println(number);
  time_taken = time_taken * 10 + number;
  Serial.print("Time = ");
  Serial.println(time_taken);
}

String HOST_NAME = "http://192.168.0.113:8000/";
String PATH_NAME = "timer/1";

void handleConfirmButtonPress() {
  Serial.println("Confirm Button Pressed");
  if(time_taken != 0 )
  {
    
  HTTPClient http;

  String url = HOST_NAME + PATH_NAME;
  
  http.begin(url);
 
  http.addHeader("Content-Type", "application/json");
  String payload = "{\"timer\":" + String(time_taken)+ "}";

  int httpCode = http.sendRequest("PUT", payload);
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      Serial.println(httpCode);
      Serial.println(response);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] PUT... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] PUT... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  }
}

void handleResetButtonPress() {
  Serial.println("Reset Button Pressed");
  count = 0;
  time_taken = 0;
}



