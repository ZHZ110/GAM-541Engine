#pragma once


 #ifdef DEBUG
 #define Info(x, text) { if(x) { WriteConsole::(text + __FILE__ + __LINE__); } }
 #else
#define Info(...) { }
#endif // DEBUG
