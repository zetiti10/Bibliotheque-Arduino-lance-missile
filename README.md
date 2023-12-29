# Bibliotheque-Arduino-lance-missile

Bibliothèque Arduino en C++ permettant de contrôler aisément un lance missile, connecté en UART.

## Utilisation de la bibliothèque

### Instanciation d'un objet lance-missile

Il existe deux constructeurs pour instancier un objet lance-missile :

1. `MissileLauncher missileLauncher(HardwareSerial *UART);` qui ne demande qu'une référence vers un `HardwareSerial`. La vitesse de communication est définie à `115200` et le délai d'attente à `1000`.

2. `MissileLauncher missileLauncher(HardwareSerial *UART, unsigned long baudRate, unsigned long timeout);` qui nécessite de préciser en plus une vitesse de communication et un délai d'attente avant de considérer le lance-missile comme déconnecté.

### Initiaisation de la communication

Pour initialiser la communication avec le lance-missile (dans le `void setup()`), il faut utiliser la méthode `missileLauncher.begin();`. Cette méthode est bloquante : elle retourne `true` lorsque l'initialisation du lance-missile est terminée et `false` s'il y a une erreur de communication.

### Informations importantes

Le lance-missile peut être contrôlé de plusieurs manières.

> Dans toutes les méthodes, les temps sont en millisecondes.

Les méthodes ayant pour paramètre `int move` demandent une direction parmis les suivantes :

| Direction | Nom dans le programme |
| --------- | --------------------- |
| Haut      | `UP`                  |
| Bas       | `DOWN`                |
| Gauche    | `LEFT`                |
| Droite    | `RIGHT`               |

Les méthodes ayant pour paramètre `int axis` demandent une direction parmis les suivantes :

| Axe                    | Nom dans le programme |
| ---------------------- | --------------------- |
| Rotation de la base    | `BASE`                |
| Inclinaison de la tête | `ANGLE`               |

Les méthodes permettant de récupérer les mouvements actuels des axes peuvent renvoyer en plus d'une direction, la valeur `STILL` lorsqu'un axe est immobile.

L'angle de rotation de la base est de `180°` et celui de l'inclinaison est de `40°`.

### Contrôle du lance-missile

- `missileLauncher.timerMove(int move, int time);` : effectue un déplacement dans un sens pour une durée spécifiée. Durée max : `99 999 ms`.
- `missileLauncher.relativeMove(int axis, int angle);` : effectue le déplacement d'un axe en fonction d'un angle relatif. L'angle va de `-180` à `180` pour la base et de `-40` à `40` pour l'inclinaison.
- `missileLauncher.absoluteMove(int axis, int angle);` : effectue le déplacement d'un axe à un angle spécifique par rapport au point 0. L'angle va de `0` à `180` pour la base et de `0` à `40` pour l'inclinaison.
- `missileLauncher.beginMove(int move);` : débute le mouvement d'un axe dans la direction souhaitée.
- `missileLauncher.stopMove(int axis);` : stoppe le mouvement d'un axe.
- `missileLauncher.calibrate();` : effectue un calibrage complet du lance-missile. Méthode bloquante : retour à la fin de la calibration ou si le lance-missile est déconnecté.
- `missileLauncher.launchMissile(int number)` : effectue le lancement de missiles. Le paramètre `number` indique le nombre de missiles à envoyer (de `0` à `3`).

### Récupération d'informations du lance-missile

- `missileLauncher.getPosition(int &baseAngle, int &angleAngle);` : méthode permettant de récupérer la position actuelle du lance-missile. Les deux paramètres sont les variables ou seront enregistrées les valeurs d'angles actuelles.
- `missileLauncher.getMissileStates(int &firstMissile, int &secondMissile, int &thirdMissile);` : métrode permettant de savoir si un missile est chargé à chaque emplacement. Les trois paramètres sont les variables ou seront enregistrés les états des supports de missile (chargé = `1` ou vide = `0`);
- `missileLauncher.isConnected();` : méthode permettant de savoir si un lance-missile est connecté.
- `missileLauncher.isReady();` : méthode permetant de savoir si le lance missile connecté est initialisé / calibré.
- `missileLauncher.baseCurrentMovement();` : méthode permettant de savoir si l'axe de la base est en mouvement. Retourne un mouvement (voir la section "Informations importantes").
- `missileLauncher.angleCurrentMovement();` : méthode permettant de savoir si l'axe de l'inclinaison est en mouvement. Retourne un mouvement (voir la section "Informations importantes").
- `missileLauncher.missilesToLaunch();` : méthode permettant de connaître le nombre de missiles restants à lancer.

## Exemple

Disponible dans les dossier `examples`.

```cpp
// Ajout de la bilbiothèque.
#include "missileLauncher.hpp"

// Utilisation du port série 3 de l'Arduino Méga.
MissileLauncher missileLauncher(&Serial3);

void setup()
{
    // Lancement de la communication avec l'ordinateur.
    Serial.begin(115200);

    // Initialisation du lance missile.
    if (missileLauncher.begin())
    {
        Serial.println("Lance-missile prêt !");

        // Déplacement des deux axes.
        missileLauncher.relativeMove(BASE, 20);
        missileLauncher.relativeMove(ANGLE, -15);

        // Récupération de la position des deux axes
        int baseAngle = 0;
        int angleAngle = 0;

        missileLauncher.getPosition(baseAngle, angleAngle);

        Serial.print("Angle de la base : ");
        Serial.println(baseAngle);
        Serial.print("Angle de l'inclinaison : ");
        Serial.println(angleAngle);

        // Lancement d'un missile.
        missileLauncher.launchMissile(1);
    }

    else
        Serial.println("Erreur de connexion avec le lance-missile.");
}

void loop()
{
    // Vide.
}
```
