/**********************************************************
 * HTTPS Client Test
 * By John M. Wargo
 * htttps://johnwargo.com
 *
 * Based on the Arduino BasicHTTPSClient.ino sample sketch
 ***********************************************************/

#include <Arduino.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>
#include <WiFi.h>

#include "cert.h"
#include "constants.h"

const char *ssid = WIFI_SSID;
const char *pswd = WIFI_PSWD;
const char *targetUrl =
    "https://baconipsum.com/api/?type=meat-and-filler&paras=1";

int counter = 0;

HTTPClient https;
NetworkClientSecure *client = new NetworkClientSecure;

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.print("\nConnecting to ");
  Serial.print(ssid);
  Serial.println(":");
  // Set Wi-Fi station mode, no incoming connections
  WiFi.mode(WIFI_STA);
  // connect to the Wi-Fi network
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter += 1;
    if (counter > 25) {
      counter = 0;
      Serial.println();
    }
  }
  Serial.println("\nWi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  if (client) {
    client->setCACert(caCert);
    Serial.println("[HTTPS] Begin");
    if (https.begin(*client, targetUrl)) {
      Serial.println("[HTTPS] GET");
      // start connection to host as a GET request
      int httpCode = https.GET();
      // httpCode is negative on library error
      if (httpCode > 0) {
        // Request sent and response handled
        Serial.printf("[HTTPS] Response: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET failed, error: %s\n",
                      https.errorToString(httpCode).c_str());
      }
      // close the connection
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  } else {
    Serial.println("Unable to create client");
    // fatal error, so go into an infinite loop
    for (;;) {
    }
  }
  Serial.println("\nWaiting 30 seconds...\n");
  delay(30000);
}
