int packet_size[8] = {};
int packet_size_dec;
const int sync = 30;
void setup() {
  Serial.begin(115200);
}

void GetPacketSize()
{
  packet_size_dec = 0;
  int multiplier = 0;
  for(int i = 0; i < 8; i++)
  {
    if(analogRead(A0) > 36)
    {
      packet_size[i] = 1;
      delay(sync);
    }
    else
    {
      packet_size[i] = 0;
      delay(sync);
    }
  }

  for(int j; j < sizeof(packet_size)/sizeof(*packet_size); j++)
  {
    packet_size_dec = packet_size_dec << 1;
    packet_size_dec = packet_size_dec + packet_size[j];
  }
  //Serial.println(packet_size_dec);
  
}

void GetData()
{
  for(int i = 0; i < packet_size_dec; i++)
  {
    if(analogRead(A0) > 36)
    {
      Serial.print("1");
      delay(sync);
    }
    else
    {
      delay(sync);
      Serial.print("0");
    }
  }
  Serial.println();
}

void loop() {
    if(analogRead(A0) > 36)
    {
      delay(5);
      GetPacketSize();    
      GetData();
    }
}

