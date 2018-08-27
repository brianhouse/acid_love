#include <toneAC.h>

// 1
const int RANGE_LOW = 60;
const int RANGE_HIGH = 400;
unsigned long DURATION = 55;    // in minutes
unsigned long LFO = 20;         // in seconds
float data[] = {0.30909,0.45455,0.89091,0.98182,0.12727,0.54545,0.49091,0.00000,0.96364,0.21818,0.45455,0.25455,0.18182,0.81818,1.00000,0.85455};
//
//// 2 (big)
//const int RANGE_LOW = 40;
//const int RANGE_HIGH = 90;
//unsigned long DURATION = 56;    // in minutes
//unsigned long LFO = 25;         // in seconds
//float data[] = {1.00000,0.50505,0.40404,0.00000,0.33333,0.12121,0.57576,0.20202,0.97980,0.45455,0.31313,0.13131,0.48485,0.50505,0.46465,0.94949};
//
//// 3
//const int RANGE_LOW = 60;
//const int RANGE_HIGH = 400;
//unsigned long DURATION = 57;    // in minutes
//unsigned long LFO = 30;         // in seconds
//float data[] = {0.67941,0.88529,1.00000,0.78824,0.46765,0.80588,0.00000,0.80000,0.27941,0.35588,0.73529,0.73824,0.16176,0.07941,0.09412,0.30882};
//
//// 4
//const int RANGE_LOW = 60;
//const int RANGE_HIGH = 400;
//unsigned long DURATION = 58;    // in minutes
//unsigned long LFO = 35;         // in seconds
//float data[] = {0.55623,0.61094,1.00000,0.94225,0.64438,0.89362,0.00000,0.82067,0.30699,0.36474,0.79635,0.78723,0.26444,0.06991,0.22188,0.34650};
//
//// 5
//const int RANGE_LOW = 60;
//const int RANGE_HIGH = 400;
//unsigned long DURATION = 59;    // in minutes
//unsigned long LFO = 40;         // in seconds
//float data[] = {0.34234,0.57207,0.77027,0.77928,1.00000,0.75225,0.00000,0.68468,0.45946,0.51802,0.84234,0.80631,0.32883,0.14414,0.16667,0.40090};
//
//// 6 (big)
//const int RANGE_LOW = 60;
//const int RANGE_HIGH = 40;
//unsigned long DURATION = 90;    // in minutes
//unsigned long LFO = 45;         // in seconds
//float data[] = {1.00000,0.62955,0.39334,0.29032,0.65245,0.18626,0.00000,0.13007,0.13840,0.15193,0.13528,0.14984,0.06035,0.01977,0.04683,0.14880};

int data_length = sizeof(data) / sizeof(data[0]);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world");
  Serial.print("Size of data: ");
  Serial.println(sizeof(data));
  Serial.print("DURATION: ");
  Serial.print(DURATION);
  Serial.println("min");
  DURATION *= 60000;
  LFO *= 1000;
}

void loop() {

  unsigned long m = millis();
  
  float pos = (m % DURATION) / float(DURATION);        // position 0-1 in data
  pos *= data_length;                                  // position in the array
  int i = pos;                                         // floor index of that position
  pos -= i;                                            // position between indexes
  
  int pitch_1 = (int)(data[i] * (RANGE_HIGH - RANGE_LOW) + RANGE_LOW);  
  int pitch_2 = (int)(data[(i + 1) % data_length] * (RANGE_HIGH - RANGE_LOW) + RANGE_LOW);
  float pitch = pitch_1 + ((pitch_2 - pitch_1) * pos);
  
  float duty = (m % LFO) / float(LFO);
  duty *= 60;
  duty += 20;
  if (duty > 50) duty = 50 - (duty - 50);
  
  toneAC(pitch, duty);

  Serial.print(i);
  Serial.print(" ");
  Serial.print(pos);
  Serial.print(" ");
  Serial.print(pitch_1);
  Serial.print(" ");
  Serial.print(pitch_2);
  Serial.print(" > ");
  Serial.print(pitch);
  Serial.print(" @ ");
  Serial.print(duty);  
  Serial.println();
      
}
