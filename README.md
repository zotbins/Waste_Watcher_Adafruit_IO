# Waste Watcher Adafruit IO

Waste Watcher is a IoT (Internet of Things) sensor module to help you keep track of your bin fullness and bin contents over time. This project is a continuation of [waste_watcher](https://github.com/zotbins/waste_watcher). This repo, in particular, uses [Adafruit IO](https://io.adafruit.com/), an off-the-shelf IoT platform that is simple to use and has a very supportive community. This project is aimed to be more user-friendly as it doesn't require you to setup/host your own server. Adafruit IO is also free to use  F O R E V E R ╰(*°▽°*)╯, according to their [website](https://io.adafruit.com/). 

## How this Project Started
I wanted a way to keep track of how much waste I was generating just to be more environmentally conscious. So I created this project as an automated way to help keep track of waste accumulation through fullness measurements while also taking pictures of the objects thrown away. 

To achieve this, I use the HC-SR04 ultrasonic sensor along with the ESP32-CAM. Doing this type of waste tracking is called a [waste audit](https://green.harvard.edu/tools-resources/how/how-host-waste-audit), which is a common practice used by universities to keep track of waste goals while also looking for opportunities increasing [waste diversion](https://en.wikipedia.org/wiki/Landfill_diversion) rates.
