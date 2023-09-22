#include <SFE_BMP180.h>

#include <Wire.h>

SFE_BMP180 bmp; // Créez un objet bmp

#define SEALEVELPRESSURE_HPA (1013.25) // Définissez la pression au niveau de la mer en hPa

#define Altitude 54 // Définissez l'altitude de votre ville par rapport au niveau de la mer

 

void setup() {

  Serial.begin(9600); // Commencez la communication série

  if (bmp.begin()) { // Initialiser le capteur

    Serial.println("Capteur BMP180  trouvé");

  } else {

    Serial.println("Capteur BMP180 non trouvé");

    while(1); // Arrêtez le programme si le capteur n'est pas détecté

  }

}

 

void loop() {

  char status; // Créez une variable pour stocker le statut du capteur

  double T,P,p0,a; // Créez des variables pour stocker la température, la pression, la pression au niveau de la mer et l'altitude

  status = bmp.startTemperature(); // Commencez une mesure de température

  if (status != 0) { // Si la mesure a commencé

    delay(1000); // Attendez que la mesure soit terminée

    status = bmp.getTemperature(T); // Obtenez la valeur de température en °C

    if (status != 0) { // Si la valeur est valide

      Serial.print("Temperature: ");

      Serial.print(T,2);

      Serial.println(" C");

 

      status = bmp.startPressure(3); // Commencez une mesure de pression avec une résolution maximale

      if (status != 0) { // Si la mesure a commencé

        delay(status); // Attendez que la mesure soit terminée

        status = bmp.getPressure(P,T); // Obtenez la valeur de pression en hPa

        if (status != 0) { // Si la valeur est valide

          Serial.print("Pressure: ");

          Serial.print(P,2);

          Serial.println(" hPa");

         p0 = bmp.sealevel(P,Altitude); // Calculez la pression au niveau de la mer en fonction de l'altitude connue (1655 mètres dans cet exemple)

          Serial.print("Pression au niveau de la mer à l'altitude donné: ");

          Serial.print(p0,2);

          Serial.println(" hPa");

          a = bmp.altitude(P,p0); // Calculez l'altitude en fonction de la pression au niveau de la mer

          Serial.print("Altitude: ");

          Serial.print(a,2);

          Serial.println(" m");

        } else {

          Serial.println("Erreur lors de la lecture de la pression\n");

        }

      } else {

        Serial.println("Erreur lors du démarrage de la mesure de pression\n");

      }

    } else {

      Serial.println("Erreur lors de la lecture de la température\n");

    }

  } else {

    Serial.println("Erreur lors du démarrage de la mesure de température\n");

  }

  Serial.println(); // Imprimez une ligne vide

  delay(3000); // Attendez 3 secondes avant la prochaine mesure

}
