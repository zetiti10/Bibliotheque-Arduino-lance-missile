#ifndef LANCE_MISSILE_DEFINITIONS
#define LANCE_MISSILE_DEFINITIONS

#include <Arduino.h>

class LanceMissile
{
    public:
    LanceMissile(UARTClass &UART);
    void begin();
    void timerMove(int move, int time);
    void relativeMove(int axis, int angle);
    void absoluteMove(int axis, int angle);
    void beginMove(int move);
    void stopMove(int axis);
    void calibrate();
    void launchMissile(int number);
    int[] getPosition();
    int[] getMissileStates();

    private:
    UARTClass *m_UART;
};

#endif