#include "keymap.h"

#define DEBOUNCE_DELAY 5

class MatrixKeyboard {
private:
    int row_pins[ROWS] = {2, 3, 4, 5, 6};  // Adjust pin numbers as needed
    int col_pins[COLS] = {7, 8, 9, 10, 11, 12, A0, A1, A2, A3, A4, A5};
    bool key_states[ROWS][COLS] = {false};
    unsigned long last_debounce_time[ROWS][COLS] = {0};
    USBHIDKeyboard Keyboard;

public:
    void begin() {
        // Initialize row pins as outputs
        for (int i = 0; i < ROWS; i++) {
            pinMode(row_pins[i], OUTPUT);
            digitalWrite(row_pins[i], HIGH);
        }
        
        // Initialize column pins as inputs with pull-ups
        for (int i = 0; i < COLS; i++) {
            pinMode(col_pins[i], INPUT_PULLUP);
        }
        
        // Initialize USB HID Keyboard
        Keyboard.begin();
    }

    void scanMatrix() {
        for (int r = 0; r < ROWS; r++) {
            // Activate current row
            digitalWrite(row_pins[r], LOW);
            
            // Read the state of each column
            for (int c = 0; c < COLS; c++) {
                // Active low
                bool current_state = !digitalRead(col_pins[c]);
                unsigned long current_time = millis();
                
                // Debouncing
                if (current_state != key_states[r][c]) {
                    if (current_time - last_debounce_time[r][c] > DEBOUNCE_DELAY) {
                        key_states[r][c] = current_state;
                        last_debounce_time[r][c] = current_time;
                    }
                }
            }
            
            // Deactivate row
            digitalWrite(row_pins[r], HIGH);
        }
    }

    void handleState() {
        bool fn_layer = key_states[4][1];

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (fn_layer && fn_keymap[r][c] != 0) {
                    if (key_states[r][c]) {
                        Keyboard.pressRaw(fn_keymap[r][c]);
                    } else {
                        Keyboard.releaseRaw(fn_keymap[r][c]);
                    }
                } else {
                    if (key_states[r][c]) {
                        Keyboard.pressRaw(keymap[r][c]);
                    } else {
                        Keyboard.releaseRaw(keymap[r][c]);
                    }
                }
            }
        }
    }
};

MatrixKeyboard kb;

void setup() {
    kb.begin();
}

void loop() {
    kb.scanMatrix();
    kb.handleState();
}