# Elektroniczny Świerszcz z ATtiny85 🦗

## 🇵🇱 Opis projektu
"Elektroniczny Świerszcz" to mały, energooszczędny generator dźwięków oparty na mikrokontrolerze **ATtiny85**, który zaskoczy każdego realistycznym odgłosem świerszcza 🦗, a także piskiem. Projekt został stworzony jako **żart** – urządzenie można łatwo ukryć w pokoju znajomego, aby generowało losowe dźwięki w nieregularnych interwałach, np. w nocy. Idealnie sprawdzi się jako zabawny sposób na rozbawienie (lub drobną irytację 😄) kogoś bliskiego.

Urządzenie posiada 4 różne tryby:
- Tryb 0: Sam świerszcz (interwały 2-4 godziny)
- Tryb 1: Sam pisk (interwały 2-4 godziny)
- Tryb 2: Świerszcz i pisk (interwały co 10 sekund – przydatne do testowania głośności po ukryciu)
- Tryb 3: Losowe dźwięki (świerszcz lub pisk w interwałach 2-4 godziny)

---

## Zdjęcia układu

### Cały układ
![Zdjęcie całego układu](images/układ.jpg)


---

## Funkcjonalności
- **Tryby dźwięku**:
  - Realistyczny odgłos świerszcza
  - Ton C (pisk)
  - Seria krótkich beepów
  - Naprzemienne dźwięki świerszcza i piska
- **Losowe interwały**:
  - Od 2 do 4 godzin (lub 10 sekund w trybie naprzemiennym).
- **Tryb uśpienia**:
  - Między generowaniem dźwięków mikrokontroler przechodzi w tryb uśpienia, aby oszczędzać energię. Dzięki temu urządzenie na baterii CR2450 wytrzyma nawet około roku.
- **Idealne do pranków**:
  - Ukryj urządzenie w pokoju znajomego, aby w nocy generowało odgłosy świerszcza albo piska w losowych odstępach.

---

## Wymagane komponenty
- Mikrokontroler **ATtiny85**
- Buzzer piezoelektryczny lub mały głośnik
- Przycisk (do zmiany trybu)
- Przełącznik zasilania (3-nóżkowy)
- Bateria **CR2450 3V** lub inna bateria o odpowiednim napięciu
- Rezystor 10kΩ (do podciągania pinu przycisku, opcjonalnie do wyciszenia buzzera)

---

## Podłączenie
1. **SPEAKER1**: Podłącz do pinu **PB1** mikrokontrolera.
2. **SPEAKER2**: Podłącz do pinu **PB2** mikrokontrolera.
3. **BUTTON_PIN**: Podłącz przycisk do pinu **PB0**, dodając rezystor podciągający 10kΩ do VCC.
4. **Przełącznik zasilania**:
   - Środkowa nóżka do +V baterii.
   - Jedna zewnętrzna nóżka do VCC układu.
   - Druga zewnętrzna nóżka do GND.

---

## Jak działa urządzenie?
1. Po włączeniu, układ automatycznie generuje dźwięk świerszcza.
2. Za pomocą przycisku możesz przełączać między trybami:
   - Tryb 0: Realistyczny dźwięk świerszcza (interwały 2-4 godziny)
   - Tryb 1: Pisk (interwały 2-4 godziny)
   - Tryb 2: Naprzemienne dźwięki świerszcza i piska (interwały co 10 sekund – przydatne do testowania ukrytego urządzenia)
   - Tryb 3: Seria losowych beepów (świerszcz lub pisk w interwałach 2-4 godziny)
3. Między odtwarzaniem dźwięków mikrokontroler przechodzi w tryb uśpienia, minimalizując zużycie baterii.

---

## Licencja
Projekt dostępny na licencji **MIT**.


# Electronic Cricket with ATtiny85 🦗

## 🇬🇧 Project Description
The "Electronic Cricket" is a small, energy-efficient sound generator based on the **ATtiny85** microcontroller. It surprises everyone with its realistic cricket-like chirps 🦗 and high-pitched beeps. The project is designed as a **prank** – you can easily hide the device in a friend's room to generate random sounds at irregular intervals, such as at night. It's a fun way to amuse (or mildly annoy 😄) someone close to you.

The device has 4 modes:
- Mode 0: Cricket sound only (intervals of 2-4 hours)
- Mode 1: High-pitched beep only (intervals of 2-4 hours)
- Mode 2: Cricket and beep sound alternation (intervals every 10 seconds – useful for testing the sound after hiding the device)
- Mode 3: Random sounds (cricket or beep in intervals of 2-4 hours)

---

## Pictures of the Circuit

### Full Circuit
![Full Circuit Picture](images/układ.jpg)

---

## Features
- **Sound Modes**:
  - Realistic cricket chirp
  - Tone C (high-pitched beep)
  - Series of short beeps
  - Alternating cricket and beep sounds
- **Random Intervals**:
  - From 2 to 4 hours (or 10 seconds in alternating mode).
- **Sleep Mode**:
  - Between sounds, the microcontroller enters sleep mode to save energy. Thanks to this, the device can last up to a year on a CR2450 battery.
- **Perfect for Pranks**:
  - Hide the device in a friend's room to generate cricket chirps or beeps at night in random intervals.

---

## Required Components
- Microcontroller **ATtiny85**
- Piezo buzzer or small speaker
- Button (to change the mode)
- Power switch (3-pin toggle switch)
- Battery **CR2450 3V** or another battery with a suitable voltage
- 10kΩ resistor (for button pull-up, optionally for reducing buzzer volume)

---

## Wiring
1. **SPEAKER1**: Connect to pin **PB1** of the microcontroller.
2. **SPEAKER2**: Connect to pin **PB2** of the microcontroller.
3. **BUTTON_PIN**: Connect the button to pin **PB0**, adding a 10kΩ pull-up resistor to VCC.
4. **Power Switch**:
   - Middle pin to the battery’s +V.
   - One outer pin to the circuit’s VCC.
   - The other outer pin to GND.

---

## How Does It Work?
1. Once powered on, the device automatically generates a cricket chirp.
2. Use the button to switch between modes:
   - Mode 0: Realistic cricket chirp (intervals of 2-4 hours)
   - Mode 1: High-pitched beep (intervals of 2-4 hours)
   - Mode 2: Alternating cricket and beep sounds (intervals every 10 seconds – useful for testing the hidden device)
   - Mode 3: Series of random beeps (cricket or beep in intervals of 2-4 hours)
3. Between sound generations, the microcontroller enters sleep mode to minimize battery consumption.

---

## License
This project is licensed under the **MIT** license.
