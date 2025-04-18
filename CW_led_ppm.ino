/*
Licencia GPL
Fuente: https://www.arduino.cc/education/morse-code-project/
*/

int ledPin = 13; //Arduino
//int ledPin = 35; //ESP32 OELD LoRa V3

//For letters
char* letters[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R con ñ "--.--",
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

//For Numbers
char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
"-....", "--...", "---..", "----."
};
//https://morsecw.com/alfabeto.html
int ppm = 10;
int dotDelay = 1200/ppm; 

void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Generador Código Morse. Utilice letras a-z y números 0-9");

}

void loop() {
  // put your main code here, to run repeatedly:
  char ch;
if (Serial.available())
  {
  ch = Serial.read(); // read a single letter if (ch >= 'a' && ch <= 'z')
  if (ch >= 'a' && ch <= 'z')
  {
    flashSequence(letters[ch - 'a']);
  }
  else if (ch >= 'A' && ch <= 'Z') {
    flashSequence(letters[ch - 'A']); }
  else if (ch >= '0' && ch <= '9') {
    flashSequence(numbers[ch - '0']); }
  else if (ch == ' ') {
    delay(dotDelay * 4);
    }
  }

}

void flashSequence(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
          flashDotOrDash(sequence[i]);
    i++; }
  delay(dotDelay * 3);
}


void flashDotOrDash(char dotOrDash) {
  digitalWrite(ledPin, HIGH); if (dotOrDash == '.')
  {
      delay(dotDelay);
    }
  else // must be a - 
  {
    delay(dotDelay * 3); }
  digitalWrite(ledPin, LOW); delay(dotDelay);
}