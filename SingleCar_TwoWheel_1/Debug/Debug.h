/**
 * @file Debug.h
 * @brief Debug相关宏函数
 * @author ZheWana
 * @date 2021/9/30 003
 */

#ifndef DEBUG_H
#define DEBUG_H

#include "stdio.h"
#include "stdarg.h"
#include "usart.h"

#define DEBUG_UART_HANDLE huart2

#define LOG_LEVEL        0\
|LOG_LEVEL_ERROR          \
|LOG_LEVEL_WARN           \
|LOG_LEVEL_INFO           \
//|LOG_LEVEL_DEBUG          \
|LOG_LEVEL_DATA

int UART_printf(UART_HandleTypeDef *huart, const char *fmt, ...);

#define LOG_LEVEL_DATA      1<<0
#define LOG_LEVEL_DEBUG     1<<1
#define LOG_LEVEL_INFO      1<<2
#define LOG_LEVEL_WARN      1<<3
#define LOG_LEVEL_ERROR     1<<4
#define LOG_LEVEL_NONE      1<<5

#define ConditionLog(__level, __condition, __msg, ...) do{if(__condition){  \
switch(__level){                                                            \
case LOG_LEVEL_DATA:DataLog(__msg,##__VA_ARGS__);break;                     \
case LOG_LEVEL_DEBUG:DebugLog(__msg,##__VA_ARGS__);break;                   \
case LOG_LEVEL_INFO:InfoLog(__msg,##__VA_ARGS__);break;                     \
case LOG_LEVEL_WARN:WarnLog(__msg,##__VA_ARGS__);break;                     \
case LOG_LEVEL_ERROR:ErrorLog(__msg,##__VA_ARGS__);break;                   \
}}}while(0)

#define DataConLog(__condition, __datamsg, ...)   ConditionLog(LOG_LEVEL_DATA,__condition,__datamsg,##__VA_ARGS__)
#define DebugConLog(__condition, __dbgmsg, ...) ConditionLog(LOG_LEVEL_DEBUG,__condition,__dbgmsg,##__VA_ARGS__)
#define InfoConLog(__condition, __infomsg, ...) ConditionLog(LOG_LEVEL_INFO,__condition,__infomsg,##__VA_ARGS__)
#define WarnConLog(__condition, __warnmsg, ...) ConditionLog(LOG_LEVEL_WARN,__condition,__warnmsg,##__VA_ARGS__)
#define ErrorConLog(__condition, __errmsg, ...) ConditionLog(LOG_LEVEL_ERROR,__condition,__errmsg,##__VA_ARGS__)

/*******************************************************************************************************************************************/

#if (LOG_LEVEL& LOG_LEVEL_DATA)
#define DataLog(__datamsg, ...) UART_printf(&DEBUG_UART_HANDLE,__datamsg,##__VA_ARGS__)
#else
#define DataLog(...) do{}while(0)
#endif//(LOG_LEVEL & LOG_LEVEL_DATA)
#if (LOG_LEVEL& LOG_LEVEL_DEBUG)
#define DebugLog(__dbgmsg, ...) UART_printf(&DEBUG_UART_HANDLE,/*"[Debug]:"*/__dbgmsg"\n",##__VA_ARGS__)
#else
#define DebugLog(...) do{}while(0)
#endif//(LOG_LEVEL & LOG_LEVEL_DEBUG)
#if (LOG_LEVEL& LOG_LEVEL_INFO)
#define InfoLog(__infomsg, ...) UART_printf(&DEBUG_UART_HANDLE,"[INFO][%s]:"__infomsg"\n",__FUNCTION__,##__VA_ARGS__)
#else
#define InfoLog(...) do{}while(0)
#endif//(LOG_LEVEL & LOG_LEVEL_INFO)
#if (LOG_LEVEL& LOG_LEVEL_WARN)
#define WarnLog(__warnmsg, ...) UART_printf(&DEBUG_UART_HANDLE,"[WARNING]["__FILE__"]\\n""\n[Func:%s][Line:%d]:"__warnmsg"\n",__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
#define WarnLog(...) do{}while(0)
#endif//(LOG_LEVEL & LOG_LEVEL_WARN)
#if (LOG_LEVEL& LOG_LEVEL_ERROR)
#define ErrorLog(__errmsg, ...) UART_printf(&DEBUG_UART_HANDLE,"[ERROR]["__FILE__"]\\n""\n[Func:%s][Line:%d]:"__errmsg"\n",__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
#define ErrorLog(...) do{}while(0)
#endif//(LOG_LEVEL & LOG_LEVEL_ERROR)

#endif //DEBUG_H
