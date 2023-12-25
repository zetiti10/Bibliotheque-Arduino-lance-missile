/**
 * @file missileLauncher.cpp
 * @author Louis L
 * @brief Fichier contenant les méthodes de la classe MissileLauncher.
 * @version 1.0
 * @date 2023-12-21
 */

// Ajout des bibliothèques au programme.
#include <Arduino.h>
#include <iostream>
#include <iomanip>
#include <sstream>

// Autres fichiers du programme.
#include "missileLauncher.hpp"

/// @brief Crée un objet lance-missile.
/// @param UART Le port UART à utiliser.
MissileLauncher::MissileLauncher(HardwareSerial *UART) : m_UART(UART) {}

/// @brief Initialise la communication avec le lance-missile.
void MissileLauncher::begin()
{
    m_UART->begin(115200);
}

/// @brief Effectue un déplacement dans un sens pour une durée spécifiée.
/// @param move Le déplacement.
/// @param time Durée du déplacement en millisecondes (jusqu'à 99 999ms).
void MissileLauncher::timerMove(int move, int time)
{
    String messageToSend = "0";
    messageToSend += move;
    messageToSend << std::setfill('0') << std::setw(5) << time;
    m_UART->println(messageToSend);
}

/// @brief Effectue le déplacement d'un axe en fonction d'un angle relatif.
/// @param axis L'axe.
/// @param angle L'angle relatif en degré (de -180 à 180 pour l'axe horizontal et de -40 à +40 pour l'axe vertical).
void MissileLauncher::relativeMove(int axis, int angle)
{
    String messageToSend = "1";
    messageToSend += axis;
    if (angle >= 0)
        messageToSend += "+" else messageToSend += "-";
    messageToSend << std::setfill('0') << std::setw(3) << abs(angle);
    m_UART->println(messageToSend);
}

/// @brief Effectue le déplacement d'un axe à un angle spécifique par rapport au point 0.
/// @param axis L'axe.
/// @param angle L'angle absolu en degré (de 0 à 180 pour l'axe horizontal et de 0 à 40 pour l'axe vertical).
void MissileLauncher::absoluteMove(int axis, int angle)
{
    String messageToSend = "2";
    messageToSend += axis;
    messageToSend << std::setfill('0') << std::setw(3) << angle;
    m_UART->println(messageToSend);
}

/// @brief Débute le mouvement d'un axe dans la direction souhaitée.
/// @param move Le déplacement.
void MissileLauncher::beginMove(int move)
{
    String messageToSend = "30";
    messageToSend += move;
    m_UART->println(messageToSend);
}

/// @brief Stoppe le mouvement d'un axe.
/// @param move L'axe.
void MissileLauncher::stopMove(int move)
{
    String messageToSend = "31";
    messageToSend += move;
    m_UART->println(messageToSend);
}

/// @brief Effectue un calibrage complet du lance-missile.
void MissileLauncher::calibrate()
{
    m_UART->println("32");
}

/// @brief Effectue le lancement de missiles.
/// @param number Le nombre de missile à envoyer.
void MissileLauncher::launchMissile(int number)
{
    String messageToSend = "4";
    messageToSend += number;
    m_UART->println(messageToSend);
}

/// @brief Méthode permettant de récupérer la position actuelle du lance-missile.
/// @return Un pointeur vers un tableau d'entiers : la première valeur est celle de l'axe horiontal et la seconde est celle de l'axe vertical.
int* MissileLauncher::getPosition()
{
    m_UART->println("50");

    String receivedMessage = waitForAMessage();

    int arrayToReturn[2];
    arrayToReturn[0] = int(receivedMessage.substring(0, 3));
    arrayToReturn[1] = int(receivedMessage.substring(8, 11));

    return arrayToReturn;
}

/// @brief Métrode permettant de savoir si un missile est chargé à chaque emplacement.
/// @return Un pointeur vers un tableau d'entiers de 3 valeurs (1 = missile chargé et 0 = vide).
int* MissileLauncher::getMissileStates()
{
    m_UART->println("51");

    String receivedMessage = waitForAMessage();

    int arrayToReturn[3];
    arrayToReturn[0] = int(receivedMessage.substring(0, 1));
    arrayToReturn[1] = int(receivedMessage.substring(1, 2));
    arrayToReturn[2] = int(receivedMessage.substring(2, 3));

    return arrayToReturn;
}

/// @brief Méthode permettant de savoir si un lance-missile est connecté.
/// @return Retourne `true` si un lance missile est actuellement connecté.
boolean MissileLauncher::isConnected()
{
    m_UART->println("52");

    String receivedMessage = waitForAMessage();

    return (!receivedMessage == "");
}

/// @brief Méthode permetant de savoir si le lance missile connecté est initialisé / calibré.
/// @return Retourne `true` si le lance missile est initialisé et calibré.
boolean MissileLauncher::isReady()
{
    m_UART->println("52");

    String receivedMessage = waitForAMessage();

    if (receivedMessage == "") return false;

    return int(receivedMessage[0]);
}

/// @brief Méthode permettant de savoir si l'axe de la base est en mouvement.
/// @return Retourne le mouvement actuel.
int MissileLauncher::baseCurrentMovement()
{
    m_UART->println("53");

    String receivedMessage = waitForAMessage();

    if (receivedMessage == "") return STILL;

    return receivedMessage[1];
}

/// @brief Méthode permettant de savoir si l'axe de l'inclinaison est en mouvement.
/// @return Retourne le mouvement actuel.
int MissileLauncher::angleCurrentMovement()
{
    m_UART->println("53");

    String receivedMessage = waitForAMessage();

    if (receivedMessage == "") return STILL;

    return receivedMessage[0];
}

/// @brief Méthode permettant de connaître le nombre de missiles restants à lancer.
/// @return Le nombre de missiles qui restent à lancer.
int MissileLauncher::missilesToLaunch()
{
    m_UART->println("53");

    String receivedMessage = waitForAMessage();

    if (receivedMessage == "") return 0;

    return receivedMessage[0];
}

String MissileLauncher::waitForAMessage()
{
    unsigned long initialTime = millis();

    while (!m_UART->available()) 
    {
        delay(1);

        if (millis >= (initialTime + CONNECTION_TIMEOUT)) return "";
    }

    delay(25);

    String receivedMessage;
    while (UART->available() > 0)
    {
        char letter = UART->read();
        receivedMessage += letter;
    }

    return receivedMessage;
}