﻿/*****************************************************************************/
/********** THIS FILE IS GENERATED BY AWTK DESIGNER, DO NOT MODIFY ***********/
/*****************************************************************************/

#include <stdio.h>
#include "gtest/gtest.h"
#include "awtk.h"

GTEST_API_ int main(int argc, char **argv)
{
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);

  platform_prepare();
  system_info_init(APP_SIMULATOR, NULL, "./");
  tk_init_internal();
  tk_init_assets();

  RUN_ALL_TESTS();

  tk_deinit_internal();

  return 0;
}
