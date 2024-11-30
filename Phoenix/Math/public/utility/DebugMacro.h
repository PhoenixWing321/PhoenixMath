// 只能在cpp里面添加，没有pragma once
#ifdef PHOENIX_DEBUG_INFO
#define PHOENIX_DEBUG(...) __VA_ARGS__;
#else
#define PHOENIX_DEBUG(...)
#endif
