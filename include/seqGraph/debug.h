#ifndef __DEBUGGING__
#define __DEBUGGING__
#include <stdio.h>

/// Logging
#ifdef DEBUG
#define LOG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif

#ifdef DEBUG
#define LOGV2(NAME, P) fprintf(stderr, "%s=(%f, %f)\n", NAME, P[0], P[1])
#else
#define LOGV2(NAME, P)
#endif

#ifdef DEBUG
#define LOGV3(NAME, P)                                                         \
  fprintf(stderr, "%s=(%f, %f, %f)\n", NAME, P[0], P[1], P[2])
#else
#define LOGV3(NAME, P)
#endif

#ifdef DEBUG
#define LOGV4(NAME, P)                                                         \
  fprintf(stderr, "%s=(%f, %f, %f, %f)\n", NAME, P[0], P[1], P[2], P[3])
#else
#define LOGV4(NAME, P)
#endif

#endif
