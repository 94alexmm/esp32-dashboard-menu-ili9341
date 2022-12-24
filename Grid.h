#include "Adafruit_ILI9341.h"

#ifndef Grid_h
#define Grid_h


class Grid {
  private:
    bool gridOpen =false;
    Adafruit_ILI9341 & tft;

    void drawTitle(String title) {
      //x,y,length,width, roundness, colour
      tft.fillRoundRect(0, 0, tft.width(), 30, 5, tft.color565(255, 255, 255));
      tft.setCursor(20, 3);
      tft.setTextColor(ILI9341_RED);
      tft.setTextSize(3);
      tft.println(title);
    }

  public:
    Grid(Adafruit_ILI9341 & tftIn) : tft(tftIn) {  }

    void showGrid() {
      gridOpen = true;
      tft.fillScreen(ILI9341_BLACK);
      addGridItem(1, "PV Voltage", "-");
      addGridItem(2, "Batt Voltage", "-");
      addGridItem(3, "Batt Current", "-");
      addGridItem(4, "PV Current", "-");
      drawTitle("Solar Status");
    }

    void hideGrid(){
      gridOpen=false;
    }

    bool isGridOpen() {
      return gridOpen;
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
};

#endif
