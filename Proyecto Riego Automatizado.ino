#include <DHT.h> 

#define DHTPIN 13 
#define DHTTYPE DHT11 

#define SOIL_MOISTURE_PIN A0 
#define WATER_LEVEL_PIN A1 
#define RELAY_PIN 2 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.flush();
  Serial.begin(9600);
  pinMode(SOIL_MOISTURE_PIN, INPUT); 
  pinMode(WATER_LEVEL_PIN, INPUT); 
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  delay(2000);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  int soil_moisture = analogRead(SOIL_MOISTURE_PIN); 
  int water_level = analogRead(WATER_LEVEL_PIN); 

  float soil_humidity = map(soil_moisture, 0, 1023, 0, 100);
  int water_level_percent = map(water_level, 0, 700, 0,65 );

  if (isnan(t) || isnan(h)) {
    Serial.println("Falla de lectura del DHT");
  } else {
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" %\t"); 
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" °C"); 
  }

  if (water_level_percent < 40) {
    digitalWrite(RELAY_PIN, HIGH);
  }
  else if (water_level_percent > 50) {
    if (soil_humidity < 40) {
      digitalWrite(RELAY_PIN, LOW);
    } 
    else {
      digitalWrite(RELAY_PIN, HIGH);
    }
   }
  delay(1000);
}

