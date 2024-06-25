// Ajout de la bilbiothèque.
#include <missileLauncher.hpp>

// Utilisation du port série 3 de l'Arduino Méga.
MissileLauncher missileLauncher(&Serial3);

void setup()
{
    // Lancement de la communication avec l'ordinateur.
    Serial.begin(115200);

    // Initialisation du lance missile.
    if (missileLauncher.begin())
    {
        Serial.println(F("Lance-missile prêt !"));

        // Déplacement des deux axes.
        missileLauncher.relativeMove(BASE, 20);
        missileLauncher.relativeMove(ANGLE, -15);

        // Récupération de la position des deux axes
        int baseAngle = 0;
        int angleAngle = 0;

        missileLauncher.getPosition(baseAngle, angleAngle);

        Serial.print(F("Angle de la base : "));
        Serial.println(baseAngle);
        Serial.print(F("Angle de l'inclinaison : "));
        Serial.println(angleAngle);

        // Lancement d'un missile.
        missileLauncher.launchMissile(1);
    }

    else
        Serial.println(F("Erreur de connexion avec le lance-missile."));
}

void loop()
{
    // Vide.
}