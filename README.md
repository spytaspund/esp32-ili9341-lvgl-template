<img src="https://img.shields.io/badge/espressif-E7352C?style=for-the-badge&logo=espressif&logoColor=white" /> <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" /> <img src="https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white" />
## Example code for esp32 running lvgl with ili9341 display + touch!

![chrome_ckHxQ8aCs3](https://github.com/user-attachments/assets/58ad0c5c-3840-488f-a939-1f2b276b1c4e)

Built for PlatformIO. Libraries used: 
* TFT_eSPI  v2.5.43
* LVGL v8.4.0
---
### Instructions to suit your setup (dublicated in main.cpp):
1. Open .pio/libdeps/[your_board]/TFT_eSPI/User_Setup.h
2. Edit these lines:
    * Line 45 - change ili9341 to your display driver
    * Lines 212-217 - write your own pins display connected to
    * Line 230 - OPTIONAL! If you have touchscreen on your display. But, if you comment this line, this code will break!
3. Go back to src/main.cpp (this file)
4. Edit these lines:
    * Line 16-17 - your display resolution
    * Line 38 - OPTIONAL! If you have touch and you want to use it, you NEED to recalibrate it to get proper touch calData. Then, replace caldata from this sketch with yours.

And that's all! Now you can upload your sketch to the board, and you're done!
