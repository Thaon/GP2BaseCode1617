#include "utils/time.h"

const std::string getLocalTimeStr(){
  time_t currentTime;
  struct tm * timeinfo;
  time(&currentTime);
  timeinfo = localtime ( &currentTime );
  char * asciitime=asctime(timeinfo);
  asciitime[strlen(asciitime)-1]=0;
  return std::string(asciitime);
}
