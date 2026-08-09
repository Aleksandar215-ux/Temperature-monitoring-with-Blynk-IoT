#define BLYNK_TEMPLATE_ID " " // upisati identifikator projekta
#define BLYNK_TEMPLATE_NAME " " // upisati naziv projekta
#define BLYNK_AUTH_TOKEN " " //upisati autentifikacioni token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 16
#define DHTTYPE DHT11
#define BUZZER 25
#define LED_ZELENA 2
#define LED_CRVENA 4
unsigned long previousBeep = 0;
bool alarmSent = false;
float threshold = 30;

char ssid[] = " "; //upisati naziv Wi-Fi mreze
char pass[] = " "; //upisati lozinku Wi_Fi mreze

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensor()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" °C  ");
  Blynk.virtualWrite(V0, t);
  if(t > threshold)
  {
      if (!alarmSent)
    {
          String poruka = "UPOZORENJE!!!!\nTemperatura je " + String(t) + " C";
          Blynk.logEvent("temperature_alarm", poruka);
        alarmSent = true;
    }

    Blynk.virtualWrite(V1,1);
    Blynk.virtualWrite(V2,0);
    Blynk.virtualWrite(V3,1);
    digitalWrite(LED_CRVENA,HIGH);
    digitalWrite(LED_ZELENA,LOW);
     if (millis() - previousBeep >= 10000)
    {
        previousBeep = millis();

        digitalWrite(BUZZER, HIGH);
        delay(300);         
        digitalWrite(BUZZER, LOW);
    }
  }
  else
  {
    alarmSent = false;
    digitalWrite(BUZZER, LOW);
    Blynk.virtualWrite(V1,0);
    Blynk.virtualWrite(V2,1);
    Blynk.virtualWrite(V3,0);
    digitalWrite(LED_CRVENA,LOW);
    digitalWrite(LED_ZELENA,HIGH);
  }
}

BLYNK_WRITE(V4)
{
  threshold = param.asFloat();

  Serial.print("Novi threshold: ");
  Serial.println(threshold);
}
void setup()
{
  
  Serial.begin(115200);
  pinMode(LED_ZELENA, OUTPUT);
  pinMode(LED_CRVENA, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();

  Serial.println("Povezivanje na WiFi...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensor);
}


void loop()
{
  Blynk.run();
  timer.run();
}