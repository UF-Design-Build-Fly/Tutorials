int data = 0;
bool up = true; //direction won't work! Syntax highlighting is important

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //make sure this number (baud rate) matches what you select in the serial console

}

void loop() { //feature to show if brackets are matched
  // put your main code here, to run repeatedly:
  Serial.println(data);
  if (up == true) { //remember this is redundant
    data = data + 1; //show how I constantly forget semicolon
    if (data > 300)
    {
      up = false;
    }
  } else
  {
    data = data - 1;
    if (data <= 0)
    {
      up = true;
    }
  }
}
