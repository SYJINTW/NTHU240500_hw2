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

### Running

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

Skip for now.  
Study probability first.

<!-- Screenshot -->
## Results

* Picoscope result at 1 Hz
  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/1Hz.png?raw=true">  

* Python Matplotlib at 1 Hz

    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/1Hz_py.png?raw=true">

* Picoscope result at 826.3 Hz (cut-off frequency)
  
    <img src="https://github.com/SYJINTW/NTHU240500_hw2/blob/master/hw2/src/826Hz.png?raw=true"> 

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* [Electronics Tutorials](https://www.electronics-tutorials.ws/filter/filter_2.html)
* [w3schools.com](https://www.w3schools.com/python/)

