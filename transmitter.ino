String data = "";
String packet_size = "";
void setup() {
  Serial.begin(115200);
  pinMode(3,OUTPUT);
  digitalWrite(3, HIGH);
}


void sendOne(){
  digitalWrite(3,LOW);
  delay(30); 
  digitalWrite(3,HIGH);
}


void sendZero(){
  delay(30); 
}


void init_connection()
{
  digitalWrite(3, LOW);
  delay(5);
  digitalWrite(3, HIGH);
}


void GetPacketSize(int dec) {
  while(dec>0) 
  { 
    packet_size = dec%2 + packet_size; 
    dec=dec/2;
  }
  while(packet_size.length()<8)
  {
    packet_size = "0" + packet_size;
  }
  //Serial.println(packet_size);
}


void SendPacketSize() {
    for(int i = 0; i < packet_size.length(); i++){
    if(packet_size[i] == '1')
    {
      sendOne();
    }
    else
    {
      sendZero();
    }
  }
  packet_size = "";
}


void SendData()
{
  for(int i = 0; i < data.length(); i++)
  {
    if(data[i] == '1')
    {
      sendOne();
      //Serial.print(data[i]);
    }
    else
    {
      sendZero();
      //Serial.print(data[i]);
    }
  }
  //Serial.println();
}


void loop() {
  while(Serial.available() == 0){}
    data = Serial.readString();
    GetPacketSize(data.length());
    init_connection();
    SendPacketSize();
    SendData();
    Serial.println();
}
