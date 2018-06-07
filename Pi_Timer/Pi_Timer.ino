const int outUSB =  2;      // Sortie commande mosfet usb raspberry
const int outShutdown = 4;    // ligue IO vers raspberry
const int outLed = 5;          // led debug
const int inRaspberry = 3;     //ligne IO venant du raspberry

String bufferString = "";         // a string to hold incoming data
boolean bufferFull = false;  // whether the string is complete
String strSecondes="";

long tempsVeille = 300L;

void setup() {
  pinMode(outUSB, OUTPUT);
  digitalWrite(outUSB, LOW);
  pinMode(outShutdown, OUTPUT);
  digitalWrite(outShutdown, LOW);
  pinMode(outLed, OUTPUT);
  digitalWrite(outLed, LOW);
  pinMode(inRaspberry, INPUT);
  // initialize serial:
  Serial.begin(9600);
  bufferString.reserve(20);
  strSecondes.reserve(20);
  delay(1000);
  digitalWrite(outUSB, HIGH);

  strSecondes = "846";
  bufferFull = true;
  Serial.write("debut du programme\n");
}

void loop()
{
  if (bufferFull) {
    digitalWrite(outLed,HIGH);
    delay(1000);
    digitalWrite(outLed,LOW);  
    tempsVeille = 0;
    //for (int i=(strSecondes.length()); i >=1; i--){
    for (int i=1; i<=(strSecondes.length()); i++){
      float mult = strSecondes.charAt((strSecondes.length())-(i)) - 48;    
      tempsVeille += long(mult * pow(10.0,float(i-1)));
      Serial.print(i-1);
      Serial.print(" ");
      Serial.print(mult);
      Serial.print(" ");
      Serial.println(tempsVeille);
    }

    Serial.println(tempsVeille);
    
    bufferString = "";
    strSecondes = "";
    bufferFull = false;
  }
}

void serialEvent() {
    while (Serial.available()) {     
        char inChar = (char)Serial.read(); 
        bufferString += inChar;
        if ((bufferString.charAt(bufferString.length()-1) == '\n') && (bufferString.charAt(0) == 'S') && (bufferString.charAt(4) == ':')) {
            strSecondes = bufferString.substring(4,bufferString.length()-1);
            bufferFull = true;
        } 
    }
}
