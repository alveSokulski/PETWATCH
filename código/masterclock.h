#pragma once

class MasterClock{
    Time lastTime;
    
    int firstIt;
    unsigned long lastIt;
    unsigned long correct;

    void timeStore();
    void timeRestart();
    Time addSecondsToDate(Time indate, long seconds);
    int daysElapsed(Time date0, Time date1);

  public:

    Time returnHours();
    Time initTime;
    MasterClock();
    long secondsElapsed();
    
};
