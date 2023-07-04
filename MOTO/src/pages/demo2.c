#include "awtk.h"
#include "../common/navigator.h"

extern ret_t on_velocity_value_changed(void* ctx, event_t* e);
extern ret_t progress_bar_animate_delta(widget_t* win, const char* name, int32_t delta);

static ret_t on_oil_click(void* ctx, event_t* e) {
  return navigator_replace("demo3");
}

static ret_t on_temp_click(void* ctx, event_t* e) {
  return navigator_replace("demo1");
}

/* 进度条动画*/
static ret_t progress_bar_animate_delta(widget_t* win, const char* name, int32_t delta) {

  widget_t* progress_circle = widget_lookup(win, name, TRUE);
  assert(progress_circle != NULL);

  int32_t value = (PROGRESS_CIRCLE(progress_circle)->value + delta);
  value = tk_min(120, value);
  value = tk_max(0, value);
  widget_animate_value_to(progress_circle, value, 1000);

  return RET_OK;
}

/**
 * 定时器事件（定时增加时间的值）
 */

static ret_t demo2_update_image(const timer_info_t* timer){
widget_t* win = WIDGET(timer->ctx);
 widget_t* veer_left = widget_lookup(win, "veer_left", TRUE);
 widget_t* veer_right = widget_lookup(win, "veer_right", TRUE);
 widget_t* progress_circle = widget_lookup(win, "progress_circle", TRUE);

 widget_t* child;

 static uint8_t add = 1;

 if(add %2==0){
  widget_set_visible(veer_left,TRUE);
  widget_set_visible(veer_right,TRUE);
  child = widget_lookup(win, "light_distance", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "light_vicinity", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "demo2_brake", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "demo2_abs", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "demo2_engine", TRUE);
  widget_set_visible(child,TRUE);
  child = widget_lookup(win, "accumulator", TRUE);
  widget_set_visible(child,TRUE);
 }else{
  widget_set_visible(veer_left,FALSE);
  widget_set_visible(veer_right,FALSE);
  child = widget_lookup(win, "light_distance", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "light_vicinity", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "demo2_brake", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "demo2_abs", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "demo2_engine", TRUE);
  widget_set_visible(child,FALSE);
  child = widget_lookup(win, "accumulator", TRUE);
  widget_set_visible(child,FALSE);
 }
	
	value_t v;
  int32_t val;
	static int add_num = 5;

  assert(progress_circle != NULL);
	
  value_set_int32(&v, widget_get_value(progress_circle));
  val = value_int32(&v);
  if (val >= 119 || val <=0) {
		add_num *= -1;
	}
  progress_bar_animate_delta(win, "progress_circle", add_num);	
	
	printf("demo1============>%d\r\n",add);
	add ++;
	return RET_REPEAT;
}

ret_t demo2_update_timer(const timer_info_t* timer){
	widget_t* win = WIDGET(timer->ctx);
	widget_t* mileage = widget_lookup(win, "data1", TRUE);
	widget_t* mileage2 = widget_lookup(win, "data2", TRUE);

	char tmpStr[10] = {0};
	static uint8_t add =0;
	static uint8_t m_num=-1;
	double count=0;

	count = 11.1 * add;
	tk_snprintf(tmpStr, sizeof(tmpStr), "%.1lfV",count);
	widget_set_text_utf8(mileage, tmpStr);

	count = 11111 * add;
	tk_snprintf(tmpStr, sizeof(tmpStr), "%.0lf",count);
	widget_set_text_utf8(mileage2, tmpStr);

	if(add ==9 || add ==0)
		m_num *= -1;
	if(m_num ==1)
		add ++;
	else
		add--;

	printf("demo2 img============>%d\r\n",add);
	return RET_REPEAT;
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
    } else if (tk_str_eq(name, "oil")) {
      widget_on(widget, EVT_CLICK, on_oil_click, win);
    } else if (tk_str_eq(name, "temp")) {
      widget_on(widget, EVT_CLICK, on_temp_click, win);
    }

  }

  return RET_OK;
}

/**
 * 初始化窗口
 */
ret_t demo2_init(widget_t* win, void* ctx) {
  (void)ctx;
  return_value_if_fail(win != NULL, RET_BAD_PARAMS);

  widget_foreach(win, visit_init_child, win);
	widget_add_timer(win , demo2_update_timer, 1000);
	
	widget_add_timer(win , demo2_update_image, 500);
  return RET_OK;
}
