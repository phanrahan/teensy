#include <USBHost_t36.h>

const int interval_time = 90;

const byte Gr = 0;

const byte R1 = 1;
const byte R2 = 2;
const byte R3 = 3;

const byte G1 = 16;
const byte G2 = 32;
const byte G3 = 48;

const byte Y1 = 17;
const byte Y2 = 33;
const byte Y3 = 50;

const byte O1 = 18;
const byte O2 = 19;
const byte O3 = 34;
const byte O4 = 35;
const byte O5 = 51;

const byte YG = 49;

byte pattern[128];

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
MIDIDevice midi1(myusb);

elapsedMillis clock_count;
byte step_count;
byte round_count;

void setup() {
  for(int i = 0; i < 8; i ++) {
    pinMode(i, OUTPUT); 
    digitalWrite(i, LOW);
  }
  delay(1500);
  myusb.begin();
  midi1.setHandleNoteOn(myNoteOn);
  midi1.setHandleNoteOff(myNoteOff);
  midi1.setHandleControlChange(myControlChange);
}

void loop() {
  myusb.Task();
  midi1.read();

  if (clock_count >= interval_time) {
    doStep();
    clock_count = 0;
  }

}

void myNoteOn(byte channel, byte note, byte velocity) {
}

void myNoteOff(byte channel, byte note, byte velocity) {
}

void myControlChange(byte channel, byte control, byte value) {
}


void doStep() {
  int n = 0;
  setGrid(n % 8, n / 8, G1);
  n += 1;
  if( n >= 64 ) {
    n = 0; 
  }
}

void setGrid(byte x_value, byte y_value, byte colour) {
  midi1.sendNoteOn(x_value + (y_value * 16), colour, 1);
}
