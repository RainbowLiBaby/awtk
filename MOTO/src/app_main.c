#include "awtk.h"

BEGIN_C_DECLS
#ifdef AWTK_WEB
#include "assets.inc"
#else /*AWTK_WEB*/
#include "../res/assets.inc"
#endif /*AWTK_WEB*/
END_C_DECLS

extern ret_t application_init(void);
//extern void* test_timer_queue(void *args);
extern ret_t application_exit(void);
//extern void* test_timer_queue(void *args);

#define APP_LCD_ORIENTATION LCD_ORIENTATION_180
#define APP_TYPE APP_SIMULATOR
#define APP_NAME "AwtkApplication"
#define APP_ENABLE_FAST_LCD_PORTRAIT

#include "awtk_main.inc"
