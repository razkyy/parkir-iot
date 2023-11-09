#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Daimyo";
const char *password = "Ol!v3Tr30";

// Define the URL for your PHP script that will handle the data
String serverUrl = "http://192.168.100.6:8000/simpan-sensor";

void setup() {
  Serial.begin(115200);
  connectToWifi();
}
void connectToWifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n'); // Read data until a newline character

    // Split the received data using the ',' character as the delimiter
    String dataValues[6];
    int dataIndex = 0;
    int start = 0;

    for (int i = 0; i < receivedData.length(); i++) {
      if (receivedData[i] == ',') {
        dataValues[dataIndex] = receivedData.substring(start, i);
        dataIndex++;
        start = i + 1;
      }
    }

    // Print the individual data values
    for (int i = 0; i < 6; i++) {
      Serial.print("Data ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(dataValues[i]);
    }

  // Create a WiFiClient instance
    WiFiClient client;

    // Create an HTTP object with the WiFiClient instance
    HTTPClient http;
    

    // Construct the POST data
    String postData = "sensor1=" + dataValues[0] +
                     "&sensor2=" + dataValues[1] +
                     "&sensor3=" + dataValues[2] +
                     "&sensor4=" + dataValues[3] +
                     "&sensor5=" + dataValues[4] +
                     "&sensor6=" + dataValues[5];


    String serverPath = serverUrl + "?" + postData;
    Serial.println(serverPath);
    http.begin(client, serverPath.c_str());
    // Make the HTTP POST request
    int httpCode = http.GET();

    // Check the HTTP response
    if (httpCode == HTTP_CODE_OK) {
      Serial.println("Data sent successfully");
    } else {
      Serial.print("HTTP error code: ");
      Serial.println(httpCode);
    }

    http.end();
  }
}




