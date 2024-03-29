/*
  Test for ROSA connectivity to server via HTTP as a client. If successful, server output should continuously display the following message: "HTTP Client Connection Successful!. Client disconnecting..."
  If not successful, an output is displayed to the serial monitor with "Error: Connection failed."
  Written by ELEC5552 Team 25.
  Last revision 24.10.2019
  
 */

// initialise libraries
#include <SPI.h>
#include <Ethernet2.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialise the Ethernet server and all necessary values. Initialise Arduino data input pin
EthernetServer server(80);

// initialise Arduino Serial Monitor
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

// performs client connection and disconnection continuously
void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // output connection status
          client.print("HTTP Client Connection Successful!. Client disconnecting...");

            client.println("<br />");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(9600);
    
    // Serial monitor
    Serial.println("Connection Successful! \n");
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }

  else {
    // Connection failed
    // output to Serial monitor

          delay(1000);
          Serial.println("Error: Connection failed \n");
  }
}
