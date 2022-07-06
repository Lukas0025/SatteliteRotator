# Sattelite (antenna) Rotator (OpenSource and Open-source hardware) (HamLIB, Gpredict, satNOGS)

Simple arduino antenna rotator with two axis (AZ and EL). For AZ is used step motor and for EL is used linear motor. 
For controll is created PCB with Arduino nano, step motor driver and four relays. Controller uses easycomm and rotator can work with HAM Lib, Gpredict, SatNOGS, ...

## Rotator setup

### Azimuth

For azimuth rotator can by used simply one gear on rope and step motor like here https://www.thingiverse.com/thing:4246844 or can by used some old HAM rotator and replace rotary pin with step motor.

* Step motor and rope

* Step motor and old rotator


### Elevation

For elevation is used linear motor more info is here https://www.qsl.net/sv1bsx/actuator/actuator.html

![Elevation](https://www.qsl.net/sv1bsx/actuator/30_an.gif)
![Elevation_open](https://www.qsl.net/sv1bsx/actuator/70_an-1a.gif)

## Controller board

Board using Arduino Nano as microcontoler, A4988 for drive stepmotor, external 4 relay board for drive linear motor and same extesion ports. Board is designed in Kicad.

![Board](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/dps_design.png?sanitize=true)

### Parts:

* Arduino Nano (https://www.ebay.com/itm/384943705316?hash=item59a06ecce4:g:9NgAAOSwJPJipEhS)
* A4988 Driver (https://www.ebay.com/itm/221921771119?hash=item33ab917e6f:g:BpsAAOSwl9BWKyv1)
* 4 relay borad (4 channels) (https://www.ebay.com/itm/295078400027?hash=item44b40b101b:g:wqoAAOSwqW9ZXzWt)
* 2x 100uF capacitator
* prited PCB 

### Extension ports

* Generic ports - 3 digitals and 2 analog ports
* SPI port
* I2C port
* power port - 5V, 3V3 and GND
* 2 relays

## Connect with PC (HamLib, Gpredict, ...)

After code uploaded to arduino you need run rotctld for parse easycomm comunication.

```sh
sudo rotctld -m 202 -r /dev/ttyACM0 -s 9600 -T 127.0.0.1 -t 4533 -C timeout=5000 -C retry=0 -vvvvvvvv > pause
```

Connect to Gpredict using add rotator to Gpredict in Edit > Settings > Interface > Rotators > add new

![Add New](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/gpredictadd.png?sanitize=true)

then you can use rotator in Antenna controller

![Gpredict](https://raw.githubusercontent.com/Lukas0025/SatteliteRotator/master/IMGs/gpredict.png?sanitize=true)
