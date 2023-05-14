#include <esp_now.h>
#include <WiFi.h>
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h" 
  
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData Data;

bool flag = true;
#define BUTTON_PIN 18
// Replace with the MAC address of the receiver ESP
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void setup() {
  //set button pin D2 GPIO 2 pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("MAC Address of ESP32: ");
  Serial.println(WiFi.macAddress());
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

}

void loop() {
  // Send data

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  Data.Y = map(ay, -17000, 17000, 0, 255); 
  Data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  delay(500);
  Serial.print("Axis X = ");
  Serial.print(Data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.print(Data.Y);
  Serial.print("  ");
  Serial.print("Axis Z  = ");
  Serial.println(Data.Z);

  /*if(digitalRead(data.X > 20 && data.Y > 20 && data.Y > 20 ){
    Serial.println("Light ON bitches !");
    uint8_t data[] = {data.X,data.Y,data.Z};
    esp_err_t result = esp_now_send(broadcastAddress, data, sizeof(data));
    if (result == ESP_OK) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Error sending data");
    }
    flag = !flag;
  }*/
  //else{
   uint8_t data[] = {Data.X,Data.Y,Data.Z};
   esp_err_t result = esp_now_send(broadcastAddress, data, sizeof(data));
    if (result == ESP_OK) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Error sending data");
    }

  
  //}
  
  delay(500);
}
