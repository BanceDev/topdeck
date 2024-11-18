#include "keymap.h"

#define DEBOUNCE_DELAY 5

int row_pins[ROWS] = {D2, D3, D4, D5, D6};
int col_pins[COLS] = {D7, D8, D9, D10, D11, D12, A0, A1, A2, A4, A5, A6};
bool key_states[ROWS][COLS];

unsigned long last_debounce_time[ROWS][COLS];

Adafruit_USBD_HID usb_hid;

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

void setup() {
  // Initialize row pins as outputs
  for (int i = 0; i < ROWS; i++) {
    pinMode(row_pins[i], OUTPUT);
    digitalWrite(row_pins[i], HIGH);
  }

  // Initialize column pins as inputs with pull-ups
  for (int i = 0; i < COLS; i++) {
    pinMode(col_pins[i], INPUT_PULLUP);
  }
  // begin the USB HID functionality
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
  TinyUSBDevice.begin();
}

void scan_matrix() {
  for (int r = 0; r < ROWS; r++) {
    // activate current row
    digitalWrite(row_pins[r], LOW);

    // read the state of each column
    for (int c = 0; c < COLS; c++) {
      // active low
      bool current_state = !digitalRead(col_pins[c]);
      unsigned long current_time = millis();

      // debouncing
      if (current_state != key_states[r][c]) {
        if (current_time - last_debounce_time[r][c] > DEBOUNCE_DELAY) {
          key_states[r][c] = current_state;
          last_debounce_time[r][c] = current_time;
        }
      }
    }

    // deactivate row
    digitalWrite(row_pins[r], HIGH);
  }
}

void loop() {

  /*scan_matrix();

  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      if (key_states[r][c]) {
        // Do something with the key press
      }
    }
  }*/

  // simulate a keyboard input
  if (usb_hid.ready()) {
    uint8_t keycode[6] = {0}; // keycode buffer
    keycode[0] = HID_KEY_A;
    usb_hid.keyboardReport(0, 0, keycode);
    delay(100);
    usb_hid.keyboardRelease(0);
    delay(1000);
}