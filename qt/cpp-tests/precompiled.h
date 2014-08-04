#ifndef __PRECOMPILED_H__
#define __PRECOMPILED_H__

#if defined __cplusplus
    #include <string>
    #include <map>
    #include <vector>
    #include <set>
    #include <queue>
    #include <cstdlib>
    #include <cstdio>
    #include <cstdarg>

#else   /// not __cplusplus compiler
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdarg.h>

#endif  /// __cplusplus

///
#include <math.h>
#include <sys/time.h>
#include <sys/sockio.h>
#include <sys/socket.h>


#include "GL/glew.h"

#endif // __PRECOMPILED_H__
