#include <lvgl.h>
#include <Arduino.h>
#include <TFT_eSPI.h>

/*
  TO SUIT YOUR SETUP, DO:
    1. Open .pio/libdeps/[your_board]/TFT_eSPI/User_Setup.h
    2. Edit these lines:
        * Line 45 - change ili9341 to your display driver
        * Lines 212-217 - write your own pins display connected to
        * Line 230 - OPTIONAL! If you have touchscreen on your display. But, if you comment this line, this code will break!
    3. Go back to src/main.cpp (this file)
    4. Edit these lines:
        * Line 16-17 - your display resolution
        * Line 38 - OPTIONAL! If you have touch and you want to use it, you NEED to recalibrate it to get proper touch calData. Then, replace caldata from this sketch with yours.
*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];
void IRAM_ATTR onTimer();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void timinit();
void lv_example_list_1(void); // Example code

static lv_obj_t * list1;

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

void setup(){
  // lvgl init
  lv_init();
  timinit();
  // TFT_eSPI init
  tft.init();
  tft.setRotation(1);
  uint16_t calData[5] = {277, 3440, 435, 3445, 6};
  tft.setTouch(calData);
  // Initialize and register display driver
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
  // Initialize and register touch driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
  lv_example_list_1(); // Example code
}

void loop(){
  lv_timer_handler();       // woah, don't delete this line!
}

// Example code - you can delete this function if you wish.
void lv_example_list_1(void)
{
    /*Create a list*/
    list1 = lv_list_create(lv_scr_act());
    lv_obj_set_size(list1, 180, 220);
    lv_obj_center(list1);

    /*Add buttons to the list*/
    lv_obj_t * btn;
    lv_list_add_text(list1, "File");
    btn = lv_list_add_btn(list1, LV_SYMBOL_FILE, "New");
    btn = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Open");
    btn = lv_list_add_btn(list1, LV_SYMBOL_SAVE, "Save");
    btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Delete");
    btn = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Edit");
    lv_list_add_text(list1, "Connectivity");
    btn = lv_list_add_btn(list1, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    btn = lv_list_add_btn(list1, LV_SYMBOL_GPS, "Navigation");
    btn = lv_list_add_btn(list1, LV_SYMBOL_USB, "USB");
    btn = lv_list_add_btn(list1, LV_SYMBOL_BATTERY_FULL, "Battery");
    lv_list_add_text(list1, "Exit");
    btn = lv_list_add_btn(list1, LV_SYMBOL_OK, "Apply");
    btn = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Close");
}
// and don't delete these functions too!
void IRAM_ATTR onTimer()
{
  lv_tick_inc(10);
}

void timinit()
{

  static hw_timer_t *timer1 = NULL;
  timer1 = timerBegin(1, 80, true);
  timerAttachInterrupt(timer1, onTimer, true);
  timerAlarmWrite(timer1, 10000, true);
  timerAlarmEnable(timer1);
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  bool touched = tft.getTouch(&touchX, &touchY, 600);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    data->point.x = touchY; // it's not good, but it works
    data->point.y = touchX;
  }
}
