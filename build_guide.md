# Waste Watcher Build Guide

The intent of this guide is to be clear and provide comprehensive instruction to help you build and setup your waste watcher. If you would like to suggest any improvements feel free to submit an issue or refer to the [Contributing](CONTRIBUTING.md) Guide.

## Materials
- [ ] PLA Filament
- [ ] ESP32-CAM
- [ ] HC-SR04
- [ ] Solid Core Wire
- [ ] Waste Watcher PCB
- [ ] 6 of 12mm M3 Screws
- [ ] 6 M3 nuts
- [ ] 1 of the 2 Pin Screw Terminal
- [ ] 2 of the 1 x 8 Female header pins
- [ ] Spare USB cable
- [ ] Heat Shrink

## Equipment Needed
- [ ] 3D printer (or 3D Printing Service)
- [ ] Soldering Iron
- [ ] Helpings Hands for Soldering
- [ ] Wire Stripper
- [ ] Computer
- [ ] FTDI Adapter and 4 Female to Female Adapter
- [ ] Jumper Cap

## 1 - 3D Print the Case
If you don't have a 3D printer, you can search up some local 3D printing services in your favorite search browser.

![](./imgs/assembly.png)

1. Before starting make sure that your bin is compatible with the case. If not, you may need to modify or create different handles. (please share them if you do! 🙂)
2. Refer to the settings below and print the following:
    1. 2 of the `sensor_mod_handle.stl`
    2. 1 of the `sensor_mod_bottom_assembly.stl`
    3. 1 of the `sensor_mod_top_assembly.stl`
3. Screw on the handles
    ![](./imgs/screw_handle_bar_reference2.jpg)

    ![](./imgs/screw_handle_bar_reference.jpg)


| Setting | Value |
| --------| ----- |
| Layer height (mm) | 0.1 |
| Shell thickness (mm) | 0.8 |
| Bottom/Top thickness (mm) | 1.5 |
| Fill Density (%) | 30 |
| Print speed (mm/s) | 50 |
| Support type | Everywhere |
| Platform adhesion type | None |

## 2 - Circuit
You can purchase the PCB from [OshPark](https://oshpark.com/) using this [link](https://oshpark.com/shared_projects/9fNFnSUL). Or if you prefer, you can refer to the schematic/KiCad files in the `pcb` folder and create your circuit on a prototyping board.

1. Let's recycle! ♻ Take your spare USB cable, cut the end, and expose the V+ (usually red) and GND (usually black)
    ![](./imgs/usb_power_cable.jpg)
2. Solder the components onto the PCB
    1. 2 Pin Screw Terminal
    2. 2 of the 1 x 8 Female header pins
3. Solder some wires onto the HC-SR04
4. Heat shrink to insulate
5. Solder the other ends of the wires into the PCB (use the labels to figure out which wire goes where)
3. Your circuit is good to go 👍
    ![](./imgs/hcsr04_pcb.jpg)

## 3 - Adafruit IO Setup
1. Create an Adafruit IO account
2. Take note of your Adafruit IO Username and Key
    ![](./imgs/adafruit_io_key.png)

    ![](./imgs/adaio_feed_key_take_note.png)
3. Create a Group
    ![](./imgs/adaio_new_group.png)
4. Create your feeds for
    1. Bin Fullness
    2. Waste Image
    ![](./imgs/adaio_new_feeds.png)
5. Create a [Dashboard](https://learn.adafruit.com/adafruit-io-basics-dashboards) for your feeds. Here's an example that I made.
    ![](./imgs/adaio_dashboard_example.png)

## 4 - Upload Code
Before getting started, make sure you satisfy these prerequisites below:
- [Visual Studio Code](https://code.visualstudio.com/)
- [Platform IO Extension Installed](https://platformio.org/install/ide?install=vscode)
- Repo Code Downloaded:
    - (Option 1) Download repo as zip and extract the contents
    - (Option 2) `git clone https://github.com/zotbins/Waste_Watcher_Adafruit_IO.git`

1. Open the subfolder `waste_watcher_adafruitIO` in Visual Studio Code
2. Create the file `config.h` in the `src` folder
    ![](./imgs/copy_config)
3. Copy the contents of `template-config` into your `config.h` file
4. Change the config settings for the following
    - `ssid` - your wifi name
    - `password` - this is your wifi password
    - `mqttClientID` - just a unique id. You can generate one with https://guidgenerator.com/
    - `mqttUsername` - this is your AdafruitIO username
    - `mqttPassword` - this your AdafruitIO key in the form of `<username>/feeds/<MQTT by Key>`. The key! Not your account password.
    - `mqttFullnessTopic` - the MQTT topic for the fullness feed you created
    - `mqttImageTopic` - the MQTT topic for the image feed you created
5. Measure the height of your bin and change `binHeight` value to reflect the height of your particular bin. That way the sensor module can calculate how full your bin is.
6. Change the other config settings as you see fit
7. Put a jumper cap on the ESP32-CAM `IO0` and `GND`
    ![](./imgs/ftdi_to_esp32_cam.jpg)
8. Plug in your FTDI Adapter to the ESP32-CAM as shown
    ![](./imgs/ftdi_circuit_design.png)
9. Plug in the FTDI Adapter into your computer
10. Click on the PlatformIO icon on the left side panel, then click **Upload and Monitor**. Wait for this to finish.
    ![](./imgs/platformio_upload_and_monitor.png)
12. While leaving the ESP32-CAM plugged into the computer, Unplug the Jumper Cap and hit the reset button
13. Wait for data to be sent in Adafruit IO
    1. Fullness data should be sent as `-1` (because there is no HC-SR04 connected yet)
    2. Image should be sent

For troubleshooting the ESP32-CAM checkout this guide: [ESP32-CAM Troubleshooting Guide](https://randomnerdtutorials.com/esp32-cam-troubleshooting-guide/)

## 5 - Monitor Waste and Create Actionable Solutions

1. Plug your ESP32-CAM into your PCB
2. Screw in the USB power wires as shown (do not mix up power and ground!)
3. Put the HC-SR04 in and then the ESP32CAM in.
3. Screw on the lid with the USB cable coming out of the rectangular hole on top

![](./imgs/waste_watcher.jpg)

Here are some actionable ideas from the README file:
> Besides just collecting data, here are some ideas that you can implement. Again the goal of this project is to help quantify and promote actionable solutions to reduce waste.
>
> - 🎯 Create a goal to reduce the rate at which you fill up a bin
> - 💻 Use the Adafruit IO Integrations (Zapier, IFTTT)
>    - Send a summary of weekly fullness rate
>    - Send alerts when bin is full
> - 🤖 Use machine learning to identify what items are thrown always
>    - identify frequently thrown away items then try to reduce that waste (eg. plastic straws are identified frequently in the waste stream, so we can ban the straw or give sustainable alternatives)
>    - identify which waste items are incorrectly thrown away

## Resources/Links
1. [Getting Started with VS Code and PlatformIO IDE for ESP32 and ESP8266 (Windows, Mac OS X, Linux Ubuntu)](https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/) - A guide to install Visual Studio Code and the PlatformIO Extension by Random Nerd Tutorials
2. [ESP32-CAM Video Streaming and Face Recognition with Arduino IDE](https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/) - Great introduction to the ESP32-CAM by Random Nerd Tutorials
3. [ESP32-CAM Troubleshooting Guide](https://randomnerdtutorials.com/esp32-cam-troubleshooting-guide/) - common problems fixed for the ESP32-CAM by Random Nerd Tutorials
