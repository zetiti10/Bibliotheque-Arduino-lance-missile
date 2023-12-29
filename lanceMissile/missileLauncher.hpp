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

#define END_LINE_CHAR 'e'

/// @brief Objet permettant de contrôler un lance-missile connecté en UART.
class MissileLauncher
{
private:
    String waitForAMessage();
    String addZeros(int number, int totalNumbers);

    HardwareSerial *m_UART;

    unsigned long m_baudRate;
    unsigned long m_timeout;
    unsigned long m_UARTWaitingTime;

public:
    MissileLauncher(HardwareSerial *UART);
    MissileLauncher(HardwareSerial *UART, unsigned long baudRate, unsigned long timeout);

    boolean begin();
    void timerMove(int move, int time);
    void relativeMove(int axis, int angle);
    void absoluteMove(int axis, int angle);
    void beginMove(int move);
    void stopMove(int axis);
    void calibrate();
    void launchMissile(int number);
    void getPosition(int &baseAngle, int &angleAngle);
    void getMissileStates(int &firstMissile, int &secondMissile, int &thirdMissile);
    boolean isConnected();
    boolean isReady();
    int baseCurrentMovement();
    int angleCurrentMovement();
    int missilesToLaunch();
};

#endif