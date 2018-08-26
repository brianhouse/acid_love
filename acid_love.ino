const int SPEAKER = A0;       // A0
const int DURATION = 10;      // in seconds
const int RANGE_LOW = 40;
const int RANGE_HIGH = 200;

float elapsed = 0.0;
int p_t = 0;
int p_s = 0;

int data[] = {
  0, 20, 100, 40, 50, 20, 10, 30, 40, 90
};

void setup() {
  pinMode(SPEAKER, OUTPUT);  
  Serial.begin(115200);
  Serial.println("Hello world");
  Serial.print("Size of data: ");
  Serial.println(sizeof(data));
}

void loop() {

  // update timers
  int t = millis();
  elapsed += t - p_t;
  if (elapsed >= DURATION * 1000) elapsed = 0;
  float pos = elapsed / (DURATION * 1000);
  int s = elapsed / 1000;

  int i = pos * (sizeof(data) / sizeof(data[0]));
  int pitch = (int)((data[i] / 100.0) * (RANGE_HIGH - RANGE_LOW)) + RANGE_LOW;

  tone(SPEAKER, pitch);
    
  if (s != p_s) {
    Serial.println(i);
    Serial.println(pitch);
    Serial.println("");
  }

  // update timers
  p_s = s;
  p_t = t;
  
}
