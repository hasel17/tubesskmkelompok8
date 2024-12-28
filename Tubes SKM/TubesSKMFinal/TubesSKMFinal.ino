#include <PID_v1.h>

// inisialisasi sensor kelembaban dan relay
const int sensorPin = A0;  // Pin analog untuk sensor kelembaban
const int relayPin = 8;  // Pin digital untuk mengontrol relay

// inisialisasi library PID
double Setpoint, Input, Output;
float Error;
double Kp = 2, Ki = 5, Kd = 1;


PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  pinMode(relayPin, OUTPUT);

  // Set nilai setpoint
  Setpoint = f550;

  // Batasi output PID agar tidak bertambah terus menerus
  myPID.SetOutputLimits(0, 255);

  // Set mode library PID ke otomatis
  myPID.SetMode(AUTOMATIC);
  Serial.begin(9600);
}

void loop() {
  // Memaca nilai sensor
  Input = analogRead(sensorPin);

  // Menghtung output PID
  myPID.Compute();

  // Mematikan pompa jika output PID lebih besar dari nilai tertentu (sesuaikan)
  Serial.print(Setpoint);
  Serial.print(" ");
  Serial.print(Input);
  Serial.print(" ");
  Serial.println(Output);
  if (Output > 200) {
    digitalWrite(relayPin, HIGH);  // Mematikan pompa
  } else {
    digitalWrite(relayPin, LOW);   // Mernghidupkan pompa
  }


  delay(1000);
}