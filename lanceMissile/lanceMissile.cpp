/**
 * @file lanceMissile.cpp
 * @author Louis L
 * @brief Fichier contenant les méthodes de la classe lanceMissile.
 * @version 1.0
 * @date 2023-12-21
 */

// Ajout des bibliothèques au programme.
#include <Arduino.h>

// Autres fichiers du programme.
#include "lanceMissile.hpp"

LanceMissile::LanceMissile(UARTClass &UART) : m_UART(UART) {}

LanceMissile::begin()
{
    m_UART->begin(115200);
    
}