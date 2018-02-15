/*
========================================================================================================================================
RS232 LED Lights (Web Control)
========================================================================================================================================
This project deals with RS232 LED Lights which is controlled by GPIO at pins 3, 4, and 5. It uses the web server to control the LED from 
Off to On.

@package        RS232 LED Light (Web Control)
@copyright      Copyright (C) 2018. Benjamin Lu
@license        GNU General Public License v2 or later (http://www.gnu.org/licenses/gpl-2.0.html)
@author         Benjamin Lu (https://www.benjlu.com/)
========================================================================================================================================
*/

/*
========================================================================================================================================
Table of Content
========================================================================================================================================
 1. Require Files
 2. Variables
 3. Setup
 4. Loop
========================================================================================================================================
*/

/*
========================================================================================================================================
 1. Require Files
========================================================================================================================================
*/
#include <SPI.h>
#include <Ethernet.h>

/*
========================================================================================================================================
 2. Variables
========================================================================================================================================
*/
EthernetServer web_server(80);  // Creating a basic Web Server using Port 80 to communicate.

String http_request;

int redLEDPin = 3;
int yellowLEDPin = 4;
int greenLEDPin = 5;

int ledInput;
int ledStatus;
int off_on;

/*
========================================================================================================================================
 3. Setup
========================================================================================================================================
*/
void setup() {
  Serial232.begin(9600);
 
  if (Ethernet.begin() == 0) {
    Serial232.println("Failed to communicate with the DHCP Server");
  }
  delay(3000);
  Serial232.println("Initializing...");
  delay(2000);
  Serial232.print("Web Server's IP Address: ");
  delay(2000);
  Serial232.println(Ethernet.localIP());
  delay(2000);
  Serial232.println("Web Server has started.");

  web_server.begin();

  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
}

/*
========================================================================================================================================
 4.0 - Loop
========================================================================================================================================
*/
void loop() { 
  EthernetClient client = web_server.available();       // Try to get a client

  if (client) {                                         // Got Client
    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        http_request += c;

        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: Closed");
          client.println();

          /*
          ==============================================================================================================================
          Start the Web Page that contains all information for the LED Lights to display.
          ==============================================================================================================================
          */
          client.println("<!DOCTYPE html");
          client.println("<html lang=\"en-US\">");
          client.println("<head>");
          client.println("<title>LED Lights (Web Control)</title>");
          client.println("<meta charset=\"UTF-8\" />");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link href=\"https://gmpg.org/xfn/11\" rel=\"profile\">");
          client.println("</head>");
          client.println("<body>");
          ledProcessInformation(client);
          client.println("</body>");
          client.println("</html>");
          Serial.print(http_request);
          http_request = "";
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }
}

void ledProcessInformation(EthernetClient lpi) {
  if (Serial232.available() == 0) {
    // Wait for input.
    Serial232.println("Enter 1 to turn on RED LED, 2 to turn off Red LED.");
    
  }
  ledInput = Serial232.parseInt();

  switch (ledInput) {
    case 1: 
      if (ledInput == 1) {
        digitalWrite(3, HIGH);
        lpi.println("You have turn on the Red LED on.");
      } 
      break;
    case 2:
      if (ledInput == 2) {
        digitalWrite(3, LOW);
        lpi.println("You have turn on the Red LED off.");
      }
      break;
  }  
}
