#define BLYNK_TEMPLATE_ID "TMPLAGLILf9P"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "9q7Cp5bNVYTsZlOZ9BE-TWyz3n_76Vau"

#define trig D0
#define echo D1
#define yel D2
#define buz D4
#define red D5
#define gre D8
bool ok = 0;


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

bool Relay = 0;
char ssid[] = "WiFi-2.4G";
char pass[] = "";
BlynkTimer timer;
double duration, distance, percentage;

void ultra()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  Blynk.virtualWrite(V2, distance);
  percentage = (20 - distance) * 100 / 17;
  Serial.print("Percentage: ");
  Serial.println(percentage);
  Blynk.virtualWrite(V0, percentage);

  if(percentage <= 20 or percentage > 90) {
    digitalWrite(red, HIGH);
  }
  else {
    digitalWrite(red, LOW);
  }
  if(percentage > 20 and percentage <= 60) {
    digitalWrite(yel, HIGH);
  }
  else {
    digitalWrite(yel, LOW);
  }
  if(percentage > 60 and percentage <= 90) {
    digitalWrite(gre, HIGH);
  }
  else digitalWrite(gre, LOW);
  if(ok == 0) {
    if(percentage > 90) {
      Blynk.logEvent("level_warning", "Your tank is almost full. Please turn off the motor.");
      ok = 1;
    }
    else if(percentage <= 20) {
      Blynk.logEvent("level_warning", "Your tank is almost empty. Please turn on the motor.");
      ok = 1;
    }
  }
}

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yel, OUTPUT);
  pinMode(gre, OUTPUT);
  pinMode(buz, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(50, ultra);
}

void loop()
{
  Blynk.run();
  timer.run();
}
