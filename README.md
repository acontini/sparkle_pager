# sparkle_pager
Ham pager development using a daughter board for TTGO T5 v. 2.0 / 2.2.

========================

## BOARD PINS
| Name                | T5 V2.0   | T5 V2.2   | T5 xxxx   |
| ------------------- | --------- | --------- | --------- |
| EPaper BUSY         | 4         | 4         | 4         |
| EPaper RST          | 16        | 12        | 12        |
| EPaper DC           | 17        | 19        | 13        |
| EPaper CS           | 5         | 5         | 2         |
| EPaper MOSI         | 23        | 23        | 15        |
| EPaper MISO         | N/A       | N/A       | N/A       |
| EPaper SCLK         | 18        | 18        | 14        |
| SDCard CS           | 13        | 13        | N/A       |
| SDCard MOSI         | 15        | 23        | N/A       |
| SDCard MISO         | 2         | 2         | N/A       |
| SDCard SCLK         | 14        | 18        | N/A       |
| Button 1            | 39        | 37        | 37        |
| Button 2            | N/A       | 38        | 38        |
| Button 3            | N/A       | 39        | 39        |
| DAC OUT             | N/A       | 25        | N/A       |
| A7139 GIO1          | 19        | TBC       | N/A       |
| A7139 GIO2          | 22        | TBC       | N/A       |
| A7139 SDIO          | 27        | TBC       | N/A       |
| A7139 SCK           | 25        | TBC       | N/A       |
| Motor               | 33        | TBC       | N/A       |
| Buzzer              | 32        | N/A       | N/A       |
| DS3231 SDA          | N/A       | N/A       | 21        |
| DS3231 SCL          | N/A       | N/A       | 22        |
| LORA MOSI           | N/A       | N/A       | 27        |
| LORA MISO           | N/A       | N/A       | 19        |
| LORA SCLK           | N/A       | N/A       | 5         |
| LORA CS             | N/A       | N/A       | 18        |
| LORA RST            | N/A       | N/A       | 23        |
| LORA DIO0           | N/A       | N/A       | 26        |
| SPRAM               | N/A       | supported | supported |
| Support EPaper Size | Full Size | Full Size | Full Size |


- 
## TTGO T5 Set Up

- For the first time, change the macro definition in `board_def.h` according to the corresponding layout and screen, and change the version to be used to 1.
```
#define TTGO_T5_1_2 0
#define TTGO_T5_2_0 1
#define TTGO_T5_2_1 0
#define TTGO_T5_2_2 0
#define TTGO_T5_2_3 0
#define TTGO_T5_2_4 0
```

- Check the screen size and color used. The default configuration screen list can be viewed in `board_def.h`.


## The following libraries are required to run the exmple provided with the TTGO T5.
- [Button2](https://github.com/lewisxhe/Button2)
- [GxEPD](https://github.com/lewisxhe/GxEPD)
- [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson/releases)

## Upload webserver resource
- Use Arduino ESP32 Sketch data Upload files,if you not install,[download ESP32FS-vX.zip](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases),Extract to <C:\Users\Your User Name\Documents\Arduino\tools>,Open Ardunio IDE,  Tools -> ESP32 Sketch data Upload -> Upload

## TTGO T5 Example
- [TTGO T5 Software](https://github.com/Xinyuan-LilyGO/T5-Ink-Screen-Series.git)

## Configure Badge Website

- **Configure the badge by entering http://ttgo.local or ip address in your browser.**

- **The display will be refreshed after submission**

## CAUTION:
- Currently only supports 100*100 size BMP format as image file for uploading

