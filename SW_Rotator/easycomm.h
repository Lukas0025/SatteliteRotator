#pragma ones

#include <Arduino.h>

class easycomm {

  private:
    Stream *serial_port;

  public:
    int ComAzim;
    int ComElev;
    
    easycomm (Stream *serial_port) {
      this->serial_port = serial_port;
    }
    
    void parse(int TruAzim, int TruElev);
};
