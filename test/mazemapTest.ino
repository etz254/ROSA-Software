/*
  Test MazeMap overlay functionality over HTTP. If successful, a MazeMap overlay centered on eZone with a blue marker generates continuously


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

// create MazeMap overlay continuously
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

        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          client.println("<head>");
              client.println("<meta name='viewport' id='vp' content='initial-scale=1.0,user-scalable=no,maximum-scale=1,width=device-width' />");
              client.println("<meta charset='utf-8' />");
          
              client.println("<link rel='stylesheet' href='https://api.mazemap.com/js/v2.0.14/mazemap.min.css'>");
              client.println("<script type='text/javascript' src='https://api.mazemap.com/js/v2.0.14/mazemap.min.js'></script>");
          
              client.println("<style>");
                  client.println("body { margin:0px; padding:0px; width: 100vw; height:100vh; }");
              client.println("</style>");
          client.println("</head>");

          client.println("<body>");
                  client.println("<div id='map' class='mazemap'></div>");
              
                  client.println("<script>");
              
                      client.println("var myMap = new Mazemap.Map({");
                          client.println("container: 'map',");
                          client.println("campuses: 309,");
                          client.println("center: {lng: 115.816100, lat: -31.979468},");
                          client.println("zoom: 18,");
                          client.println("scrollZoom: true,");
                          client.println("doubleClickZoom: true,");
                          client.println("touchZoomRotate: true,");
                          client.println("zLevelControl: true");
                      client.println("});");
              
                      client.println("myMap.on('load', function(){");
                          // MazeMap ready
              
                          client.println("var lngLat = myMap.getCenter();");
              
                          client.println("var marker = new Mazemap.MazeMarker( {");
                              client.println("color: 'MazeBlue',");
                              client.println("size: 36, ");
                              client.println("zLevel: 1");
                          client.println("} ).setLngLat( lngLat ).addTo(myMap);");
              
                      client.println("});");
              
                  client.println("</script>");
              client.println("</body>");

      client.println("</html>");

    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
    }
  }
}
