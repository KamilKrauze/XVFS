#ifndef PLATFORM_H
#define PLATFORM_H

#if defined(WIN32) || defined(_WIN32) || (defined(__WIN32) && !defined(__CYGWIN__)) || defined(_WIN64)

#define PLATFORM_WINDOWS 1
#define WINDOWS_LEAN_AND_MEAN 1

#elif defined(__unix__)

#define PLATFORM_UNIX 1

#else

#error "Current platform is not supported in this project"

#endif 

#endif // ! PLATFORM_H