#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "Wifi_Name";//for me its redmi here
const char* password = "Password";//password

void setup()
{
  Serial.begin(115200);
  connectWiFi();
  server.begin();
}

void loop()
{

}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
