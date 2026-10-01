#!/usr/bin/env python3
"""
Autonomiczna Stacja Pogodowa - Skrypt dla Raspberry Pi
Pomiar temperatury, wilgotności i prędkości wiatru z użyciem RPi.GPIO
"""

import time
import RPi.GPIO as GPIO
import Adafruit_DHT

# Konfiguracja Pinów GPIO (numeracja BCM)
DHT_SENSOR = Adafruit_DHT.DHT22
DHT_PIN = 4
WIND_PIN = 17

# Zmienne globalne
pulse_count = 0
SAMPLE_INTERVAL = 3.0  # Czas pomiaru w sekundach

def wind_pulse_callback(channel):
    """Funkcja callback wywoływana przy każdym impulsie z anemometru."""
    global pulse_count
    pulse_count += 1

def main():
    global pulse_count

    # Konfiguracja GPIO
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(WIND_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    # Rejestracja przerwania na opadające zbocze sygnału (FALLING)
    GPIO.add_event_detect(WIND_PIN, GPIO.FALLING, callback=wind_pulse_callback, bouncetime=20)

    print("--- Stacja Pogodowa Uruchomiona (Raspberry Pi) ---")
    print("Naciśnij Ctrl+C, aby zakończyć.\n")

    try:
        while True:
            start_time = time.time()
            pulse_count = 0
            
            # Odczekanie interwału pomiarowego
            time.sleep(SAMPLE_INTERVAL)
            
            elapsed_time = time.time() - start_time
            
            # Odczyt z czujnika DHT22
            humidity, temperature = Adafruit_DHT.read_retry(DHT_SENSOR, DHT_PIN)
            
            # Obliczenie prędkości wiatru (1 Hz = ~2.4 km/h)
            current_pulses = pulse_count
            rps = current_pulses / elapsed_time
            wind_speed = rps * 2.4

            if humidity is not None and temperature is not None:
                print(f"[POMIAR] Temp: {temperature:.1f}°C | "
                      f"Wilgotność: {humidity:.1f}% | "
                      f"Wiatr: {wind_speed:.2f} km/h")
            else:
                print("[BŁĄD] Nie udało się pobrać danych z czujnika DHT22.")

    except KeyboardInterrupt:
        print("\nZatrzymywanie programu...")
    finally:
        GPIO.cleanup()
        print("Czyszczenie pinów GPIO zakończone.")

if __name__ == "__main__":
    main()