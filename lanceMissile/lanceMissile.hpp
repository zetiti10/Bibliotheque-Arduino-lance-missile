#ifndef LANCE_MISSILE_DEFINITIONS
#define LANCE_MISSILE_DEFINITIONS

#include <Arduino.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define BASE 0
#define ANGLE 1

class LanceMissile
{
public:
    LanceMissile(HardwareSerial *UART);
    void begin();
    void timerMove(int move, int time);
    void relativeMove(int axis, int angle);
    void absoluteMove(int axis, int angle);
    void beginMove(int move);
    void stopMove(int axis);
    void calibrate();
    void launchMissile(int number);
    int getPosition(); // Tableau de 2.
    int getMissileStates(); // Tableau de 3.

private:
    HardwareSerial *m_UART;
};

#endif