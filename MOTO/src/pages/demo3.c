#include "awtk.h"
#include "../common/navigator.h"

extern ret_t on_velocity_value_changed(void* ctx, event_t* e);
extern ret_t progress_bar_animate_delta(widget_t* win, const char* name, int32_t delta);
extern ret_t demo2_update_timer(const timer_info_t* timer);

ret_t demo3_update_image(const timer_info_t* timer){
	widget_t* win = WIDGET(timer->ctx);
	widget_t* veer_left = widget_lookup(win, "veer_left", TRUE);
	widget_t* veer_right = widget_lookup(win, "veer_right", TRUE);

 widget_t* child;
	static uint8_t add = 1;

 if(add %2==0){
		widget_set_visible(veer_left,TRUE);
		widget_set_visible(veer_right,TRUE);
 }else{
	  widget_set_visible(veer_left,FALSE);
		widget_set_visible(veer_right,FALSE);
	}

 if(add %5==0){
  child = widget_lookup(win, "light_distance", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "light_vicinity", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "brake", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "ABS", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "engine", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "accumulator", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "TCS", TRUE);
  widget_set_visible(child,TRUE);
 }else{
  child = widget_lookup(win, "light_distance", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "light_vicinity", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "brake", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "ABS", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "engine", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "accumulator", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "TCS", TRUE);
  widget_set_visible(child,FALSE);
 }

	printf("demo1============>%d\r\n",add);
	add ++;
	return RET_REPEAT;
}

static ret_t on_next_click(void* ctx, event_t* e) {
  return navigator_replace("demo1");
}

static ret_t on_break_click(void* ctx, event_t* e) {
  return navigator_replace("demo2");
}
/**
 * 初始化窗口的子控件
 */
static ret_t visit_init_child(void* ctx, const void* iter) {
  widget_t* win = WIDGET(ctx);
  widget_t* widget = WIDGET(iter);
  const char* name = widget->name;

  // 初始化指定名称的控件（设置属性或注册事件），请保证控件名称在窗口上唯一
  if (name != NULL && *name != '\0') {
    if (tk_str_eq(name, "progress_circle")) {
      widget_on(widget, EVT_VALUE_CHANGED, on_velocity_value_changed, win);
    } else if (tk_str_eq(name, "next")) {
      widget_on(widget, EVT_CLICK, on_next_click, win);
    } else if (tk_str_eq(name, "break")) {
      widget_on(widget, EVT_CLICK, on_break_click, win);
    }

  }

  return RET_OK;
}

/**
 * 初始化窗口
 */
ret_t demo3_init(widget_t* win, void* ctx) {
  (void)ctx;
  return_value_if_fail(win != NULL, RET_BAD_PARAMS);

  widget_foreach(win, visit_init_child, win);

	widget_add_timer(win , demo2_update_timer, 1000);
	widget_add_timer(win , demo3_update_image, 500);
  return RET_OK;
}
