#include <espnow.h>
#include <ESP8266WiFi.h>

// Replace with the MAC address of the sender ESP
uint8_t senderAddress[] = {0xC8, 0xF0, 0x9E, 0x7A, 0xBB, 0x3C}; //C8:F0:9E:7A:BB:3C

void OnDataRecv(uint8_t *senderMac, uint8_t *data, uint8_t dataLen) {
  Serial.print("Received data from: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(senderMac[i], HEX);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.print(", data: ");
  for (int i = 0; i < dataLen; i++) {
    Serial.print(data[i]);
    Serial.print(" ");
    if(data[i] < 20){
      digitalWrite(2, HIGH);
    }

    else{
      digitalWrite(2, LOW);         
    }
     
  }
    
  Serial.println();
}

void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //print mac address of reciever device
  Serial.println(" ");
    Serial.println("MAC Address of ESP8266: " + WiFi.macAddress());

    
  // Initialize ESP-NOW
  if (esp_now_init() != ERR_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register callback function for receiving data
  

  // Register peer
  
 /* esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, senderAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ERR_OK){
    Serial.println("Failed to add peer");
    return;
  }*/
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
 //esp_now_register_recv_cb(OnDataRecv);
 //delay(500);
}
