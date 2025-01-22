/**********************************************************
 * HTTPS Client Test
 * By John M. Wargo
 * htttps://johnwargo.com
 *
 * Based on the Arduino BasicHTTPSClient.ino sample sketch
 ***********************************************************/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

#include "caCert.h"
#include "constants.h"

const char *ssid = WIFI_SSID;
const char *pswd = WIFI_PSWD;
const char *targetUrl = "https://baconipsum.com/api/?type=meat-and-filler&paras=1";

int counter = 0;

NetworkClientSecure *client = new NetworkClientSecure;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Serial.print("\nConnecting to ");
  Serial.print(ssid);
  Serial.println(":");
  // Set Wi-Fi station mode, no incoming connections
  WiFi.mode(WIFI_STA);
  // connect to the Wi-Fi network
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    counter += 1;
    if (counter > 25)
    {
      counter = 0;
      Serial.println();
    }
  }
  Serial.println("\nWi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop()
{
  if (client)
  {
    client->setCACert(cert);
    HTTPClient https;
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, targetUrl))
    {
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0)
      {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          String payload = https.getString();
          Serial.println(payload);
        }
      }
      else
      {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
    else
    {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  else
  {
    Serial.println("Unable to create client");
    // fatal error, so go into an infinite loop
    for (;;)
    {
    }
  }
  Serial.println("\nWaiting 30 seconds...\n");
  delay(30000);
}
