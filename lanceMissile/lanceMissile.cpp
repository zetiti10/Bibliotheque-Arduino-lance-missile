/**
 * @file lanceMissile.cpp
 * @author Louis L
 * @brief Fichier contenant les méthodes de la classe lanceMissile.
 * @version 1.0
 * @date 2023-12-21
 */

// Ajout des bibliothèques au programme.
#include <Arduino.h>
#include <iostream>
#include <iomanip>
#include <sstream>

// Autres fichiers du programme.
#include "lanceMissile.hpp"

LanceMissile::LanceMissile(HardwareSerial *UART) : m_UART(UART) {}

void LanceMissile::begin()
{
    m_UART->begin(115200);
}

/// @brief Effectue un déplacement dans un sens pour une durée spécifiée.
/// @param move Le déplacement.
/// @param time Durée du déplacement en millisecondes (jusqu'à 99 999ms).
void LanceMissile::timerMove(int move, int time)
{
    String messageToSend = "0";
    messageToSend += move;
    messageToSend << std::setfill('0') << std::setw(5) << time;
    m_UART->println(messageToSend);
}

/// @brief Effectue le déplacement d'un axe en fonction d'un angle relatif.
/// @param axis L'axe.
/// @param angle L'angle relatif en degré (de -180 à 180 pour l'axe horizontal et de -40 à +40 pour l'axe vertical).
void LanceMissile::relativeMove(int axis, int angle)
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
void LanceMissile::absoluteMove(int axis, int angle)
{
    String messageToSend = "2";
    messageToSend += axis;
    messageToSend << std::setfill('0') << std::setw(3) << angle;
    m_UART->println(messageToSend);
}

/// @brief Débute le mouvement d'un axe dans la direction souhaitée.
/// @param move Le déplacement.
void LanceMissile::beginMove(int move)
{
    String messageToSend = "30";
    messageToSend += move;
    m_UART->println(messageToSend);
}

/// @brief Stoppe le mouvement d'un axe.
/// @param move L'axe.
void LanceMissile::stopMove(int move)
{
    String messageToSend = "31";
    messageToSend += move;
    m_UART->println(messageToSend);
}

/// @brief Effectue un calibrage complet du lance-missile.
void LanceMissile::calibrate()
{
    m_UART->println("32");
}

/// @brief Effectue le lancement de missiles.
/// @param number Le nombre de missile à envoyer.
void LanceMissile::launchMissile(int number)
{
    String messageToSend = "4";
    messageToSend += number;
    m_UART->println(messageToSend);
}