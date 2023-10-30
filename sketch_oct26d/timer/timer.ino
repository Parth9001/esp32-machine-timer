#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

// const char* ssid = "TP-Link_5708";
const char* ssid = "So Ja Bro";
// const char* ssid = "H5Tech";
// const char* password = "93970105";
const char* password = "areysojabro";
// const char* password = "hostel5tech";
const int num = 10;
// const int buttonPins[num] = {19,12,27,25,33,32,4,5,18,23};
const int buttonPins[num] = {19,13,12,14,27,25,32,33,4,5};
int lastState[num] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
const int confirmButtonPin = 23;  
int lastConfirmState = HIGH;
const int resetButtonPin = 18; 
int lastResetState = HIGH;
int count = 0;
int time_taken = 0;

bool timerRunning;
time_t startingTimer;
int tempTimer = 0;

time_t lastButtonClick = time(NULL);
bool backLight = true;

LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Enter Time");
  Serial.begin(9600);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    // Serial.println("Connecting to WiFi...");
    lcd.setCursor(0,0);
    lcd.print("Connecting Wifi");
  }

  // Serial.println("Connected to WiFi");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected :)");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Time");

  timerRunning = false;

  for (int i = 0; i < num; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(confirmButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
}

void loop() {

  if(time(NULL)-lastButtonClick>60 && !timerRunning){
    lcd.noBacklight();
    backLight = false;
  }else{
    lcd.backlight();
    backLight = true;
  }

  //just in case WiFi gets disconnected
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connecting Wifi");
    lcd.setCursor(0,1);
    lcd.print("Please Wait...");
    delay(1000);
    return;
  }

  if(timerRunning){
    lcd.setCursor(0, 0);
    lcd.print(" Machine In Use");
    time_taken = -(time(NULL) - startingTimer)/60 + tempTimer;
    // Serial.println(time(NULL)-startingTimer);
    delay(1000);
  }else{
    lcd.setCursor(0, 0);
    lcd.print("   Enter Time   ");
  }
  
  //printing time on lcd
  lcd.setCursor(4, 1);
  lcd.print("Time: ");
  if(time_taken<10){
    lcd.print("0");
    lcd.print(time_taken);
  }
  else{
    lcd.print(time_taken);
  }

  //loop over all 12 buttons to check input
  buttonPress();
}

void buttonPress(){
  //reading Reset Button
  if (digitalRead(resetButtonPin) == LOW && lastResetState == HIGH) {
    lastResetState = LOW;
    handleResetButtonPress();
  }
  else if(digitalRead(resetButtonPin) == HIGH && lastResetState==LOW){
      lastResetState = HIGH;
  }

  if(timerRunning){
    return;
  }

  //reading number pins on ESP32
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
  //reading Confirm button
  if (digitalRead(confirmButtonPin) == LOW && lastConfirmState == HIGH) {
    lastConfirmState = LOW;
    handleConfirmButtonPress();
  }
  else if(digitalRead(confirmButtonPin) == HIGH && lastConfirmState==LOW){
      lastConfirmState = HIGH;
  }
  
}

void handleNumberButtonPress(int number) {
  Serial.print("Button Pressed: ");
  Serial.println(number);
  time_taken = time_taken * 10 + number;
  Serial.print("Time = ");
  Serial.println(time_taken);
  lastButtonClick=time(NULL);
}

String HOST_NAME = "http://192.168.132.101:8000/";
// String HOST_NAME = "http://192.168.1.100:8000/";
// String HOST_NAME = "http://172.20.10.5:8000";
// String HOST_NAME = "https://3e18-103-21-127-76.ngrok-free.app/";
// String HOST_NAME = "https://d1fb-2402-8100-2703-c2fe-dcf5-16f3-a6c6-109f.ngrok-free.app/";
String PATH_NAME = "timer/1";

void handleConfirmButtonPress() {
  bool reqSent = false;
  if(timerRunning == false){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CONFIRMED!");

    HTTPClient http;
    String url = HOST_NAME + PATH_NAME;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"timer\":" + String(time_taken)+ "}";

    lcd.setCursor(0,1);
    lcd.print("Sending Request");

    int httpCode = http.sendRequest("PUT", payload);
    if (httpCode > 0) {
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String response = http.getString();
        Serial.println(httpCode);
        Serial.println(response);

        lcd.setCursor(0,1);
        lcd.print("Request Sent :)  ");
        reqSent=true;
        startingTimer = time(NULL);
        timerRunning = true;
        tempTimer = time_taken;

        delay(1000);

      } else {
        // HTTP header has been send and Server response header has been handled
        // Serial.printf("[HTTP] PUT... code: %d\n", httpCode);
        lcd.setCursor(0,1);
        lcd.print("Failed: httpCode");
        delay(1000);
      }
    } else {
      // Serial.printf("[HTTP] PUT... failed, error: %s\n", http.errorToString(httpCode).c_str());
      lcd.setCursor(0,1);
        lcd.print("Failed: Bad Req!");
        delay(1000);
    }

    // if(reqSent==true){
    //   timerRunning = true;
      
    // }
    
    lcd.clear();
    http.end();
  }
}

void handleResetButtonPress() {
  // Serial.println("Reset Button Pressed");

  lcd.clear();
  // lcd.setCursor(0,0);
  // lcd.print("Reset Pressed");
  count = 0;
  time_taken = 0;
  timerRunning = false;
  lcd.clear();
}



