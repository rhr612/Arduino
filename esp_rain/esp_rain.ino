#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"
#include <EEPROM.h>

const char *service_name = "RAT Tech";
const char *pop = "1234567";

// define the Device Names
char deviceName_1[] = "Light1";
char deviceName_2[] = "Light2";
char deviceName_3[] = "Fan";
char deviceName_4[] = "UNIVERSAL";

// define the GPIO connected with Relays and switches
static uint8_t RelayPin1 = 23;  //D23
static uint8_t RelayPin2 = 22;  //D22
static uint8_t RelayPin3 = 21;  //D21
static uint8_t RelayPin4 = 19;  //D19

static uint8_t SwitchPin1 = 13;  //D13
static uint8_t SwitchPin2 = 12;  //D12
static uint8_t SwitchPin3 = 14;  //D14
static uint8_t SwitchPin4 = 27;  //D27

static uint8_t wifiLed    = 2;   //D2
static uint8_t gpio_reset = 0;

// Switch State
bool SwitchState_1 = LOW;
bool SwitchState_2 = LOW;
bool SwitchState_3 = LOW;
bool SwitchState_4 = LOW;

bool relay_state1 = true;
bool relay_state2 = true;
bool relay_state3 = true;
bool relay_state4 = true;

//The framework provides some standard device types like switch, lightbulb, fan, temperature sensor.
static Switch my_switch1(deviceName_1, &RelayPin1);
static Switch my_switch2(deviceName_2, &RelayPin2);
static Switch my_switch3(deviceName_3, &RelayPin3);
static Switch my_switch4(deviceName_4, &RelayPin4);

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#else
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
        printQR(service_name, pop, "softap");
#endif        
        break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Serial.printf("\nConnected to Wi-Fi!\n");
        digitalWrite(wifiLed, true);
        break;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(device_name, deviceName_1) == 0) {
      
      Serial.printf("Lightbulb = %s\n", val.val.b? "true" : "false");
      
      if(strcmp(param_name, "Power") == 0) {
          Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        relay_state1 = val.val.b;
        digitalWrite(RelayPin1, !relay_state1);
        EEPROM.put(1, !relay_state1);
        EEPROM.commit();
      

        param->updateAndReport(val);
      }
      
    } else if(strcmp(device_name, deviceName_2) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        relay_state2 = val.val.b;
        digitalWrite(RelayPin2, !relay_state2);
        EEPROM.put(2, !relay_state2);
        EEPROM.commit();

        param->updateAndReport(val);
      }
  
    } else if(strcmp(device_name, deviceName_3) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        relay_state3 = val.val.b;
        digitalWrite(RelayPin3, !relay_state3);
        EEPROM.put(3, !relay_state3);
        EEPROM.commit();

        param->updateAndReport(val);
      }
  
    } else if(strcmp(device_name, deviceName_4) == 0) {
      
      Serial.printf("Switch value = %s\n", val.val.b? "true" : "false");

      if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        relay_state4 = val.val.b;
        digitalWrite(RelayPin4, !relay_state4);
        EEPROM.put(4, !relay_state4);
        EEPROM.commit();

        param->updateAndReport(val);
      }  
    }  
}

void manual_control()
{
  if (digitalRead(SwitchPin1) == LOW && SwitchState_1 == LOW) {
    relay_state1 = EEPROM.read(1);
    digitalWrite(RelayPin1, !relay_state1);
    
    
    SwitchState_1 = HIGH;
    my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, relay_state1);
    EEPROM.put(1, !relay_state1);
    EEPROM.put(11, SwitchState_1);
    EEPROM.commit();
    Serial.println("Switch-1 on");
    Serial.println(EEPROM.read(1));
  }
  if (digitalRead(SwitchPin1) == HIGH && SwitchState_1 == HIGH) {
    relay_state1 = EEPROM.read(1);
    digitalWrite(RelayPin1, !relay_state1);
    
    SwitchState_1 = LOW;
    my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state1);
    EEPROM.put(1, !relay_state1);
    EEPROM.put(11, SwitchState_1);
    EEPROM.commit();
    Serial.println("Switch-1 off");
    Serial.println(EEPROM.read(1));
  }
  if (digitalRead(SwitchPin2) == LOW && SwitchState_2 == LOW) {
    relay_state2 = EEPROM.read(2);
    digitalWrite(RelayPin2, !relay_state2);
    
    SwitchState_2 = HIGH;
    my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state2);
    EEPROM.put(2, !relay_state2);
    EEPROM.put(12, SwitchState_2);
    EEPROM.commit();
    Serial.println("Switch-2 on");
  }
  if (digitalRead(SwitchPin2) == HIGH && SwitchState_2 == HIGH) {
    relay_state2 = EEPROM.read(2);
    digitalWrite(RelayPin2, !relay_state2);
    
    SwitchState_2 = LOW;
    my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state2);
    EEPROM.put(2, !relay_state2);
    EEPROM.put(12, SwitchState_2);
    EEPROM.commit();
    Serial.println("Switch-2 off");
  }
  if (digitalRead(SwitchPin3) == LOW && SwitchState_3 == LOW) {
    relay_state3 = EEPROM.read(3);
    digitalWrite(RelayPin3, !relay_state3);
    
    SwitchState_3 = HIGH;
    my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state3);
    EEPROM.put(3, !relay_state3);
    EEPROM.put(13, SwitchState_3);
    EEPROM.commit();
    Serial.println("Switch-3 on");
  }
  if (digitalRead(SwitchPin3) == HIGH && SwitchState_3 == HIGH) {
    relay_state3 = EEPROM.read(3);
    digitalWrite(RelayPin3, !relay_state3);
    
    SwitchState_3 = LOW;
    my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state3);
    EEPROM.put(3, !relay_state3);
    EEPROM.put(13, SwitchState_3);
    EEPROM.commit();
    Serial.println("Switch-3 off");
  }
  if (digitalRead(SwitchPin4) == LOW && SwitchState_4 == LOW) {
    relay_state4 = EEPROM.read(4);
    digitalWrite(RelayPin4, !relay_state4);
    
    SwitchState_4 = HIGH;
    my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state4);
    EEPROM.put(4, !relay_state4);
    EEPROM.put(14, SwitchState_4);
    EEPROM.commit();
    Serial.println("Switch-4 on");
  }
  if (digitalRead(SwitchPin4) == HIGH && SwitchState_4 == HIGH) {
  relay_state4 = EEPROM.read(4);
    digitalWrite(RelayPin4, relay_state4);
    
    SwitchState_4 = LOW;
    my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME,relay_state4);
    EEPROM.put(4, !relay_state4);
    EEPROM.put(14, SwitchState_4);
    EEPROM.commit();
    Serial.println("Switch-4 off");
  }
}  

void setup()
{
    uint32_t chipId = 0;
    
    Serial.begin(115200);
    EEPROM.begin(500);
    relay_state1 = EEPROM.read(1);

    relay_state2 = EEPROM.read(2);
    relay_state3 = EEPROM.read(3);
    relay_state4 = EEPROM.read(4);
    SwitchState_1=EEPROM.read(11);
    SwitchState_2=EEPROM.read(12);
    SwitchState_3=EEPROM.read(13);
    SwitchState_4=EEPROM.read(14);
    my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, relay_state1);
    my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, relay_state2);
    my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, relay_state3);
    my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, relay_state4);
    
    
    // Set the Relays GPIOs as output mode
    pinMode(RelayPin1, OUTPUT);
    pinMode(RelayPin2, OUTPUT);
    pinMode(RelayPin3, OUTPUT);
    pinMode(RelayPin4, OUTPUT);  
    pinMode(wifiLed, OUTPUT);
    
    // Configure the input GPIOs
    pinMode(SwitchPin1, INPUT_PULLUP);
    pinMode(SwitchPin2, INPUT_PULLUP);
    pinMode(SwitchPin3, INPUT_PULLUP);
    pinMode(SwitchPin4, INPUT_PULLUP);
    pinMode(gpio_reset, INPUT);
    
    // Write to the GPIOs the default state on booting
    digitalWrite(RelayPin1, relay_state1);
    digitalWrite(RelayPin2, relay_state2);
    digitalWrite(RelayPin3, relay_state3);
    digitalWrite(RelayPin4, relay_state4);
    
    //EEPROM.put(1, relay_state);
    digitalWrite(wifiLed, LOW);

    Node my_node;    
    my_node = RMaker.initNode("RAT Tech");

    //Standard switch device
    my_switch1.addCb(write_callback);
    my_switch2.addCb(write_callback);
    my_switch3.addCb(write_callback);
    my_switch4.addCb(write_callback);

    //Add switch device to the node   
    my_node.addDevice(my_switch1);
    my_node.addDevice(my_switch2);
    my_node.addDevice(my_switch3);
    my_node.addDevice(my_switch4);

    //This is optional 
    RMaker.enableOTA(OTA_USING_PARAMS);
    //If you want to enable scheduling, set time zone for your region using setTimeZone(). 
    //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
    // RMaker.setTimeZone("Asia/Shanghai");
    // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
    RMaker.enableTZService();
    RMaker.enableSchedule();

    //Service Name
    for(int i=0; i<17; i=i+8) {
      chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }

    Serial.printf("\nChip ID:  %d Service Name: %s\n", chipId, service_name);

    Serial.printf("\nStarting ESP-RainMaker\n");
    RMaker.start();

    WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif

    my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
    my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
    my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
    my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, false);
}

void loop()
{
      Serial.println(EEPROM.read(1));
    // Read GPIO0 (external button to reset device
    if(digitalRead(gpio_reset) == LOW) { //Push button pressed
        Serial.printf("Reset Button Pressed!\n");
        // Key debounce handling
        delay(100);
        int startTime = millis();
        while(digitalRead(gpio_reset) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // If key pressed for more than 10secs, reset all
          Serial.printf("Reset to factory.\n");
          RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Reset Wi-Fi.\n");
          // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
          RMakerWiFiReset(2);
        }
    }
    delay(100);

    if (WiFi.status() != WL_CONNECTED)
    {
      //Serial.println("WiFi Not Connected");
      digitalWrite(wifiLed, false);
    }
    else
    {
      //Serial.println("WiFi Connected");
      digitalWrite(wifiLed, true);
    }

    manual_control();
}
