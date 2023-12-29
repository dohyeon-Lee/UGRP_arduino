#define SBUF_SIZE 64*2
 
char sbuf[SBUF_SIZE];
signed int sbuf_cnt=0;

int EBimuAsciiParser(float *item, int number_of_item)
{
  int n,i;
  int rbytes;
  char *addr; 
  int result = 0;
  
  rbytes = Serial1.available();
  // Serial.println(rbytes);
  for(n=0;n<rbytes;n++)
  {
    sbuf[sbuf_cnt] = Serial1.read();
    if(sbuf[sbuf_cnt]==0x0a)
    {
      // Serial.println(sbuf);
      addr = strtok(sbuf,",");
      for(i=0;i<number_of_item;i++)
      {
        item[i] = atof(addr);
        addr = strtok(NULL,",");
      }

      result = 1;
    }
    else if(sbuf[sbuf_cnt]=='*')
    {
      sbuf_cnt=-1;
    }
 
    sbuf_cnt++;
    if(sbuf_cnt>=SBUF_SIZE) sbuf_cnt=0;
  }
  
  return result;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.write("<soa2>");
  Serial1.write("<sor1>");
  Serial.println(Serial1.read());
}

int count = 0;
void loop() {
  // put your main code here, to run repeatedly:
  float Data[6];
  if(EBimuAsciiParser(Data, 6))
  {
    Serial.print("\n\r");
    Serial.print(Data[0]);   Serial.print(" ");
    Serial.print(Data[1]);   Serial.print(" ");
    Serial.print(Data[2]);   Serial.print(" ");
    Serial.print(Data[3]);   Serial.print(" ");
    Serial.print(Data[4]);   Serial.print(" ");
    Serial.print(Data[5]);   Serial.print(" ");
    // double dt = double((micros() - now))/1000000.;
    // Serial.print(1/dt);
  }
}
