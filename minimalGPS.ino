//#define DEBUG

#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <DueTimer.h>

#define monitorTimer 2000 // Ever #ms bluetooth log
#define recInterval 1000
#define buttonPin   2
#define ledPin      3
unsigned long millisOld;
unsigned long tDelay;

TinyGPSPlus gps;

int recording = 0;

boolean stringComplete = false;
String inputString = "";

const int CS = 4;
int sdok = 0;
File dataFile;
File root;
File entry;
String filename = "";
int numfile = 0;
int contafile;
unsigned long counter = 0;

String dataString = "";
String locationString = "noFix";
String speedString = "noSpeed";
String timeString = "00:00:00";
String dateString = "YYYY-MM-DD";
String headerString = "";

double latD = 0;
double lngD = 0;

int Tday = 0, Tmonth = 0;

void setup()
{
    Serial1.begin(9600);
    Serial2.begin(9600);    //Bluetooth
    Serial.begin(9600);
    pinMode(CS, OUTPUT);
    pinMode(buttonPin,INPUT);
    pinMode(ledPin,OUTPUT);

    if (SD.begin(CS))
    {
        newfilename();
        sdok = 1;
    }
    else
    {
        Serial.println("ERRORE SD!");
        sdok = 0;
    }
    Timer3.attachInterrupt(bluetoothPing);

    bluetoothIntro();
}

void loop()
{
      if (Serial2.available() > 1)
      {
        inputString = Serial2.readStringUntil('\r');
        inputString.toLowerCase();
        Serial2.println("");
        executeCommand();
        Serial2.flush();
        inputString = "";
      }
    while (Serial1.available())
        gps.encode(Serial1.read());

    // buttonCheck();
    
    //#ifdef DEBUG
    //    recording = 1;
    //#endif
    
    if (recording == 1)
    {
        digitalWrite(ledPin,HIGH);
        millisOld= millis();
        record();
        tDelay = (recInterval - constrain(millis() - millisOld, 0, recInterval));
        digitalWrite(ledPin,LOW);
        delay(tDelay);
    }
}

void record()
{
    fillLocation();
    fillSpeed();
    fillDate();
    fillTime();
    
    fillDataString();

    if (gps.location.isValid())
    {
        dataFile = SD.open(filename, FILE_WRITE);
        if (dataFile)
        {
            if(counter==0)
            {
                makeHeader();
                dataFile.println(headerString);
                dataFile.println("");
                dataFile.println("N,latitude,longitude,speed,date,time");
            }
            else
                dataFile.println(dataString);
            dataFile.close();
            counter++;
        }
        
        
        #ifdef DEBUG
        Serial.println(dataString);       // Only for debugging (with recording = 1)
        #endif
    }
}

void newfilename()
{
    if(dataFile)
      dataFile.close();
    root = SD.open("/");
    contafile = 1;
    while (true)
    {
        entry  =  root.openNextFile();
        if (!entry)
        {
            break;
        }
        if (!entry.isDirectory())
        {
            contafile++;
            // entry.name();
        }
        entry.close();
    }
    root.close();
    filename = "";
    filename += "LOG";
    if (contafile < 10)
        filename += "0";
    filename += ("%d", contafile);
    filename += (".txt");
    SD.begin(CS);
}


