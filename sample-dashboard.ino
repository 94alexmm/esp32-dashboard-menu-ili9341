/*
  Simple ILI9341 Menu and dashboard using the generic 4x3 membrane keypad
  By 94alexmm
*/

#include "Grid.h"
#include "Menu.h"
#include "Adafruit_ILI9341.h"
#include <Keypad.h>

const uint8_t ROWS = 4;
const uint8_t COLS = 3;
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
Grid grid = Grid(tft);
Menu menu = Menu(tft);

void setup() {

  tft.begin();
  Serial.begin(9600);
  tft.setRotation(1);
  showInfoMsg("Connecting to controller", 3000);
  grid.showGrid();
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


void handleHashKey() {
grid.hideGrid();
    menu.showMenu();

}

void updateGridValues() {
  if (!menu.isMenuOpen()) {
    if (refreshTime < currentTime) {
      grid.updateGridValue(1, String(random(140, 150)) + "V");
      grid.updateGridValue(2, String(random(47, 48)) + "V");
      grid.updateGridValue(3, String(random(1, 4)) + "A");
      grid.updateGridValue(4, String(random(1, 4)) + "A");
      refreshTime = currentTime + 1000;
    }
  }
}

void checkCurrentState(){
  if(!menu.isMenuOpen() && !grid.isGridOpen()){
    grid.showGrid();
  }
}

void loop() {
  currentTime = millis();
  updateGridValues();
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.println(key);
    if (menu.isMenuOpen()) {
      menu.handleKeyPress(key);
    } else {
      switch (key) {
        case '#':
          handleHashKey();
          break;
      }
    }

  }
  checkCurrentState();
}
