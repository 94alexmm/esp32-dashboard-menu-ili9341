#include "Adafruit_ILI9341.h"

#ifndef Menu_h
#define Menu_h


class Menu {
  private:
    Adafruit_ILI9341 & tft;
    bool menuOpen = false;
    String rootOptions[4] = { "1 - Program User Settings", "2 - Configure Grid", "3 - View Firmware Info", "# - Exit Menu" };
    String optOneOptions[3] = { "1 - Float charge voltage", "2 - Bulk charge voltage", "* - Back" };

    void  drawOptions(String options[]) {
      tft.fillRoundRect(0, 40, tft.width(), 180, 0, tft.color565(0, 0, 0));
      tft.setTextSize(2);
      tft.setTextColor(ILI9341_WHITE);
      int startX = 0;
      int startY = 60;
      int arrayLength= sizeof(options);
      for (int i = 0; i < arrayLength; i++) {
        tft.setCursor(startX, startY);
        tft.println(options[i]);
        startY = startY + 30;
      }

    }

  public:
    Menu(Adafruit_ILI9341 & tftIn) : tft(tftIn) {  }

    void handleKeyPress(char key) {
      switch (key) {
        case '#':
          hideMenu();
          break;
        case '1':
          drawOptions(optOneOptions);
          break;
        case '*':
          drawOptions(rootOptions);
          break;
      }
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

    void showMenu() {
      tft.fillScreen(ILI9341_BLACK);
      menuOpen = true;
      showInfoMsg("Press # to exit menu", 1000);
      tft.fillScreen(ILI9341_BLACK);
      drawTitle("Menu");
      drawOptions(rootOptions);
    }


    void hideMenu() {
      menuOpen = false;

    }

    bool isMenuOpen() {
      return menuOpen;
    }

};

#endif
