const int LED[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
const int LED_THRESHOLD[10] = {28, 29, 30, 31, 32, 33, 34, 35, 36, 37};
#define CUT_OFF 10
#define VOLTAGE_IN A1
#define VOLTAGE_AVERAGES 20
#define CUT_OFF_THRESHOLD 35

//Voltage Averaging
int voltageValue[VOLTAGE_AVERAGES];
int voltageSig = 0;
int voltageValueCount = 0;
uint32_t voltageTotal = 0;
int prevVoltageSig = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  //setup LED and CUTT_OFF Pins
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(LED[4], OUTPUT);
  pinMode(LED[5], OUTPUT);
  pinMode(LED[6], OUTPUT);
  pinMode(LED[7], OUTPUT);
  pinMode(LED[8], OUTPUT);
  pinMode(CUT_OFF, OUTPUT);
  
  //turn on transistor
  digitalWrite(CUT_OFF, HIGH);

  //Blink each LED once then Flash all LEDs twice
  digitalWrite(LED[0], HIGH);
  delay(100);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], HIGH);
  delay(100);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], HIGH);
  delay(100);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], HIGH);
  delay(100);
  digitalWrite(LED[3], LOW);
  digitalWrite(LED[4], HIGH);
  delay(100);
  digitalWrite(LED[4], LOW);
  digitalWrite(LED[5], HIGH);
  delay(100);
  digitalWrite(LED[5], LOW);
  digitalWrite(LED[6], HIGH);
  delay(100);
  digitalWrite(LED[6], LOW);
  digitalWrite(LED[7], HIGH);
  delay(100);
  digitalWrite(LED[7], LOW);
  digitalWrite(LED[8], HIGH);
  delay(100);
  digitalWrite(LED[8], LOW);
  delay(250);

  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  digitalWrite(LED[4], HIGH);
  digitalWrite(LED[5], HIGH);
  digitalWrite(LED[6], HIGH);
  digitalWrite(LED[7], HIGH);
  digitalWrite(LED[8], HIGH);
  delay(100);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], LOW);
  digitalWrite(LED[4], LOW);
  digitalWrite(LED[5], LOW);
  digitalWrite(LED[6], LOW);
  digitalWrite(LED[7], LOW);
  digitalWrite(LED[8], LOW);
  delay(100);

  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  digitalWrite(LED[4], HIGH);
  digitalWrite(LED[5], HIGH);
  digitalWrite(LED[6], HIGH);
  digitalWrite(LED[7], HIGH);
  digitalWrite(LED[8], HIGH);
  delay(100);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], LOW);
  digitalWrite(LED[4], LOW);
  digitalWrite(LED[5], LOW);
  digitalWrite(LED[6], LOW);
  digitalWrite(LED[7], LOW);
  digitalWrite(LED[8], LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (voltageValueCount < VOLTAGE_AVERAGES) {

    voltageTotal -= voltageValue[voltageValueCount];
    voltageValue[voltageValueCount] = analogRead(VOLTAGE_IN);
    voltageTotal += voltageValue[voltageValueCount];
    voltageValueCount++;
    voltageSig = voltageTotal / VOLTAGE_AVERAGES;
  }


  else {
    voltageValueCount = 0;
  }

  if (abs(voltageSig - prevVoltageSig) >= .1) {
    for (int i = 0; i < 10; i++) {
      if (voltageSig < LED_THRESHOLD[i]) {
        break;
      }
      else {
        digitalWrite(LED[(i - 1)], HIGH);
      }
    }
  }
  else{
    prevVoltageSig = voltageSig;
  }
  
  if(voltageSig > CUT_OFF_THRESHOLD){
    digitalWrite(CUT_OFF, LOW);
  }

}
