/*
  Simple ILI9341 Menu and dashboard using the generic 4x3 membrane keypad
  By 94alexmm
*/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Keypad.h>

const uint8_t ROWS = 4;
const uint8_t COLS = 3;
bool isMenuOpen = false;
uint64_t currentTime = 0;
uint64_t refreshTime = 2000;

#define TFT_DC 2
#define TFT_CS 15
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6'},
  { '7', '8', '9' },
  { '*', '0', '#' }
};

uint8_t colPins[COLS] = { 26, 27, 21 };
uint8_t rowPins[ROWS] = { 12, 13, 14, 22 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {

  tft.begin();
  Serial.begin(9600);
  tft.setRotation(1);
  showInfoMsg("Connecting to controller", 3000);
  openDashGrid();
}

void openDashGrid() {
  tft.fillScreen(ILI9341_BLACK);
  addGridItem(1, "PV Voltage", "-");
  addGridItem(2, "Batt Voltage", "-");
  addGridItem(3, "Batt Current", "-");
  addGridItem(4, "PV Current", "-");
  drawTitle("Solar Status");
}

void addGridItem(int position, String title, String value) {
  int startX, startY;
  switch (position) {
    case 1:
      startX = 0;
      startY = 40;
      break;
    case 2:
      startX = 170;
      startY = 40;
      break;
    case 3:
      startX = 0;
      startY = 120;
      break;
    case 4:
      startX = 170;
      startY = 120;
      break;
  }

  tft.setCursor(startX, startY);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println(title);
  tft.setTextSize(5);
  tft.setCursor(startX + 10, startY + 30);
  tft.println(value);

}

void drawTitle(String title) {
  //x,y,length,width, roundness, colour
  tft.fillRoundRect(0, 0, tft.width(), 30, 5, tft.color565(255, 255, 255));
  tft.setCursor(20, 3);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println(title);
}

void showInfoMsg(String msg, int time) {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRoundRect(0, 0, tft.width(), 30, 5, tft.color565(255, 255, 255));
  tft.setCursor(20, 3);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println("Info");
  tft.setCursor(0, 100);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println(msg);
  delay(time);
}

void openMenu() {
  tft.fillScreen(ILI9341_BLACK);
  isMenuOpen = true;
  showInfoMsg("Press # to exit menu", 1000);
  tft.fillScreen(ILI9341_BLACK);
  drawTitle("Menu");
  drawOptions();
}

void  drawOptions() {
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(0, 60);
  tft.println("1 - Program User Settings");
  tft.setCursor(0, 90);
  tft.println("2 - Configure Grid");
  tft.setCursor(0, 120);
  tft.println("3 - View Firmware Info");
  tft.setCursor(0, 150);
  tft.println("# - Exit menu");
}

void closeMenu() {
  isMenuOpen = false;
  openDashGrid();
}

void handleHashKey() {
  if (!isMenuOpen) {
    openMenu();
  } else {
    closeMenu();
  }
}

void updateGridValues() {
  if (!isMenuOpen) {
    if (refreshTime < currentTime) {
      updateGridValue(1, String(random(140, 150)) + "V");
      updateGridValue(2, String(random(47, 48)) + "V");
      updateGridValue(3, String(random(1, 4)) + "A");
      updateGridValue(4, String(random(1, 4)) + "A");
      refreshTime = currentTime + 1000;
    }
  }
}

void updateGridValue(int position, String newValue) {
  int startX, startY;
  switch (position) {
    case 1:
      startX = 0;
      startY = 40;
      break;
    case 2:
      startX = 170;
      startY = 40;
      break;
    case 3:
      startX = 0;
      startY = 120;
      break;
    case 4:
      startX = 170;
      startY = 120;
      break;
  }
  //Draw blank over old value
  tft.fillRoundRect(startX, startY + 30, 150, 45, 5, tft.color565(0, 0, 0));
  tft.setCursor(startX, startY);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.setCursor(startX + 10, startY + 30);
  tft.println(newValue);
}

int64_t xx_time_get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
}

void loop() {
  currentTime = millis();
  updateGridValues();
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.println(key);
    switch (key) {
      case '#':
        handleHashKey();
        break;
    }
  }
}






