# Bilibili_Fans
Arduino环境下使用以TTGO-T-Display(ESP32)实现自动获取B站对应UID的关注等数据，在液晶屏上显示。
![ttgo](.\images\ttgo.jpg)

![01](.\images\begin.jpg)

![02](.\images\connecting.jpg)

![03](.\images\connected.jpg)

![04](.\images\fans.jpg)

### 开发流程

1. 安装[CP2102驱动](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)。

2. 访问[TTGO-T-Display](https://github.com/Xinyuan-LilyGO/TTGO-T-Display)仓库，获取开发使用的库和例程。

   1. 拷贝**TFT_eSPI** 到 **<C:\Users\你的用户名\Documents\Arduino\libraries>** 目录内
   2. 打开**ArduinoIDE** , 在文件，示例中找到**TFT_eSPI**, T-Display出厂测试程序位于**TFT_eSPI -> FactoryTest**,你也可以使用其他TFT_eSPI提供的示例程序

3. 访问[arduino-esp32](https://github.com/espressif/arduino-esp32)仓库，获取开发的的库以及设备库。

   1. 解压移动到Arduino安装目录/hardware/espressif/esp32

   2. 运行hardware/espressif/esp32/tools/get.exe

   3. 待命令运行结束，重启arduino

4. 在**Arduino IDE** 工具选项中 ， 开发板选择 **ESP32 Dev Module**,**在PSRAM选项中选择Disable**， **Flash Size 选项中选择4MB** ，其它保持默认
5. 选择对应的串行端口，如果不清楚请移除所有串行端口，之保留板子处于USB连接状态，选择那一个即可
6. 最后可点击上传即可，勾号旁边的向右箭头.

## 待更新

