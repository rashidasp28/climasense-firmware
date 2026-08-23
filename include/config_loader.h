#pragma once

#ifdef __has_include
  #if __has_include("climasense_config.h")
    #include "climasense_config.h"
  #else
    #include "config.example.h"
  #endif
#else
  #include "config.example.h"
#endif
