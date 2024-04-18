## RobotCar
#Self driving robot car


**Aim**:

To design a robot car which can drive itself surrounding an object such as a trash can or one gallon milk bottle with an ultrasonic distance sensor and audio sensor

**Steps**

(1) Use the Arduino to control the two DC motors to drive the car moving forward, backward,
turn left, or turn right.

(2) Use the ultrasonic distance sensor to measure the distance between the car and a
nearby object such as a trash can.

(3) Implement a control algorithm to drive the robot car such that the car cycles around a
trash can (or other object placed on the floor) but never touches it. You can refer to the
demo video (reference [5]).

(4) use the sound sensor module to sample pre-recorded tones and convert the sound to
digital values

(5) use FFT library to process the audio samples and detect peak frequencies

(6) compare the peak frequencies detected against know patterns. The pattern to match is
music notes “C4” and “A4” (with frequency of 262Hz, 440Hz, respectively). If the note is
“C4”, stop the robot car. If the note is “A4”, allow the robot car to continue its movement.
To match with the frequencies, an error of 2% is allowed. For example, you can
recognize the note as C4 if the peak frequency is in the range of between 257Hz and
267Hz.



**MATERIALS REQUIRED:**
| Part Name                                                                     |Quantity   |
|-------------------------------------------------------------------------------|-----------|
|                                                                               |           |
| Arduino board                                                                 | 1         |
| DC motor                                                                      | 1         |
| Power supply module                                                           | 1         |
| L293D                                                                         | 1         |
| Button                                                                        | 1         |
| Sound module                                                                  | 1         |
| Robot kit(includes top/bottom plates,batterycharger,tt motors,wheels setsetc) | 1         |
| assorted jumper wires                                                         | as needed |

**Demo:**

https://github.com/CartagenaUML/sensors-and-actuators/assets/157857568/22aa6e01-399a-4b6b-9962-dd4dc73d7622


**Images**



![Robot car](https://github.com/CartagenaUML/sensors-and-actuators/assets/157857568/a02b8b8e-38b1-45f5-814f-848c89485ddf)


![56de3c2a-28a1-4811-b00e-9fa722d2f02d - Copy](https://github.com/CartagenaUML/sensors-and-actuators/assets/157857568/bde90a2d-c796-41a1-a570-b7889441c243)
![56de3c2a-28a1-4811-b00e-9fa722d2f02d](https://github.com/CartagenaUML/sensors-and-actuators/assets/157857568/cac81d8e-8425-43a6-b7f0-71a7e42bf36d)

References:
1. Arduino IDE: https://www.arduino.cc/en/main/software
   
2. The resource files (sample code and tutorials) from Elegoo:
https://www.elegoo.com/download/

3. For EECE.5520 students, you need to install “arduinoFFT” library through the IDE’s library
manager tool.

4. For EECE.5520 students, you need to refer to the robot car assembly guide to build the two-wheel
robot car: https://github.com/ACANETS/eece-4520-5520-
labs/blob/2039441de8a069a14cadbb58f175f142d48f87c0/lab3/assembly%20guide.md

5. Add FFT library manually from Arduino IDE Manage libraries and add ArduinoFFT by Enrique Condes
   
6. Hugging bot demo video: https://youtu.be/7CNUAesYvLU
