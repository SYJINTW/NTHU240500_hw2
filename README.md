<!-- ABOUT THE PROJECT -->
## About The Project

This is a project for Embedded System Lab's homework.
It is about using creating a GUI on uLCD, then use DAC to create a triangle wave, and use ADC to detect it, then use matplotlib to plot the ADC data. 

### Built With

* C++
* Python

## Homework Description
* (Inputs) Add buttons on the bread board (as DigitalIn): up, down and select.
* (Display) Create a selection display on uLCD to select from a few frequencies by your choice, e.g., 100Hz, 200Hz, etc.
* (Generate waveform) Use DAC to generate a wave form with the chosen frequency and pass the generated signal through a RC low pass filter.
* (Measure) Use Picoscope to measure the generated wave form.
* (Sample) Sample the generated wave form and send the value to PC/Python.
* (Analysis) Analyze the captured waveform: show frequency response and wave on screen with Matplotlib.

<!-- GETTING STARTED -->
## Getting Started

### Running & compile

* Embedding in B_L4S5I_IOT01A
  
    ```sh
    sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f
    ```
* To check the output of ADC by screen
    
    ```sh
    sudo screen /dev/ttyACM0
    ```
* Run python FFT.py to analysis the wave
  
    ```sh
    sudo python3.8 FFT.py
    ```


<!-- ROADMAP -->
## Roadmap

1. Create GUI for choosing the which freqency to generate. And sleep 100ms to refreshing the output on uLCD.

    ```C++
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
    ```

    GUI may look like the image below.
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/uLCD_1.png?raw=true">
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/uLCD_82.6.png?raw=true">  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/uLCD_500.png?raw=true">  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/uLCD_826.png?raw=true">  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/uLCD_1000.png?raw=true">  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/uLCD_select.png?raw=true">  


1. Generate the triangle waveform by DAC, and define the X-axis value when the waveform peaks at 3V, and 1/10 wave length from left is the peak. So first I change the amp to 3V by transform by 3/3.3. However, I calculate the time of for-loop by Timer to replace using sleep_for(). The timer is `0.000237 seconds` in one for-loop.
    ```C++
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
        for(float i = 0; i < amp; i += amp / (uptime / 0.0000237))
        {
            aout = i;
        }
        for(float i = amp; i > 0; i -= amp / (downtime/0.0000237))
        {
            aout = i;
        }
    }
    ```

1. Use Timer to calculate the time of the loop, and use `duration_cast<chrono::seconds>(t.elapsed_time()).count()` to get the time of the loop, the time will be `3 seconds`.
So that we know the freqency of sample is `500/3=16.66667Hz`
    ```C++
    // in main function
    ...
    thread.start(sample);
    ...

    // sample function define
    void sample(void)
    {
        t.start();
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
        auto s = chrono::duration_cast<chrono::seconds>(t.elapsed_time()).count();
        printf("time: %llus\n", s); // -> 3 sec & 500
    }
    ```
    
1. In FFT.py, we must change the sampling rate to the loop frequency in sample function.
    
    ```python
    Fs = 1000.000
    ```

<!-- Screenshot -->
## Results

* Picoscope result at 1 Hz
  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/wv_1Hz.png?raw=true">  

* Python Matplotlib at 1 Hz

    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/py_1Hz.png?raw=true">

* Picoscope result at 82.6 Hz
    
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/wv_82.6Hz.png?raw=true">  

* Python Matplotlib at 82.6 Hz
    
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/py_82.6Hz.png?raw=true">

* Picoscope result at 500 Hz

    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/wv_500Hz.png?raw=true">  

* Python Matplotlib at 500 Hz

    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/py_500Hz.png?raw=true">

* Picoscope result at 826.3 Hz (cut-off frequency)
  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/wv_826Hz.png?raw=true"> 

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* [Electronics Tutorials](https://www.electronics-tutorials.ws/filter/filter_2.html)
* [w3schools.com](https://www.w3schools.com/python/)

