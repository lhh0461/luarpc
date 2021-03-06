#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <string>
#include <iostream>

#include "CLog.h"


#define MAX_TIME_STR_LEN  30
#define MAX_LOG_FILE_NAME 128 
#define MAX_LOG_BUF_LEN   10240

static char g_strLogBuf[MAX_LOG_BUF_LEN];
static LOG_LEVEL g_eLogSwitch = LOG_DEBUG;
static char g_LogFileName[MAX_LOG_FILE_NAME];
static FILE *g_fp = NULL;

static inline const char *_level_string(LOG_LEVEL level)
{
    switch (level)
    {
        case LOG_DEBUG:
            return "[debug]";
        case LOG_INFO:
            return "[info]";
        case LOG_WARNING:
            return "[warn]";
        case LOG_ERROR:
            return "[error]";
        case LOG_FATAL:
            return "[fatal]";
        default:
            break;
    }   
    return "";
}

void debug_printf(LOG_LEVEL level, const char *filename, int fileline, const char *format, ...)
{
    va_list args;
    time_t t;
    char strtime[MAX_TIME_STR_LEN];
    const char *strlevel;

    if ((g_eLogSwitch != LOG_ALL) && (level < g_eLogSwitch)) {
        return;
    }

    if (format == NULL) return;

    (void)time(&t);
    strftime(strtime, sizeof(strtime), "%Y-%m-%d %H:%M:%S", localtime(&t)); 

    strlevel = _level_string(level);

    va_start(args, format);
    (void)vsnprintf(g_strLogBuf, MAX_LOG_BUF_LEN, format, args);
    va_end(args);

    if (g_fp == NULL) {
        g_fp = fopen(g_LogFileName, "w");
        if (!g_fp) {
            perror("open log file error.");
            std::cout << std::string(g_LogFileName) << std::endl;
            return;
        }
    }

    fprintf(g_fp, "[%s] [%s:%d] %s %s\n", strtime, filename, fileline, strlevel, g_strLogBuf);
    fflush(g_fp);
    fprintf(stderr, "[%s] [%s:%d] %s %s\n", strtime, filename, fileline, strlevel, g_strLogBuf);
    fflush(stderr);
}

void SetLogSwitchLevel(LOG_LEVEL e_switch_level)
{
    g_eLogSwitch = e_switch_level;
}

void SetLogFileName(const char *file_name)
{
    sprintf(g_LogFileName, "%s",file_name);
}
