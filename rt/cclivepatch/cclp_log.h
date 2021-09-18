#ifndef __CCLIVEPATCH_LOG_H
#define __CCLIVEPATCH_LOG_H 1

#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

#define err_log(fmt...) __debug_log(LOG_ERR, __func__, __LINE__, fmt)
#define warn_log(fmt...) __debug_log(LOG_WARN, __func__, __LINE__, fmt)
#define info_log(fmt...) __debug_log(LOG_INFO, __func__, __LINE__, fmt)
#define debug_log(fmt...) __debug_log(LOG_DEBUG, __func__, __LINE__, fmt)

static char __attribute__((unused)) *__level_color[] = {
    [LOG_ERR] = "\033[1;31m",
    [LOG_WARNING] = "\033[1;32m",
    [LOG_INFO] = "\033[1;33m",
    [LOG_DEBUG] = "\033[1;34m",
};

static int __attribute__((unused)) __debug_log(int level, const char *func, int line, char *fmt, ...)
{
	int n = 0;
	va_list va;
	va_start(va, fmt);

	fprintf(stderr, "%s[%s:%d] ", __level_color[level], func, line);
	n += vfprintf(stderr, fmt, va );
	fprintf(stderr, "\033[m");

	va_end(va);
	return n;
}

//#define err_log(fmt...) do{}while(0)
//#define warn_log(fmt...) do{}while(0)
//#define info_log(fmt...) do{}while(0)
//#define debug_log(fmt...) do{}while(0)
//#define trace_log(fmt...) do{}while(0)



#endif //__CCLIVEPATCH_LOG_H