#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/power.h>

#define F_CPU 8000000UL

const uint8_t SPEAKER1 = 1;
const uint8_t SPEAKER2 = 2;
const uint8_t BUTTON_PIN = 0;

const unsigned long SHORT_INTERVAL = 10000UL; // 10 sekund
const unsigned long MIN_INTERVAL = 7200000UL; // 2 godziny
const unsigned long MAX_INTERVAL = 14400000UL; // 4 godziny

uint8_t soundMode = 0;
volatile bool buttonPressed = false;
bool alternateFlag = false;
unsigned long lastSoundTime = 0;
unsigned long currentInterval = MIN_INTERVAL;
volatile bool wdtFired = false;
volatile uint32_t wdtCount = 0; // Zmieniona na uint32_t dla długich interwałów

void resetAudioPins() {
    pinMode(SPEAKER1, INPUT);
    pinMode(SPEAKER2, INPUT);
    digitalWrite(SPEAKER1, LOW);
    digitalWrite(SPEAKER2, LOW);
}

void playChirp(uint16_t frequency, uint16_t duration) {
    pinMode(SPEAKER1, OUTPUT);
    pinMode(SPEAKER2, OUTPUT);

    uint32_t period = 1000000 / frequency;
    uint32_t pulse = period / 4;
    uint32_t startTime = millis();

    while (millis() - startTime < duration) {
        if (buttonPressed) break;
        digitalWrite(SPEAKER1, HIGH);
        digitalWrite(SPEAKER2, LOW);
        delayMicroseconds(pulse);
        digitalWrite(SPEAKER1, LOW);
        digitalWrite(SPEAKER2, HIGH);
        delayMicroseconds(pulse);
    }
    resetAudioPins();
}

void playCricket() {
    uint8_t chirpCount = random(3, 12);
    for (uint8_t i = 0; i < chirpCount; i++) {
        if (buttonPressed) break;
        playChirp(2200, 10);
        delay(random(20, 30));
    }
    delay(200);
    chirpCount = random(3, 12);
    for (uint8_t i = 0; i < chirpCount; i++) {
        if (buttonPressed) break;
        playChirp(2200, 10);
        delay(random(20, 30));
    }
    resetAudioPins();
}

void playToneC() {
    pinMode(SPEAKER1, OUTPUT);
    pinMode(SPEAKER2, OUTPUT);
    TCCR1 = 0x90 | (8 - 5);
    OCR1C = 354;
    delay(2990);
    TCCR1 = 0x90;
    resetAudioPins();
}

void playBeeps() {
    pinMode(SPEAKER1, OUTPUT);
    pinMode(SPEAKER2, OUTPUT);
    for(uint8_t i=0; i<3; i++) {
        TCCR1 = 0x90 | (8 - 5);
        OCR1C = 954;
        delay(190);
        TCCR1 = 0x90;

        TCCR1 = 0x90 | (8 - 5);
        OCR1C = 354;
        delay(190);
        TCCR1 = 0x90;
    }
    resetAudioPins();
}

void handleButton() {
    soundMode = (soundMode + 1) % 4;
    resetAudioPins();

    switch (soundMode) {
        case 0: playCricket(); break;
        case 1: playToneC(); break;
        case 2: 
            playCricket();
            delay(200);
            playToneC();
            alternateFlag = false;
            break;
        case 3: playBeeps(); break;
    }

    currentInterval = (soundMode == 2) ? SHORT_INTERVAL : random(MIN_INTERVAL, MAX_INTERVAL);
    lastSoundTime = millis();
    
    wdtCount = 0; // Resetujemy licznik WDT po zmianie trybu
}

void enterSleep() {
    resetAudioPins();

    MCUSR = 0;
    wdt_reset();

    WDTCR = (1<<WDCE)|(1<<WDE);
    WDTCR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0);

    ADCSRA &= ~(1<<ADEN);
    power_all_disable();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_bod_disable();

    GIMSK |= (1 << PCIE);
    PCMSK |= (1 << PCINT0);

    sei();
    
    sleep_cpu();
    
    sleep_disable();

    power_all_enable();
    
    GIMSK &= ~(1 << PCIE);

    PCMSK &= ~(1 << PCINT0);
}

ISR(PCINT0_vect) {
    if (!(PINB & (1 << BUTTON_PIN))) {
        buttonPressed = true;
    }
}

ISR(WDT_vect) {
    wdtFired = true;
    wdtCount++;
}

void setup() {
    pinMode(SPEAKER1, INPUT);
    pinMode(SPEAKER2, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    resetAudioPins();

    randomSeed(analogRead(3));
    
    ADCSRA &= ~(1<<ADEN);

    playCricket();

    lastSoundTime = millis();

    currentInterval = random(MIN_INTERVAL, MAX_INTERVAL);

    wdtCount=0; // Upewniamy się że licznik jest wyzerowany na starcie
}

void loop() {
    if (buttonPressed) {
        buttonPressed=false;
        handleButton();
    }

    if(wdtFired){
        wdtFired=false;

        if(soundMode==2 && wdtCount>= (SHORT_INTERVAL/8000)){
            if(alternateFlag)playToneC();
            else playCricket();
            alternateFlag=!alternateFlag;

            wdtCount=0;
        }else if(soundMode!=2 && wdtCount>= (currentInterval/8000)){
            switch(soundMode){
                case 0:playCricket();break;
                case 1:playToneC();break;
                case 3:random(2)?playCricket():playToneC();break;
            }

            wdtCount=0;

            currentInterval=random(MIN_INTERVAL,MAX_INTERVAL);
        }
    }

resetAudioPins();

enterSleep();
}
