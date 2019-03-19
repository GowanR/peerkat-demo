/*
 * ESP8266 Wi-Fi Button
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
#include <ESP8266WiFi.h>

// Replace with your SSID and Password
const char* ssid     = "peerkat";
const char* password = "doubleclick";
//const char* ssid     = "luminosity";
//const char* password = "sparky2018";

// Replace with your unique URL resource
const char* resource = "/click";

// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/button_pressed/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy";

// Maker Webhooks IFTTT


//######################################################################################################################################
// cmd --> 'ipconfig' --> ipv4 address
//
// Make sure this number is the same as your ipv4 address
//######################################################################################################################################
const char* server = "192.168.0.100";




//const char* server = "192.168.1.246";

void setup() {
  Serial.begin(115200); 

  initWifi();
  makeIFTTTRequest();

  // Deep sleep mode until RESET pin is connected to a LOW signal (pushbutton is pressed)
  ESP.deepSleep(0);
}
   
void loop() {
  // sleeping so wont get here
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 5000) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
     Serial.println("Failed to connect, going back to sleep");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
  client.print(String("GET ") + resource + 
                  " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" + 
                  "Connection: close\r\n\r\n");
                  
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
     Serial.println("No response, going back to sleep");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop();
}
