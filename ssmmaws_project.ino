
#include "esp32-hal-timer.h"

/*
#ifdef ESP32
  #pragma message "Compiling for ESP32"
#else
  #error "Not compiling for ESP32"
#endif


/* configurations */
#define DIRECT_ADC_VAL 0
#define AVERAGE_ADC_VAL 1

#define CALCULATION_MODE AVERAGE_ADC_VAL

/* Change these values based on your observations */
#define wetSoil 1600   // Define max value we consider soil 'wet'
#define drySoil 2400   // Define min value we consider soil 'dry'
#define openAir 2860   // Define min value we consider sensor out

// Define analog input
#define sensorPin A0
#define NUM_READINGS 500
#define ON 1
#define OFF 0
#define PUMP_EN_PIN 15

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile bool pumpStatus = false;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  pumpStatus = false;
  digitalWrite(PUMP_EN_PIN, HIGH);
  Serial.println("Status: Pump Off in timer");
  portEXIT_CRITICAL_ISR(&timerMux);
}

void EnableTimer(){

  uint32_t desiredFrequency = 1000000; // 1MHz frequency
  timer = timerBegin(desiredFrequency); 

  if (timer == NULL) {
    Serial.println("ERROR! Timer initialization failed");
  } 
   
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 50000, false, 0);
}

void StartTimer(int iSeconds){
  timerWrite(timer, 0);                      // clear timer
  timerAlarm(timer, 1000000 * iSeconds, false, 0);  // generate one shot
}

void Pump(bool bOnOff){

  switch(bOnOff){
    case ON:
      if(!pumpStatus){
        digitalWrite(PUMP_EN_PIN, LOW);  
        pumpStatus = true;
        StartTimer(5);
        Serial.println("Status: Pump On");
      }
      else
        Serial.println("Status: Pump already On");
      break;
    case OFF:
    default:
      if(pumpStatus){
        digitalWrite(PUMP_EN_PIN, HIGH);
        pumpStatus = false;
        Serial.println("Status: Pump Off");
      }
      else
        Serial.println("Status: Pump already off");
      break;
  }
}

// Read sensor data
int readSensorData(int pin) {
  return analogRead(pin);
}

// Calculate average of sensor readings
int calculateAverage(int* values, int numValues) {
  int sum = 0;
  for (int i = 0; i < numValues; i++) {
    sum += values[i];
  }
  return sum/numValues;
}

float getFilteredMean(int* data, int size, float threshold = 1.0) {
  float sum = 0;
  for (int i = 0; i < size; i++) sum += data[i];
  float mean = sum / size;

  float variance = 0;
  for (int i = 0; i < size; i++)
    variance += pow(data[i] - mean, 2);
  float stddev = sqrt(variance / size);

  // Filter and calculate mean again
  float filteredSum = 0;
  int filteredCount = 0;
  for (int i = 0; i < size; i++) {
    if (fabs(data[i] - mean) <= threshold * stddev) {
      filteredSum += data[i];
      filteredCount++;
    }
  }

  return (filteredCount > 0) ? (filteredSum / filteredCount) : mean;
}


void setup() {  
  Serial.begin(9600);
  pinMode(PUMP_EN_PIN, OUTPUT);    
  digitalWrite(PUMP_EN_PIN, HIGH);
  EnableTimer();
}



void loop() {

#ifdef CALCULATION_MODE
  
  int sensorValues[NUM_READINGS];
  int averageMoistureLevel;

  // Read and average sensor values
  for (int i = 0; i < NUM_READINGS; i++) {
    sensorValues[i] = readSensorData(sensorPin);
    delay(1);
  }
  averageMoistureLevel = getFilteredMean(sensorValues, NUM_READINGS);
  Serial.print("Average MoistureLevel: ");
  Serial.println(averageMoistureLevel);

// Determine soil moisture status
  if (averageMoistureLevel == 0){
      printf("Not powered\n");
      Pump(OFF);  
  }else if (averageMoistureLevel > openAir){
      printf("Moisture sensor Error!\n");
      Pump(OFF);  
  } else if (averageMoistureLevel >= drySoil) {
      printf("Soil is dry. Irrigation needed.\n");
      Pump(ON);
  } else if (averageMoistureLevel >= wetSoil && averageMoistureLevel < drySoil) {
      printf("Soil moisture is optimal.\n");
      Pump(OFF);
  } else {
      printf("Soil is wet. No irrigation needed.\n");
      Pump(OFF);
  }


#else  

  
  // Read the Analog Input and print it
  int moisture = analogRead(sensorPin);
  Serial.print("Analog output: ");
  Serial.println(moisture);
  
  // Determine status of our soil
  if (moisture < wetSoil) {
    Serial.println("Status: Soil is too wet");
    Pump(OFF);
  }else if (moisture >= wetSoil && moisture < drySoil) {
    Serial.println("Status: Soil moisture is perfect");
    Pump(OFF);
  }else if (moisture >= drySoil && moisture < openAir) {
    Serial.println("Status: Soil is too dry - time to water!");
    Pump(ON);
  }else {
    Serial.println("Moisture sensor error!");
    Pump(OFF);
  }

#endif  

  Serial.println();
  // Take a reading every 3 seconds
  delay(3000);
}
