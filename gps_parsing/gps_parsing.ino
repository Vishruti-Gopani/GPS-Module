
#include <SoftwareSerial.h> 

SoftwareSerial gpsSerial(12,11);//rx,tx 

int localhour=5;
int localminute=31;
int i ,j;


String GPGAA_i="";
String GPGAA="$GPGAA";
String utc_time="";
String latitude="";
String latitude_d="";
String longitude="";
String longitude_d="";
String date="";
String month="";
String year="";

char gpsdata[5];
uint8_t x,a=0;

void setup()
{ 
Serial.begin(9600); // connect serial 
gpsSerial.begin(56000); // connect gps sensor
} 

void loop(){ 

while(gpsSerial.available())
 {
  
  
 // GPGAA_i=gpsSerial.readStringUntil(',');
 
 // if(GPGAA_i=GPGAA)
  
 
 if(gpsSerial.find("$GPGGA,"))
  { 
   
      
     
      
    Time();
    
    Latitude();
    Longitude();
    for(i=0;i<=8;i++)
    {
     gpsSerial.readStringUntil(',');
      
    }
    
  }

  if(gpsSerial.find("$GPZDA,"))
  {
   Date();
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
 }
}

void Latitude()
{
    latitude=gpsSerial.readStringUntil(',');
    Serial.print("Latitude:");
    float lat=latitude.toFloat();
    Serial.print(lat/100.f,6);
    
    latitude_d=gpsSerial.readStringUntil(',');
    Serial.print("  ");
    Serial.println(latitude_d);
  }


void Longitude()
{
  
    longitude=gpsSerial.readStringUntil(',');
    Serial.print("Longitude:");
    float lon=longitude.toFloat();
    Serial.print(lon/100.f,6);
    
    longitude_d=gpsSerial.readStringUntil(',');
    Serial.print("  ");
    Serial.println(longitude_d);
  
  }
  

void Time()
{
   
    utc_time=gpsSerial.readStringUntil(',');
    float utime=utc_time.toFloat();
    long ut=(long)utime;  
    long hour=(ut/10000);
    long minute=(ut/100)%100;
    long second=(ut)%100;
    Serial.print("UTCtime:");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(second);

   minute=minute+localminute;
   if(minute>59)
      {
       minute=minute-60;
       hour=hour+1;
      }
   else{
        if(minute<0)
        {
        minute=minute+60;
        hour=hour-1;
        }
       }
   
    hour=hour+localhour;
    if(hour>23)
      {
        hour=hour-24;
      }
      else 
         {
        if(hour<0)
        {
          
        hour=hour+24;
        }
    } 
     Serial.print("localtime:");
     Serial.print(hour);
     Serial.print(":");
     Serial.print(minute);
     Serial.print(":");
     Serial.println(second);
    }

void Date()
{ 
  gpsSerial.readStringUntil(',');
  date=gpsSerial.readStringUntil(',');
  month=gpsSerial.readStringUntil(',');
  year=gpsSerial.readStringUntil(',');

   Serial.print("Date:");
   Serial.print(date);
   Serial.print(":");
   Serial.print(month);
   Serial.print(":");
   Serial.println(year);
  
  }
