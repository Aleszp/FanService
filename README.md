# FanService
Simple program for keeping Raspberry Pi cool with PWM controlled fan connected tio GPIO pin 18 (hardware PWM pin).

libpigpio required (available under MIT license). Under Raspbian system just install:
sudo apt install libpigpio-dev

Compilation:
make

Installation (copies executable and config files to /opt/FanService and fan.service file to /etc/systemd/system/):
sudo make install

To start service:
sudo service fan start
sudo service fan enable

(c) Aleksander Szpakiewicz-Szatan, 2022
