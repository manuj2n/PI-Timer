const int outUSB =  2;      // Sortie commande mosfet usb raspberry
const int outShutdown = 4;    // ligue IO vers raspberry
const int outLed = 5;          // led debug
const int inRaspberry = 3;     //ligne IO venant du raspberry

String bufferString = "";         // a string to hold incoming data
boolean bufferFull = false;  // whether the string is complete
String strSecondes="";

long tempsVeille = 0;

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

  /* DEBUG */
  //strSecondes = "300";
  //bufferFull = true;
  //Serial.write("debut du programme\n");
}

void loop()
{
  delay(25); 
  if (bufferFull) {
    tempsVeille = 0L;
    for (int i=1; i<=(strSecondes.length() - 1); i++){
      int mult = strSecondes.charAt((strSecondes.length())-(i)) - 48;
      long tmp = (mult * pow(10.0,(i-1)));    
      tempsVeille += tmp;
      /* DEBUG */
      Serial.print(pow(10.0,(i-1)));
      Serial.print(" ");
      Serial.print(mult);
      Serial.print(" ");
      Serial.println(tmp);
    }
    Serial.print("strSecondes : ");
    Serial.println(strSecondes);
    tempsVeille -= 30; // rattrappe le shutdown
    Serial.print("DEBUT VEILLE : ");
    Serial.println(tempsVeille);
    delay(30000); // attend 30s le shutdown 
    digitalWrite(outLed,HIGH);
    digitalWrite(outUSB, LOW);
    unsigned long departMillis = millis();    
    unsigned long courantMillis = millis()+1;

    while (courantMillis - departMillis <= tempsVeille * 1000) {
      delay(25);
      courantMillis = millis();     
    }
    
    Serial.println("FIN VEILLE");

    digitalWrite(outUSB, HIGH);
    digitalWrite(outLed,LOW);  
 
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
            bufferString = "";
            bufferFull = true;
        } 
    }
}
