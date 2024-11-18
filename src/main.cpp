#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

Adafruit_USBD_HID usb_hid;

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};

void setup() {
  // begin the USB HID functionality
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
  TinyUSBDevice.begin();
}

void loop() {
  // simulate a keyboard input
  if (usb_hid.ready()) {
    uint8_t keycode[6] = {0}; // keycode buffer
    keycode[0] = HID_KEY_A;
    usb_hid.keyboardReport(0, 0, keycode);
    delay(100);
    usb_hid.keyboardRelease(0);
    delay(1000);
}