void fillDataString()
{
    dataString = "";
    dataString += String(counter);
    dataString += ",";
    dataString += locationString;
    dataString += ",";
    dataString += speedString;
    dataString += ",";
    dataString += dateString;
    dataString += ",";
    dataString += timeString;
}

void fillLocation()
{
    if (gps.location.isValid())
    {
        locationString = "";
        latD = gps.location.lat();
        lngD = gps.location.lng();
        locationString +=String(latD,6);
        locationString +=",";
        locationString +=String(lngD,6);
    }
}
void fillSpeed()
{
    if (gps.speed.isValid())
    {
        speedString = "";
        speedString += String(gps.speed.kmph(),6);
    }
}
void fillDate()
{
    if (gps.date.isValid())
    {
        dateString = "";
        dateString +=String(gps.date.year());
        dateString +="-";
        Tmonth = gps.date.month();
        if(Tmonth<10)
            dateString += "0";
        dateString +=String(Tmonth);
        dateString +="-";
        Tday = gps.date.day();
        if(Tday<10)
            dateString += "0";
        dateString +=String(Tday);
    }
}
void fillTime()
{
    if(gps.time.isValid())
    {
        timeString = "";
        if (gps.time.hour() < 10) timeString +="0";
        timeString += String(gps.time.hour());
        timeString +=":";
        if (gps.time.minute() < 10) timeString +="0";
        timeString += String(gps.time.minute());
        timeString +=":";
        if (gps.time.second() < 10) timeString +="0";
        timeString += String(gps.time.second());
    }
}

void makeHeader()
{
        headerString = "File: ";
        headerString += filename;
        headerString += " - First fix at ";
        headerString += timeString;
        headerString += " UTC ";
        headerString += dateString;
}
