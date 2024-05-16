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

#define trigPin D0
#define echoPin D1
#define ledP1 D6

BlynkTimer timer;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
bool lampu = false;

float jarakCm, jarakInch;

WiFiServer server(80); // Initialize the web server on port 80


void setup() {
  Serial.begin(115200); // Starts the serial communication
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, ssid_pass, "blynk.cloud", 80);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  pinMode(ledP1, OUTPUT);

  // Connecting to a WiFi network
    WiFi.begin(ssid, ssid_pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to the WiFi network");

    // Connecting to an MQTT broker
    client.setServer(mqtt_broker, mqtt_port); //konek ke mqtt broker
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
     // Publish and subscribe
    client.subscribe(topic_Command);
    client.subscribe(topic_Data);
}


void loop() {
  client.loop();
  Blynk.run();
  timer.run();

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = (duration/2) / 29.1;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  client.setCallback(callback);
  Blynk.virtualWrite(V0, distanceCm);
  Blynk.virtualWrite(V1, distanceInch);

 // Check if any reads failed and exit early (to try again).
  if (isnan(distanceCm) || isnan(distanceInch)) {
    Serial.println(F("Failed to read from distanceCm or distanceInch"));
    return;
  }

  // Prints the distance on the Serial Monitor
  Serial.println("-----------------");
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  Serial.print("Status LED: ");

  if (distanceCm >= 4) {
    digitalWrite(ledP1, HIGH);
    Serial.println("OFF");
  } else {
    digitalWrite(ledP1, LOW);
    Serial.println("ON");
  }

  Serial.println("-----------------");
  
  delay(1000);
}


void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message: ");
    String message;

    for (int i = 0; i < length; i++) {
        message += (char) payload[i];  // Convert *byte to string
    }
    Serial.print(message);
    

    if (strcmp(topic, topic_Command)==0) {
      if (message == "Jarak1"){ 
        client.publish(topic_Data, String(distanceCm).c_str());
      }
    }

    Serial.println();
    Serial.println("-----------------------");
}

BLYNK_WRITE(V2) {
  int buttonState = param.asInt();
  if (buttonState == 1) {
    client.publish(topic_Command, "Jarak1");
  }
}