/*****************************
  Project:  Bilibili_Fans
  Author:   Staick
  Date:     2021.7.9
  Version:  V1.0
  Attention:
      1.本项目使用TTGO-T-Display作为开发板进行编程，如需使用其他开发板，需要对显示部分进行修改！！！
      2.具体使用时，需要修改ssid、password以及UID,可以直接搜索进行修改。
  
*****************************/
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <Ticker.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "bilibili.h"

HTTPClient http;
Ticker timer;
DynamicJsonBuffer jsonBuffer(256);                     //ArduinoJson V5
TFT_eSPI tft = TFT_eSPI(135,240);                      //设置显示的宽高240x135

const char *ssid = "WiFi名称";                         //路由器SSID
const char *password = "WiFi密码";                     //WIFI密码
String UID = "B站的UID";                               //B站的UID

long follower = 0;                                     //粉丝数
long *fans = &follower;
String followerUrl = "http://api.bilibili.com/x/relation/stat?vmid=" + UID;           //获取粉丝数的URL

void connectRouter(void);                             //连接到路由器
void getFollower(String url,long* fans);              //获取粉丝数
void displayInit(void);                               //显示初始化
void espDelay(int ms);
void displayBegin(void);
void displaySucess(void);
void displayFans(void);
void callBack(void);

void setup(){
  Serial.begin(115200);
  displayInit();
  displayBegin();
  connectRouter();
  displaySucess();
  getFollower(followerUrl,fans);
  displayFans();
  timer.attach(60,callBack);
}

void loop(){
  
}

void connectRouter(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi...");

  // 等待WiFi连接
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
   Serial.println("");
   Serial.println("WiFi connected!");
   Serial.print("IP address:");
   Serial.println(WiFi.localIP());
   delay(500);
}

void getFollower(String url,long* fans){
  http.begin(url);

  int httpCode = http.GET();
  Serial.printf("[HTTP] GET... code: %d\n", httpCode);

  if (httpCode == 200)
    {
        Serial.println("Get OK");
        String resBuff = http.getString();

        JsonObject &root = jsonBuffer.parseObject(resBuff);
        if (!root.success())
        {
          Serial.println("parseObject() failed");
          return;
        }

        *fans = root["data"]["follower"];
        Serial.print("Fans: ");
        Serial.println(follower);       
    }else{
        Serial.printf("[HTTP] GET... failed, error: %d\n", httpCode);
    }
    http.end();
}

void displayInit(void){
  tft.init();                             //tft初始化
  tft.setRotation(1);                     //设置屏幕方向
  tft.fillScreen(TFT_BLACK);              //清屏
  tft.setTextColor(TFT_SKYBLUE);          //设置文字颜色，文字
  tft.setCursor(0, 0);                    //设置光标的位置
  tft.setTextDatum(MC_DATUM);             //设置文字的位置为左上
  tft.setTextSize(1);                     //设置文字大小
  tft.setSwapBytes(true);
}

void espDelay(int ms){
  esp_sleep_enable_timer_wakeup(ms * 1000);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
  esp_light_sleep_start();
}

void displayBegin(){
  tft.setSwapBytes(true);
  tft.pushImage(0,0,240,135,background);
  tft.setTextSize(2);
  tft.drawString("V1.0",tft.width()/2,100);
  espDelay(2000);
  tft.setSwapBytes(true);
  tft.pushImage(0,0,240,135,background);
  tft.setTextSize(1);
  tft.drawString("Wait for WiFi",tft.width()/2,100);
}

void displaySucess(){
  tft.setSwapBytes(true);
  tft.pushImage(0,0,240,135,background);
  tft.drawString("WiFi connected",tft.width()/2,100);
  delay(1000);
}

void displayFans(){
  tft.setSwapBytes(true);
  tft.setTextSize(2);
  tft.pushImage(0,0,240,135,staick);
  tft.drawString(String(follower),tft.width()/2+55,tft.height()/2+2);
}

void callBack(void){
  getFollower(followerUrl,fans);
  displayFans();
}
