#ifdef DLL
  #ifdef __unix__
    #define API
  #else
    #define API __declspec(dllexport)
  #endif
#else
  #ifdef __unix__
    #define API
  #else
    #define API __declspec(dllimport)
  #endif
#endif
