#include "mbed.h"
#include "uLCD_4DGL.h"
#include <iostream>
#include <thread>
#include <ctime> // for clock

using namespace std::chrono;

Timer t;
Thread thread;

DigitalIn upbn(D13);
DigitalIn downbn(D11);
DigitalIn selectbn(D12);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
AnalogOut aout(PA_4);

float freqlist[5] = {1, 82.6, 500, 826.33, 1000};
float ADCdata[500];

void sample(void)
{
    //t.start();
    for(int i = 0; i < 500; i++)
    {
        ADCdata[i] = aout;
        ThisThread::sleep_for(2ms); // let it finish in 1sec
    }
    //t.stop();
    for(int i = 0; i < 500; i++)
    {
        printf("%f\r\n", ADCdata[i]);
    }
    //auto s = chrono::duration_cast<chrono::seconds>(t.elapsed_time()).count();
    //printf("time: %llus\n", s); // -> 3 sec & 500
}

int main()
{    
    // check if the button works
    /*
    while(1)
    {
        printf("up has value : %d \n\r", upbn.read());
        printf("down has value : %d \n\r", downbn.read());
        printf("select has value : %d \n\r", selectbn.read());
        ThisThread::sleep_for(250ms);
    }
    */

    // select the frequency
    float freq = freqlist[0];
    int pos = 0;

    // GUI
    while(1)
    {
        if(upbn.read() && pos!=4) pos++;
        else if(downbn.read() && pos!=0) pos--;
        else if(selectbn.read())
        {
            freq = freqlist[pos];
            break;
        }
        uLCD.locate(0,0);
        uLCD.printf("%-6.f\n", freqlist[pos]);
        ThisThread::sleep_for(100ms);
    }
    uLCD.locate(0,1);
    uLCD.printf("SELECT %.2f Hz\n", freq);

    // setting
    double T = 1/freq;
    double amp = 3/3.3;
    double uptime = T / 10;
    double downtime = T / 10 * 9;
    
    // start thread for sample
    thread.start(sample);

    // main loop
    while(1)
    {
        for(float i = 0; i < amp; i += amp / (uptime / 0.000021))
        {
            aout = i;
        }
        for(float i = amp; i > 0; i -= amp / (downtime/0.000021))
        {
            aout = i;
        }
    }

    thread.join();
}