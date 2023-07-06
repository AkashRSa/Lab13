#include "MQTT.h"
#include "oled-wing-adafruit.h"

SYSTEM_THREAD(ENABLED);

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);
OledWingAdafruit display;
String information = "";
void setup()
{
  Serial.begin(9600);
  while (!Serial.isConnected())
  {
  }
  display.setup();
  display.clearDisplay();
  client.subscribe("inTopic/message");
  Serial.println("Setup");
}

void loop()
{
  display.loop();
  display.clearDisplay();
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("inTopic/message");
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(information);
  display.display();
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.println(p);
  information = p;
}