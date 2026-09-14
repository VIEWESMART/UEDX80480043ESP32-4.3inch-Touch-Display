/**
 * @brief 应用功能开关（可在编译前修改，或通过 CMake -DAPP_ENABLE_COLOR_TEST=1 传入）
 *
 * APP_ENABLE_COLOR_TEST：GPIO0 切换 + 纯色/色条测试页。默认关闭，只跑导出 UI。
 */
#pragma once

#ifndef APP_ENABLE_COLOR_TEST
#define APP_ENABLE_COLOR_TEST 0
#endif
