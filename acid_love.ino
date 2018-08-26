const int SPEAKER = A0;
unsigned long DURATION = 1; // in minutes
const int RANGE_LOW = 40;
const int RANGE_HIGH = 100;

int data[] = {
  0, 20, 100, 40, 50, 20, 10, 30, 40, 90
};
int data_length = sizeof(data) / sizeof(data[0]);

void setup() {
  pinMode(SPEAKER, OUTPUT);  
  Serial.begin(115200);
  Serial.println("Hello world");
  Serial.print("Size of data: ");
  Serial.println(sizeof(data));
  Serial.print("DURATION: ");
  Serial.print(DURATION);
  Serial.println("min");
  DURATION *= 60000;
}

void loop() {

  float pos = (millis() % DURATION) / float(DURATION); // position 0-1 in data
  pos *= data_length;                                  // position in the array
  int i = pos;                                         // floor index of that position
  pos -= i;                                            // position between indexes
  
  int pitch_1 = (int)((data[i] / 100.0) * (RANGE_HIGH - RANGE_LOW)) + RANGE_LOW;  
  int pitch_2 = (int)((data[(i + 1) % data_length] / 100.0) * (RANGE_HIGH - RANGE_LOW)) + RANGE_LOW;
  int pitch = pitch_1 + ((pitch_2 - pitch_1) * pos);
//
//  Serial.print(i);
//  Serial.print(" ");
//  Serial.print(pos);
//  Serial.print(" ");
//  Serial.print(pitch_1);
//  Serial.print(" ");
//  Serial.print(pitch_2);
//  Serial.print(" > ");
//  Serial.print(pitch);
//  Serial.println();

  tone(SPEAKER, pitch);
      
}
