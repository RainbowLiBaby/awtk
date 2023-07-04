#include "awtk.h"
#include "../common/navigator.h"

/**
 * 初始化窗口的子控件
 */
static ret_t visit_init_child(void* ctx, const void* iter) {
  widget_t* win = WIDGET(ctx);
  widget_t* widget = WIDGET(iter);
  const char* name = widget->name;

  // 初始化指定名称的控件（设置属性或注册事件），请保证控件名称在窗口上唯一
  if (name != NULL && *name != '\0') {

  }

  return RET_OK;
}

static ret_t update_tmer(const timer_info_t* timer){
	widget_t* win = WIDGET(timer->ctx);
	widget_t* mileage = widget_lookup(win, "mileage", TRUE);
	widget_t* mileage2 = widget_lookup(win, "mileage2", TRUE);

	char tmpStr[10] = {0};
	static uint8_t add =0;
	static uint8_t m_num=-1;
	double count=0;

	count = 11111.1 * add;
	tk_snprintf(tmpStr, sizeof(tmpStr), "%.1lf",count);
	widget_set_text_utf8(mileage, tmpStr);

	count = 111.1 * add;
	tk_snprintf(tmpStr, sizeof(tmpStr), "%.1lf",count);
	widget_set_text_utf8(mileage2, tmpStr);

	if(add ==9 || add ==0)
		m_num *= -1;
	if(m_num ==1)
		add ++;
	else
		add--;

	printf("demo1 img============>%d\r\n",add);
	return RET_REPEAT;
}

/**
 * 初始化窗口
 */
ret_t demo_init(widget_t* win, void* ctx) {
  (void)ctx;
  return_value_if_fail(win != NULL, RET_BAD_PARAMS);

  widget_foreach(win, visit_init_child, win);

	widget_add_timer(win , update_tmer, 1000);

  return RET_OK;
}
