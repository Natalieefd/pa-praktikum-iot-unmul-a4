#define BLYNK_TEMPLATE_ID "TMPL6BnclZkL7"
#define BLYNK_TEMPLATE_NAME "kel4pa"
#define BLYNK_AUTH_TOKEN "-4ZL1S3LeY_KZXmsnxsJVyD5Ciwa9ErT"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PubSubClient.h>

char ssid[] = "o.o";
char ssid_pass[] = "mauapakamuu";

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic_Command = "kelompok-4/command";
const char *topic_Data = "kelompok-4/data";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

#define buzzerP1 D7

float distanceCm;
unsigned long buzzerStartTime = 0;
const unsigned long BUZZER_DURATION = 3000; // 3 seconds in milliseconds

BlynkTimer timer;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, ssid_pass, "blynk.cloud", 80);

  pinMode(buzzerP1, OUTPUT);

  // Connecting to a WiFi network
  WiFi.begin(ssid, ssid_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");

  // Connecting to an MQTT broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    String client_id = "mqttx_626c0481";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public EMQX MQTT broker connected");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  
  // Subscribe to topics
  client.subscribe(topic_Command);
  client.subscribe(topic_Data);
}

void loop() {
  client.loop();
  Blynk.run();
  timer.run();
}

void callback(char *topic, byte *payload, unsigned int length) {
  String message;
  
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (strcmp(topic, topic_Data) == 0) {
    distanceCm = message.toFloat();  // Update the global distanceCm variable
    Blynk.virtualWrite(V0, distanceCm);
    Blynk.virtualWrite(V1, distanceCm * 0.393701);

    if (distanceCm >= 4) {
      tone(buzzerP1, 1000);
      delay(5000);
      noTone(buzzerP1);

    } else {
      noTone(buzzerP1);
    }
  }

  Serial.println("Message arrived in topic: " + String(topic));
  Serial.println("Message: " + message);
}
