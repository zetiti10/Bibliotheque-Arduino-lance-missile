#ifndef MISSILE_LAUNCHER_DEFINITIONS
#define MISSILE_LAUNCHER_DEFINITIONS

#include <Arduino.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define STILL 4

#define BASE 0
#define ANGLE 1

#define CONNECTION_TIMEOUT 1000

class MissileLauncher
{
public:
    MissileLauncher(HardwareSerial *UART);
    void begin();
    void timerMove(int move, int time);
    void relativeMove(int axis, int angle);
    void absoluteMove(int axis, int angle);
    void beginMove(int move);
    void stopMove(int axis);
    void calibrate();
    void launchMissile(int number);
    int* getPosition();
    int* getMissileStates();
    boolean isConnected();
    boolean isReady();
    int baseCurrentMovement();
    int angleCurrentMovement();
    int missilesToLaunch();

private:
    String waitForAMessage();

    HardwareSerial *m_UART;
};

#endif