# Waste Watcher Adafruit IO

Waste Watcher is an IoT based sensor module to help keep track of waste data metrics with real-time bin fullness data and waste images. This is intended to help quantify and promote actionable solutions to reduce waste. This project is a continuation of [waste_watcher](https://github.com/zotbins/waste_watcher).

## Adafruit IO

This repo, in particular, uses [Adafruit IO](https://io.adafruit.com/), an off-the-shelf IoT platform. For now, Adafruit IO is a great addition to this project and helps in the following ways:
- 🤗 Helps makes the project more user-friendly (no need to setup your own server, ready to use APIs, Dashboard feature)
- 🆓 Free to use F O R E V E R ╰(*°▽°*)╯ (according to their [website](https://io.adafruit.com/))
- 🤝 Great community on Discord willing to help people out
- 🔒 Data is never [sold](https://www.adafruit.com/iotbor/)

## Features

- 🗑 Collect waste bin fullness telemetry
- 📷 Capture image of inside the waste bin
- 🔧 Fully customizable (adjust data collection rate, tweak case design for your needs, change camera settings, etc.)

## Getting Started

1. Follow the Build Guide
2. Create your Adafruit IO account
3. Upload your code to the ESP32 CAM
4. Start collecting your waste data

## Actionable Ideas for Your Waste Data

Besides just collecting data, here are some ideas that you can implement. Again the goal of this project is to help quantify and promote actionable solutions to reduce waste.

- 🎯 Create a goal to reduce the rate at which you fill up a bin
- 💻 Use the Adafruit IO Integrations (Zapier, IFTTT)
    - Send a summary of weekly fullness rate
    - Send alerts when bin is full
- 🤖 Use machine learning to identify what items are thrown always
    - identify frequently thrown away items then try to reduce that waste (eg. plastic straws are identified frequently in the waste stream, so we can ban the straw or give sustainable alternatives)
    - identify which waste items are incorrectly thrown away

## Contributors

## Credits/Acknowledgements
1. [ESP32Cam-MQTT by abish7643](https://github.com/abish7643/ESP32Cam-MQTT) - Great reference in how to send images through MQTT
2. [ESP32-CAM Projects by Random Nerd Tutorials](https://randomnerdtutorials.com/projects-esp32-cam/) - Quality background information on getting started with the ESP32-CAM


## How this Project Started

This project started at UCI in 2017 with a group of 4 undergraduates for a hackathon hosted by UCI TIPPERS. The aim of the project was to help create a tool to help with UCI's zero waste initiatives. Since then, the project is being shared to the open-source community through ZBCE and the ZotBins UCI undergraduate team continues with new members every year.

## Other
1. License
2. Contributing
3. Code of Conduct
