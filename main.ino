
const int adress[] = {0, 1, 2, 3};
const int multiplexer = A0;
int multiplexerStates[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int s1[] = {314, 327};      //values determined by calculations
int s2[] = {163, 173};      //see Input Values.xlsx
int s3[] = {90, 97};        //for circuit see Circuit.png
int s4[] = {46, 52};        //here
int s12[] = {397, 411};     //R0 = 1 kΩ
int s13[] = {359, 372};     //R1 = 2,2 kΩ
int s14[] = {337, 350};     //R2 = 5,1 kΩ
int s23[] = {229, 240};     //R3 = 10 kΩ
int s24[] = {197, 208};     //R4 = 20 kΩ
int s34[] = {130, 138};     
int s123[] = {432, 446};    
int s124[] = {415, 429};
int s134[] = {379, 393};
int s234[] = {258, 269};
int s1234[] = {448, 462};



void updateMultiplexer()
{
  for(int i=0; i<16; i++)
  {
    digitalWrite(adress[0], HIGH && (i & B00000001));
    digitalWrite(adress[1], HIGH && (i & B00000010));
    digitalWrite(adress[2], HIGH && (i & B00000100));
    digitalWrite(adress[3], HIGH && (i & B00001000));
    multiplexerStates[i] = analogRead(multiplexer);
  }
}

String translateToButtons(int value)
{
  String buttons = " ";
  if(value>=s1[0] && value<= s1[1]) buttons = "0001";
  else if(value>=s2[0] && value<= s2[1]) buttons = "0010";
  else if(value>=s3[0] && value<= s3[1]) buttons = "0100";
  else if(value>=s4[0] && value<= s4[1]) buttons = "1000";
  else if(value>=s12[0] && value<= s12[1]) buttons = "0011";
  else if(value>=s13[0] && value<= s13[1]) buttons = "0101";
  else if(value>=s14[0] && value<= s14[1]) buttons = "1001";
  else if(value>=s23[0] && value<= s23[1]) buttons = "0110";
  else if(value>=s24[0] && value<= s24[1]) buttons = "1010";
  else if(value>=s34[0] && value<= s34[1]) buttons = "1100";
  else if(value>=s123[0] && value<= s123[1]) buttons = "0111";
  else if(value>=s124[0] && value<= s124[1]) buttons = "1011";
  else if(value>=s134[0] && value<= s134[1]) buttons = "1101";
  else if(value>=s234[0] && value<= s234[1]) buttons = "1110";
  else if(value>=s1234[0] && value<= s1234[1]) buttons = "1111";
  else buttons = "0000";
  
  return buttons;
}

void setup() 
{
  for(int i=0; i<4; i++) 
  {
    pinMode(adress[i], OUTPUT);
    digitalWrite(adress[i], LOW);
  }
  Serial.begin(9600);
  Serial.println("Beginning!");
}

void loop() 
{
  String message = "Buttons pressed: ";
  updateMultiplexer();
  for(int i=0; i<16; i++)
  {
    //Serial.println("Channel " + String(i) + " = " + String(multiplexerStates[i]));
    message += translateToButtons(multiplexerStates[i])+" ";
  }
  Serial.println(message);
  delay(100);
}
