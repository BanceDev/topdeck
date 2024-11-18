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

    void sendKeyPress(int row, int col) {
        Keyboard.pressRaw(keymap[row][col]);
    }

    void sendKeyRelease(int row, int col) {
        Keyboard.releaseRaw(keymap[row][col]);
    }

    void simulateKeyPress() {
        uint8_t keycode[6] = {0};
        keycode[0] = HID_KEY_A;
        Keyboard.pressRaw(HID_KEY_A);
        delay(100);
        Keyboard.releaseRaw(HID_KEY_A);
        delay(1000);
    }
};

MatrixKeyboard kb;

void setup() {
    kb.begin();
}

void loop() {
    // keyboard.scanMatrix();

    kb.simulateKeyPress();
}