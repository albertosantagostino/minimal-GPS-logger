void executeCommand()
{
   if (inputString == "start")
   {
      if(sdok)
      {
        Serial2.println("Registrazione AVVIATA!");
        recording = 1;
        Timer3.start(monitorTimer*1000);
      }
      if(!sdok)
        Serial2.println("SD ERROR! Check and reset");
   }
   if (inputString == "stop")
   {
      recording = 0;
      Timer3.stop();
   }
    if (inputString == "logon")
      Timer3.start(monitorTimer*1000);
    if (inputString == "logoff")
      Timer3.stop();
    if (inputString == "help")
      bluetoothIntro();
}
void bluetoothPing()
{
    fillLocation();
    fillTime();
    dataString = "";
    dataString += String(counter);
    dataString += ",";
    dataString += locationString;
    dataString += ",";
    dataString += timeString;
    if (sdok)
      dataString += " SDOK";
    if (!sdok)
      dataString += " NOSD";
    if (recording == 1)
      dataString += " RECORDING";
    if (recording == 0)
      dataString += " STANDBY";

    Serial2.println(dataString);
    dataString = "";
}

void bluetoothIntro()
{
  Serial2.flush();
  Serial2.println("");
  Serial2.println(" _______________________________");
  Serial2.println("|     MinimalGPSLogger AS       |");
  Serial2.println("|                               |");
  Serial2.println("| START / STOP to record on SD  |");
  Serial2.println("| LOGON / LOGOFF to monitor GPS |");
  Serial2.println("| HELP for this command list    |");
  Serial2.println("|                               |");
  Serial2.print  ("| SD ");
  if(sdok)
  {
    Serial2.print(":)    ");
    Serial2.print(filename);
    Serial2.println("            |");
  }
  if(!sdok)
    Serial2.println(":(                         |");
  Serial2.println("|_______________________________|");
  Serial2.println("");
}

