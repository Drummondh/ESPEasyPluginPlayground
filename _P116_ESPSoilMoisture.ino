//#######################################################################################################
//#################################### Plugin 116: ESP Soil Sensor V1.1##################################
//#######################################################################################################

#define PLUGIN_116
#define PLUGIN_ID_116 116
#define PLUGIN_NAME_116 "ESP Capacitive Soil Moisture Sensor"
#define PLUGIN_VALUENAME1_116 "Moisture"

boolean Plugin_116_init = false;
byte pin_soil = 0;

boolean Plugin_116(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {
    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_116;
        Device[deviceCount].Type = DEVICE_TYPE_SINGLE;
        Device[deviceCount].VType = SENSOR_TYPE_SINGLE;
        Device[deviceCount].Ports = 0;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 1;
        Device[deviceCount].SendDataOption = true;
        Device[deviceCount].TimerOption = true;
        Device[deviceCount].GlobalSyncOption = true;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_116);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_116));
        break;
      }

    case PLUGIN_INIT:
      {
        Plugin_116_init = true;
		pin_soil = 5;  //MOD
        pinMode(pin_soil, OUTPUT); //Mod
        
        //digitalWrite(pin_soil, HIGH); //MOD
		 // analogWriteFreq(40000);
		 // analogWrite(5, 400); //MOD
        success = true;
        break;
      }


    case PLUGIN_READ:
      {
        pin_soil = 5; //Mod
       // noInterrupts(); //Mod
       // byte x;  //mod
        int value;
        value = 0;
       // for (x = 0; x < 25; x++)
        {
		   analogWrite(pin_soil, HIGH); //Mod
		  analogWriteFreq(40000);
		  analogWrite(pin_soil, 400); //MOD
          delayMicroseconds(500);
          value = analogRead(A0);
         // delayMicroseconds(40);
          //digitalWrite(pin_soil, HIGH); //Mod
          // delayMicroseconds(9680); //MOD
        }
        // interrupts();
        UserVar[event->BaseVarIndex] = (float)value;
        String log = F("Soil Moisture value: ");
        log += value;
        addLog(LOG_LEVEL_INFO, log);
        success = true;
		//analogWrite(pin_soil, LOW);
        break;
      }
  }
  return success;
}
