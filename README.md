Wi-Fi connected environmental monitor built on an ESP32 and a DHT11 sensor. Readings stream in real time to the Blynk IoT platform, and the device raises visual and audible alerts when a configured threshold is exceeded.

Hardware
Component	Model	Purpose
Microcontroller	ESP32	Wi-Fi connectivity and sensor readout
Sensor	DHT11	-Temperature and relative humidity
Indicator	 LED -	Visual alert on threshold breach
Buzzer	ld bzpg-2312 active buzzer -	Audible alert

Wiring: 
GPI0 2 - Green LED 
GPI0 4 - RED LED
GPIO 16 - DATA DHT11
GPI0 25 - LD BZPG-2312

How it works
The ESP32 connects to the local Wi-Fi network and authenticates with Blynk Cloud.
Temperature and humidity are sampled every <!-- FILL: interval --> and pushed to virtual pins on the Blynk dashboard.
If a reading crosses the configured threshold, the device triggers the LED and buzzer locally and sends a notification through Blynk.

Local alerting is deliberate: the device keeps warning even if the internet connection drops, so a failure of the cloud service does not mean a silent failure of the monitor.

Blynk dashboard
<img width="921" height="2048" alt="WhatsApp Image 2026-07-22 at 11 12 39" src="https://github.com/user-attachments/assets/aa3b21fb-1533-4cdf-9704-d572a53e192d" />



 I fotografiju sklopa: ![Hardware setup]
 <img width="1019" height="765" alt="image" src="https://github.com/user-attachments/assets/d64a064d-46d4-4f8c-9add-e4578926a576" />

Configuration
cpp
// Set before flashing:
#define BLYNK_TEMPLATE_ID   "..."
#define BLYNK_AUTH_TOKEN    "..."
char ssid[] = "...";
char pass[] = "...";

Required libraries: Blynk, DHT sensor

Limitations and next steps
DHT11 has coarse resolution (±2 °C); a DHT22 or SHT31 would be a straight upgrade
Depends on Wi-Fi coverage — see the LoRa version for a long-range, low-power alternative
No local logging: readings are lost if the connection drops
Author

Aleksandar Popović — MSc Mechatronics, University of Novi Sad LinkedIn · apopovic915@gmail.com
