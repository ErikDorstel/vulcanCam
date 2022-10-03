# vulcanCam
ESP32 based IR Camera with WebUI
#### Features
* uses MLX90640 as Infrared Camera with standard I2C pins
* uses I2C address 0x33
* works as WLAN client and AP (AP chooser included)
* WebUI with IP address 192.168.4.1
* mDNS hostname heliometer.local
* DNS hostname heliometer.local (WLAN AP mode only)
* 32x24 pixels
* upscaling to 640x480 pixels with smooth css image rendering
* temperature display (right side of frame)
* shot mode (average 20 frames)
* shows temperature after click in frame
#### I2C bus
* SDA GPIO 21
* SCL GPIO 22
* address 0x33
#### PC (Firefox) Screenshot
![IMAGE ALT TEXT HERE](https://www.dorstel.de/github/vulcanCam_v1.2.png)
