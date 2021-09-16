#ifndef __KP_LOG_H__
#define __KP_LOG_H__

#include <stdio.h>

extern int log_level, log_indent;

void kplog(int level, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
void kpfatal(const char *fmt, ...) __attribute__((noreturn,format(printf,1,2)));

#define kpdebug(fmt...)		kplog(LOG_DEBUG, fmt)
#define kpwarn(fmt...)		kplog(LOG_WARN, fmt)
#define kpinfo(fmt...)		kplog(LOG_INFO, fmt)

void _kpfatalerror(const char *filename, int line, const char *fmt, ...)
	__attribute__((noreturn,format(printf,3,4)));
void _kplogerror(const char *filename, int line, const char *fmt, ...)
	__attribute__((format(printf,3,4)));

#define kpfatalerror(fmt...)	_kpfatalerror(__FILE__, __LINE__, fmt)
#define kplogerror(fmt...)	_kplogerror(__FILE__, __LINE__, fmt)

#define kperr(fmt...)		do {		\
	int errsv = errno;			\
	errno = 0;				\
	_kplogerror(__FILE__, __LINE__, fmt);	\
	errno = errsv;				\
} while (0)

#define LOG_ERR		0
#define LOG_WARN	1
#define LOG_INFO	2
#define LOG_DEBUG	3
#define LOG_TRACE	5

#ifndef NODEBUG_LOG
/**
*  * 调试 日志
*   *	荣涛 
*    *	2021年9月15日
*     */
#include <stdarg.h>

#define err_log(fmt...) __debug_log(LOG_ERR, __func__, __LINE__, fmt)
#define warn_log(fmt...) __debug_log(LOG_WARN, __func__, __LINE__, fmt)
#define info_log(fmt...) __debug_log(LOG_INFO, __func__, __LINE__, fmt)
#define debug_log(fmt...) __debug_log(LOG_DEBUG, __func__, __LINE__, fmt)
#define trace_log(fmt...) __debug_log(LOG_TRACE, __func__, __LINE__, fmt)

//#define exit_log() exit(1)

static char __attribute__((unused)) *__level_color[] = {
    [LOG_ERR] = "\033[1;31m",
    [LOG_WARN] = "\033[1;32m",
    [LOG_INFO] = "\033[1;33m",
    [LOG_DEBUG] = "\033[1;34m",
    [LOG_TRACE] = "\033[1;35m",
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
#else
#define err_log(fmt...) do{}while(0)
#define warn_log(fmt...) do{}while(0)
#define info_log(fmt...) do{}while(0)
#define debug_log(fmt...) do{}while(0)
#define trace_log(fmt...) do{}while(0)
#define exit_log() do{}while(0)

#endif

#endif
