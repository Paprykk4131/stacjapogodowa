/*
 * Autonomiczna Stacja Pogodowa - Kod dla Arduino / ESP32
 * Pomiar temperatury, wilgotności oraz prędkości wiatru z użyciem przerwań.
 */

#include <DHT.h>

#define DHTPIN 2          // Pin cyfrowy połączony z sygnałem DHT22
#define DHTTYPE DHT22     // Typ czujnika (DHT22)
#define WIND_PIN 3        // Pin cyfrowy anemometru (wymaga interfejsu Interrupt)

DHT dht(DHTPIN, DHTTYPE);

// Zmienne do obsługi przerwania anemometru
volatile unsigned long pulseCount = 0;
unsigned long lastSampleTime = 0;
const unsigned long sampleInterval = 3000; // Czas próbkowania: 3 sekundy

// Funkcja obsługi przerwania (ISR) dla anemometru
void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("--- Inicjalizacja Stacji Pogodowej ---"));

  dht.begin();

  // Konfiguracja pinu anemometru z wbudowanym rezystorem Pull-Up
  pinMode(WIND_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WIND_PIN), countPulse, RISING);
}

void loop() {
  unsigned long currentTime = millis();

  // Odczyt i przeliczenie danych co 3 sekundy
  if (currentTime - lastSampleTime >= sampleInterval) {
    
    // Odczyt z czujnika DHT22
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Wyłączenie przerwań na czas odczytu zmiennej pulseCount
    noInterrupts();
    unsigned long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    // Obliczanie prędkości wiatru:
    // Założenie: 1 obrót na sekundę (1 Hz) = 2.4 km/h dla standardowego anemometru
    float timeSec = (currentTime - lastSampleTime) / 1000.0;
    float rps = pulses / timeSec; // Obroty na sekundę
    float windSpeed = rps * 2.4;  // Prędkość w km/h

    lastSampleTime = currentTime;

    // Sprawdzenie poprawności odczytów DHT
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Błąd odczytu z czujnika DHT22!"));
      return;
    }

    // Wyświetlenie wyników w Porcie Szeregowym
    Serial.print(F("[POMIAR] Temp: "));
    Serial.print(temperature, 1);
    Serial.print(F(" °C | Wilgotność: "));
    Serial.print(humidity, 1);
    Serial.print(F(" % | Prędkość wiatru: "));
    Serial.print(windSpeed, 2);
    Serial.println(F(" km/h"));
  }
}