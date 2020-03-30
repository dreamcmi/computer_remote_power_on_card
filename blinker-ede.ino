
/* 电脑远程开机卡V1.0
 * 2020.2.11创建项目
 * 目前版本Beta V1.0.4
 * 最后修改时间2020.2.18
 * 作者：梦程MI  Bilibili uid：88809897
 * 使用平台： Blinker Aruino
 * ESP8266开发板 2.6.3
 * pwr信号-D5-GPIO14
 * rst信号-D7-GPIO13
 * 本项目开源 遵循GPL2.0规则。
 * 未经 梦程MI 许可，禁止用作商业用途。
 * 本项目软硬件均由 梦程MI 独立制作，请尊重版权。
 * 本项目适合有一定基础的开发者编译制作，没有arduino基础的请学习完arduino后在进行实践操作。
 */
 
//引入blinker
#define BLINKER_MIOT_LIGHT  //blinker-light小爱（我目前知道只有这个可以设置多开关）
#define BLINKER_WIFI
#define BLINKER_ESP_SMARTCONFIG

#include <Blinker.h>

//---------------定义初始信息--------------
char auth[] = "259675414f88"; //授权码
//---------------------------------------


//定义针脚
const int pwr = D5;       //D5-PWR信号
const int rst = D7;       //D7-RST信号


//---------------建立开关-----------------
BlinkerButton Button0("PWR");
BlinkerButton Button1("RST");

//---------------Smartconfig---------------
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}


//---------------按钮PWR----------------------
void button0_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  digitalWrite(pwr, HIGH);
  delay(200);
  digitalWrite(pwr, LOW);
  Button0.print("tap");
}


//--------------按钮RST----------------------
void button1_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  digitalWrite(rst, HIGH);
  delay(200);
  digitalWrite(rst, LOW);
  Button1.print("tap");
}

//------------引入小爱多设置----------------------
void miotMode(uint8_t mode)
{
    BLINKER_LOG("need set mode: ", mode);

    if (mode == BLINKER_CMD_MIOT_DAY) {      //PWR按键
    
            Button0.print("tap");
            digitalWrite(pwr, HIGH);
            delay(200);
            digitalWrite(pwr, LOW);
       
    }
    else if (mode == BLINKER_CMD_MIOT_NIGHT) { //RST按键
            Button1.print("tap");
            digitalWrite(rst, HIGH);
            delay(200);
            digitalWrite(rst, LOW);
    }
    BlinkerMIOT.mode(mode);
    BlinkerMIOT.print();
}
//----------------------------------------
void setup() {
  
    //开启blinker 若不出错此命令可以不执行
    Blinker.deleteTimer();
    // 初始化串口
    Serial.begin(115200);
    //开启DEBUG（监视器可以查看）
    BLINKER_DEBUG.stream(Serial);
   
    // 初始化IO
    pinMode(pwr, OUTPUT);
    pinMode(rst, OUTPUT);
    
    //默认写入低电平
    digitalWrite(pwr, LOW);
    digitalWrite(rst, LOW);
    
    // 初始化blinker
    Blinker.begin(auth);
    
    //初始化smartconfig
    Blinker.attachData(dataRead);
    
    //回调小爱
    BlinkerMIOT.attachMode(miotMode);
    
    //注册回调函数
    Button0.attach(button0_callback);
    Button1.attach(button1_callback);

}

void loop() {
    Blinker.run();  //程序开始
}
