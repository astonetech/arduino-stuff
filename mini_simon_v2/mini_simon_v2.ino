/* vim: set ft=c : */

/**
 * Mini version of Simon (1978)
 *
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 *
 * Usage:
 *   Connect leds on 3, 6, 9
 *   Connect switches on 2, 4, 7
 *   Connect speaker on 12
 */

const int totalLeds = 3;
const int ledsPines[totalLeds] = {9, 6, 3};
const int buttonsPines[totalLeds] = {7, 4, 2};
const int speakerPin = 12;
const int ledsSounds[totalLeds] = {659, 1109, 1760}; // E, C#, A
const int gameOverSound = 330;
const int winSound = 2093;

const int seqLength = 5;
int seq[seqLength];
int seqIndex = 0;

boolean gameOver = false;


void setup() {

    for (int i = 0; i < totalLeds; i++) {
        pinMode(ledsPines[i], OUTPUT);
    }

    pinMode(speakerPin, OUTPUT);

    /* Gen and show sequence */
    randomSeed(analogRead(0));
    for (int i = 0; i < seqLength; i++) {
        seq[i] = random(totalLeds);
        digitalWrite(ledsPines[seq[i]], HIGH);
        tone(speakerPin, ledsSounds[seq[i]], 500);
        delay(500);
        digitalWrite(ledsPines[seq[i]], LOW);
        delay(500);
    }

}

void loop() {

    // Game
    if (!gameOver && seqIndex < seqLength) {
        for (int i = 0; i < totalLeds; i++) {
            int done = false;
            while(digitalRead(buttonsPines[i]) == HIGH) {
                if (!done) {
                    done = true;
                    digitalWrite(ledsPines[i], HIGH);
                    tone(speakerPin, ledsSounds[i]);
                    if (seq[seqIndex++] != i) {
                        gameOver = true;
                    }
                }
            }
            digitalWrite(ledsPines[i], LOW);
            noTone(speakerPin);
        }
    }

    // You Win
    if (!gameOver && seqIndex == seqLength) {
        delay(100);
        for (int i = 0; i < 10; i++) {
            digitalWriteAll(HIGH);
            tone(speakerPin, winSound, 50);
            delay(50);
            digitalWriteAll(LOW);
            delay(50);
        }
        while (true);
    }

    // Game Over
    if (gameOver) {
        delay(100);
        digitalWriteAll(HIGH);
        tone(speakerPin, gameOverSound, 750);
        delay(750);
        digitalWriteAll(LOW);
        while (true);
    }

    delay(50);

}

void digitalWriteAll(int value) {
    for (int i = 0; i < totalLeds; i++) {
        digitalWrite(ledsPines[i], value);
    }
}

