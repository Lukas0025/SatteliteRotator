#include "easycomm.h"

void easycomm::parse(int TruAzim, int TruElev) {
  String ComputerRead = "";
  String Azimuth = "";
  String Elevation = "";

  while (this->serial_port->available()) {
    ComputerRead = this->serial_port->readString();
  }

  // looking for command <AZxxx.x>
  for (int i = 0; i <= ComputerRead.length(); i++) {
    if ((ComputerRead.charAt(i) == 'A') &&
        (ComputerRead.charAt(i + 1) == 'Z')) { // if read AZ
      for (int j = i + 2; j <= ComputerRead.length(); j++) {
        if (isDigit(ComputerRead.charAt(j))) { // if the character is number
          Azimuth = Azimuth + ComputerRead.charAt(j);
        } else {
          break;
        }
      }
    }
  }

  // looking for command <ELxxx.x>
  for (int i = 0; i <= ComputerRead.length(); i++) {
    if ((ComputerRead.charAt(i) == 'E') &&
        (ComputerRead.charAt(i + 1) == 'L')) { // if read EL
      if ((ComputerRead.charAt(i + 2)) == '-') {
        this->ComElev = 0; // if elevation negative
        break;
      }

      for (int j = i + 2; j <= ComputerRead.length(); j++) {
        if (isDigit(ComputerRead.charAt(j))) { // if the character is number
          Elevation = Elevation + ComputerRead.charAt(j);
        } else {
          break;
        }
      }
    }
  }

  // if <AZxx> received
  if (Azimuth != "") {
    this->ComAzim = Azimuth.toInt();
    this->ComAzim =
        this->ComAzim % 360; // keeping values between limits(for trackers with
                             // more than 360 deg. rotation)
  }

  // if <ELxx> received
  if (Elevation != "") {
    this->ComElev = Elevation.toInt();
    if (this->ComElev > 180) {
      this->ComElev = 0;
    }
    if (this->ComElev > 90) { // if received more than 90deg. (for trackers with
                              // 180deg. elevation)
      this->ComElev = 180 - this->ComElev; // keep below 90deg.
      this->ComAzim =
          (this->ComAzim + 180) % 360; // and rotate the antenna on the back
    }
  }

  // looking for <AZ EL> interogation for antenna position
  for (int i = 0; i <= ComputerRead.length(); i++) {
    if ((ComputerRead.charAt(i) == 'A') &&
        (ComputerRead.charAt(i + 1) == 'Z') &&
        (ComputerRead.charAt(i + 3) == 'E') &&
        (ComputerRead.charAt(i + 4) == 'L')) {
      this->serial_port->println("AZ" + String(TruAzim) + ".0 EL" +
                                 String(TruElev) + ".0");
    }
  }
}
