#include <SPI.h> 
#include <WiFi.h>
#include <BoltDeviceCredentials.h>
#include <BoltIoT-Arduino-Helper.h>
int lpin=6;
WiFiServer server(80);
  void setup() {
    boltiot.Begin(Serial); //Initialize the Bolt interface over serial uart. Serial could be replaced with Serial0 or Serial1 on Arduino mega boards.
         //In this example Tx pin of Bolt is connected to Rx pin of Arduino Serial Port
         //and Rx pin of Bolt is connected to tx pin of arduino Serial Port
    analogWrite(lpin,200); //Set pin 2 as input. We will send this pin's state as the data to the Bolt Cloud
  }
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
   // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
       // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Value at A0 is ");
            client.print(analogRead(A0));
            client.print("<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /ON")) {
          digitalWrite(lpin, HIGH);
        }
        if (currentLine.endsWith("GET /OFF")) {
          digitalWrite(lpin, LOW);
        }
        if (currentLine.endsWith("GET /SLEEP")) {
          analogWrite(lpin, 25);
        }
        if (currentLine.endsWith("GET /STUDY")) {
          analogWrite(lpin, 100);
        }
        if (currentLine.endsWith("GET /SEARCH")) {
          analogWrite(lpin, 255);
        }
      }
    }
    // close the connection:
    client.stop();
   // Serial.println("client disconnected");
  }
}
