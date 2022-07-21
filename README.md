# Sattelite (antenna) Rotator (OpenSource and Open-source hardware) (HamLIB, Gpredict, satNOGS) (Linear motor EL)

Simple arduino antenna rotator with two axis (AZ and EL). For AZ is used step motor and for EL is used linear motor. 
For controll is created PCB with Arduino nano, step motor driver and four relays. Controller uses easycomm and rotator can work with HAM Lib, Gpredict, SatNOGS, ...

![Whole](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/whole.jpg?sanitize=true)

## Rotator setup

### Azimuth

For azimuth rotator can by used simply one gear on rope and step motor like here https://www.thingiverse.com/thing:4246844 or can by used some old HAM rotator and replace rotary pin with step motor.

* Step motor and rope

![StepMotor](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/stepmotoraz.jpg?sanitize=true)

* Step motor and old rotator

![OldRotator](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/rotatoraz.jpg?sanitize=true)


### Elevation

For elevation is used linear motor more info is here https://www.qsl.net/sv1bsx/actuator/actuator.html

![Elevation](https://www.qsl.net/sv1bsx/actuator/30_an.gif)
![Elevation_open](https://www.qsl.net/sv1bsx/actuator/70_an-1a.gif)

## Controller board

Board using Arduino Nano as microcontoler, A4988 for drive stepmotor, external 4 relay board for drive linear motor and same extesion ports. Board is designed in Kicad.

![Board](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/dps_design.png?sanitize=true)

### Parts:

* Arduino Nano (https://www.ebay.com/itm/384943705316)
* A4988 Driver (https://www.ebay.com/itm/221921771119)
* 4 relay borad (4 channels) (https://www.ebay.com/itm/295078400027)
* 2x 100uF capacitator (C1 is inverse pins)
* 2x 2 Pin 2.54mm Pitch PCB Screw Terminal Block (https://www.ebay.com/itm/264467271488)
* 2x 15pin 2.54mm Long Pin Female Header (https://www.ebay.com/itm/223478558792)
* 2x 8pin 2.54mm Long Pin Female Header (https://www.ebay.com/itm/223478558792)
* 1x 4pin 2.54mm Long Pin Male Header
* prited PCB 

### Extension ports

* Generic ports - 3 digitals and 2 analog ports
* SPI port
* I2C port
* power port - 5V, 3V3 and GND
* 2 relays

### Ports mapping

|  Boards          | Arduino Nano |
|------------------|--------------|
| Relay 1          |      D2      |
| Relay 2          |      D4      |
| Relay 3          |      D3      |
| Relay 4          |      D5      |
| Step Motor Step  |      D6      |
| Step Motor Dir   |      D7      |
| Generic 1        |      D8      |
| Generic 2        |      D9      |
| Generic 3        |      D10     |
| A0               |      A0      |
| A1               |      A1      |
| MI               |    MISO      |
| MO               |    MOSI      |
| SCK              |     SCK      |
| SDA (I2C)        |     SDA/A4   |
| SCL (I2C)        |     SCL/A5   |

## Connect with PC (HamLib, Gpredict, ...)

After code uploaded to arduino you need run rotctld for parse easycomm comunication.

```sh
sudo rotctld -m 202 -r /dev/ttyACM0 -s 9600 -T 127.0.0.1 -t 4533 -C timeout=5000 -C retry=0 -vvvvvvvv > pause
```

Connect to Gpredict using add rotator to Gpredict in Edit > Settings > Interface > Rotators > add new

![Add New](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/gpredictadd.png?sanitize=true)

then you can use rotator in Antenna controller

![Gpredict](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/gpredict.png?sanitize=true)
