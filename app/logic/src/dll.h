#ifdef DLL
  #define API __declspec(dllexport)
#else
  #define API __declspec(dllimport)
#endif