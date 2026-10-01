# 🌤️ Autonomiczna Stacja Pogodowa IoT (Projekt Akademicki)

System mikroprocesorowy do ciągłego monitorowania parametrów atmosferycznych: temperatury, wilgotności względnej oraz prędkości wiatru.

![Licencja](https://img.shields.io/badge/License-MIT-blue.svg)
![Platforma](https://img.shields.io/badge/Hardware-Arduino_%7C_ESP32_%7C_Raspberry_Pi-orange)
![Status](https://img.shields.io/badge/Status-Ready-brightgreen)

---

## 📌 1. Opis Projektu
Projekt został wykonany na potrzeby zajęć akademickich. Celem projektu było stworzenie autonomicznego układu pomiarowego, który zbiera dane z czujników w czasie rzeczywistym i przelicza je na jednostki fizyczne.

### Główne Funkcjonalności:
- Pomiar temperatury powietrza z dokładnością do ±0.5°C.
- Pomiar wilgotności względnej powietrza (0–100% RH).
- Pomiar prędkości wiatru za pomocą anemometru czaszowego z czujnikiem impulsowym (kontaktronowym).
- Rejestracja zdarzeń z wykorzystaniem przerwań sprzętowych (Hardware Interrupts).

---

## 🛠️ 2. Wykaz Komponentów (BOM)

| Element | Model / Specyfikacja | Rola w projekcie |
| :--- | :--- | :--- |
| **Jednostka główna** | Arduino / ESP32 / Raspberry Pi | Pobór i przetwarzanie danych |
| **Czujnik Temp. i Wilgotności** | DHT22 (AM2302) / BME280 | Pomiar temperatury i wilgotności |
| **Czujnik Wiatru** | Anemometr czaszowy (Kontaktron) | Zliczanie obrotów na czas |
| **Rezystor Pull-Up** | 10kΩ | Stabilizacja sygnału z czujnika DHT |
| **Zasilanie** | USB 5V lub Ogniwo 18650 Li-Ion | Zasilanie układu pomiarowego |

---

## 🔌 3. Schemat Połączeń (Pinout)

```
       +-----------------------+
       |   ESP32 / ARDUINO     |
       +-----------------------+
       |  5V / 3.3V   <---> VCC|---> DHT22 / Anemometr
       |  GND         <---> GND|---> DHT22 / Anemometr
       |  Pin D2      <---> DATA---> DHT22 (z rezystorem 10k do VCC)
       |  Pin D3      <---> SIG |---> Anemometr (Przerwanie INT0)
       +-----------------------+
```

---

## 🚀 4. Szybki Start i Uruchomienie

### Wariant A: Arduino / ESP32
1. Otwórz plik `src/main.ino` w **Arduino IDE**.
2. Zainstaluj bibliotekę **DHT sensor library** (Adafruit).
3. Wybierz odpowiednią płytkę i port COM, a następnie wgraj program.

### Wariant B: Raspberry Pi (Python)
1. Upewnij się, że masz zainstalowany Python 3 oraz biblioteki GPIO:
   ```bash
   pip3 install RPi.GPIO Adafruit_DHT
   ```
2. Uruchom skrypt pomiarowy:
   ```bash
   python3 src/weather_station.py
   ```

---

## 📜 Licencja
Projekt udostępniany na licencji **MIT**. Wszelkie prawa zastrzeżone.
