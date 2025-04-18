/*
Licencia GPL
Fuente: https://www.arduino.cc/education/morse-code-project/

reformulado para funcionar sin conexión al PC.
Emite mensajes automaticos segun el botón presionado en pines 8 a 12.
Salida pin 13.

CONTINUAR
*/

int ledPin = 13; //Arduino
//int ledPin = 35; //ESP32 OELD LoRa V3

const int buttonPin12 = 12;  // lu1vz
const int buttonPin11 = 11;  // hola
const int buttonPin10 = 10;  // cw codigo morse
const int buttonPin9 = 9;  // instituto balseiro 70 años
const int buttonPin8 = 8;  // fil2025

int buttonState12;        // the current reading from the input pin
int lastButtonState12 = LOW;  // the previous reading from the input pin
unsigned long lastDebounceTime12 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay12 = 50;    // the debounce time; increase if the output flickers

int buttonState11;        // the current reading from the input pin
int lastButtonState11 = LOW;  // the previous reading from the input pin
unsigned long lastDebounceTime11 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay11 = 50;    // the debounce time; increase if the output flickers

int buttonState10;        // the current reading from the input pin
int lastButtonState10 = LOW;  // the previous reading from the input pin
unsigned long lastDebounceTime10 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay10 = 50;    // the debounce time; increase if the output flickers

int buttonState9;        // the current reading from the input pin
int lastButtonState9 = LOW;  // the previous reading from the input pin
unsigned long lastDebounceTime9 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay9 = 50;    // the debounce time; increase if the output flickers

int buttonState8;        // the current reading from the input pin
int lastButtonState8 = LOW;  // the previous reading from the input pin
unsigned long lastDebounceTime8 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay8 = 50;    // the debounce time; increase if the output flickers


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
  pinMode(buttonPin12, INPUT);   // lu1vz
  pinMode(buttonPin11, INPUT);   // hola
  pinMode(buttonPin10, INPUT);   // cw codigo morse
  pinMode(buttonPin9, INPUT);    // ib 70 años
  pinMode(buttonPin8, INPUT);    // fil2025

  // set initial LED state
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  Serial.println("Generador Código Morse con botones. Utilice letras a-z y números 0-9");

}

void loop() {
  // put your main code here, to run repeatedly:
  char ch='\0';
  int reading12 = digitalRead(buttonPin12);
  int reading11 = digitalRead(buttonPin11);
  int reading10 = digitalRead(buttonPin10);
  int reading9 = digitalRead(buttonPin9);
  int reading8 = digitalRead(buttonPin8);
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

  // BOTONES CON MENSAJES PREDETERMINADOS ################################################################

  //BOTÓN12 ################################################################
  // If the switch changed, due to noise or pressing:
  if (reading12 != lastButtonState12) {
    // reset the debouncing timer
    lastDebounceTime12 = millis();
    //Serial.println("SW CH");
  }

  if ((millis() - lastDebounceTime12) > debounceDelay12) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    
    // if the button state has changed:
    if (reading12 != buttonState12) {
      buttonState12 = reading12;
      // Serial.println("BTN CH");
      // ch = 'l';
      // Serial.print("STR: ");
      // Serial.println(ch);
      // only toggle the LED if the new button state is HIGH
      if (buttonState12 == HIGH) {
        ch = 'l';
        flashSequence(letters[ch - 'a']);
        Serial.print("l");
        ch = 'u';
        flashSequence(letters[ch - 'a']);
        Serial.print("u");
        ch = '1';
        flashSequence(letters[ch - 'a']);
        Serial.print("1");
        ch = 'v';
        flashSequence(letters[ch - 'a']);
        Serial.print("v");
        ch = 'z';
        flashSequence(letters[ch - 'a']);
        Serial.print("z");

      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState12 = reading12;

  //BOTÓN11 ################################################################
  if (reading11 != lastButtonState11) {
    lastDebounceTime11 = millis();
  }
  if ((millis() - lastDebounceTime11) > debounceDelay11) {
    if (reading11 != buttonState11) {
      buttonState11 = reading11;
      if (buttonState11 == HIGH) {
        ch = 'h';
        flashSequence(letters[ch - 'a']);
        Serial.print("h");
        ch = 'o';
        flashSequence(letters[ch - 'a']);
        Serial.print("o");
        ch = 'l';
        flashSequence(letters[ch - 'a']);
        Serial.print("l");
        ch = 'a';
        flashSequence(letters[ch - 'a']);
        Serial.print("a");
        ch = ' ';
        flashSequence(letters[ch - 'a']);
        Serial.print(" ");

      }
    }
  }
  lastButtonState11 = reading11;

  //BOTÓN10 ################################################################
  if (reading10 != lastButtonState10) {
    lastDebounceTime10 = millis();
  }
  if ((millis() - lastDebounceTime10) > debounceDelay10) {
    if (reading10 != buttonState10) {
      buttonState10 = reading10;
      if (buttonState10 == HIGH) {
        ch = 'c';
        flashSequence(letters[ch - 'a']);
        Serial.print("c");
        ch = 'w';
        flashSequence(letters[ch - 'a']);
        Serial.print("w");
        ch = ' ';
        flashSequence(letters[ch - 'a']);
        Serial.print(" ");
        ch = 'c';
        flashSequence(letters[ch - 'a']);
        Serial.print("c");
        ch = 'o';
        flashSequence(letters[ch - 'a']);
        Serial.print("o");
        ch = 'd';
        flashSequence(letters[ch - 'a']);
        Serial.print("d");
        ch = 'i';
        flashSequence(letters[ch - 'a']);
        Serial.print("i");
        ch = 'g';
        flashSequence(letters[ch - 'a']);
        Serial.print("g");
        ch = 'o';
        flashSequence(letters[ch - 'a']);
        Serial.print("o");
        ch = ' ';
        flashSequence(letters[ch - 'a']);
        Serial.print(" ");
        ch = 'm';
        flashSequence(letters[ch - 'a']);
        Serial.print("m");
        ch = 'o';
        flashSequence(letters[ch - 'a']);
        Serial.print("o");
        ch = 'r';
        flashSequence(letters[ch - 'a']);
        Serial.print("r");
        ch = 's';
        flashSequence(letters[ch - 'a']);
        Serial.print("s");
        ch = 'e';
        flashSequence(letters[ch - 'a']);
        Serial.print("e");
      }
    }
  }
  lastButtonState10 = reading10;

  //BOTÓN9 ################################################################
  if (reading9 != lastButtonState9) {
    lastDebounceTime9 = millis();
  }
  if ((millis() - lastDebounceTime9) > debounceDelay9) {
    if (reading9 != buttonState9) {
      buttonState9 = reading9;
      if (buttonState9 == HIGH) {
        ch = 'i';
        flashSequence(letters[ch - 'a']);
        Serial.print("I");
        ch = 'b';
        flashSequence(letters[ch - 'a']);
        Serial.print("B");
        ch = ' ';
        flashSequence(letters[ch - 'a']);
        Serial.print(" ");
        ch = '7';
        flashSequence(letters[ch - 'a']);
        Serial.print("7");
        ch = '0';
        flashSequence(letters[ch - 'a']);
        Serial.print("0");
        ch = ' ';
        flashSequence(letters[ch - 'a']);
        Serial.print(" ");
        ch = 'a';
        flashSequence(letters[ch - 'a']);
        Serial.print("a");
        ch = 'ñ';
        flashSequence(letters[ch - 'a']);
        Serial.print("ñ");
        ch = 'o';
        flashSequence(letters[ch - 'a']);
        Serial.print("o");
        ch = 's';
        flashSequence(letters[ch - 'a']);
        Serial.print("s");
      }
    }
  }
  lastButtonState9 = reading9;

  //BOTÓN8 ################################################################
  if (reading8 != lastButtonState8) {
    lastDebounceTime10 = millis();
  }
  if ((millis() - lastDebounceTime8) > debounceDelay8) {
    if (reading8 != buttonState8) {
      buttonState8 = reading8;
      if (buttonState8 == HIGH) {
        ch = 'f';
        flashSequence(letters[ch - 'a']);
        Serial.print("f");
        ch = 'i';
        flashSequence(letters[ch - 'a']);
        Serial.print("i");
        ch = 'l';
        flashSequence(letters[ch - 'a']);
        Serial.print("l");
        ch = '2';
        flashSequence(letters[ch - 'a']);
        Serial.print("2");
        ch = '0';
        flashSequence(letters[ch - 'a']);
        Serial.print("0");
        ch = '2';
        flashSequence(letters[ch - 'a']);
        Serial.print("2");
        ch = '5';
        flashSequence(letters[ch - 'a']);
        Serial.print("5");

      }
    }
  }
  lastButtonState8 = reading8;
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