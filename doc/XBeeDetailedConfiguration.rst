Configurer le module Xbee
-------------------------

Vous pouvez configurer un module XBee depuis du code fonctionnant sur
une carte Arduino OU depuis un logiciel fonctionnant sur un ordinateur.
Pour le configurer depuis une carte Arduino, il faut placer
l'interrupteur sur la position "Micro". Pour configurer le module XBee
depuis un ordinateur, il faut placer l'interrupteur sur la position
"USB" et désactiver le microcontroleur (ou le retirer de la carte
Arduino).

Pour passer le module en mode de configuration, vous devez lui envoyer 3
signes plus: +++ et il doit y avoir un temps d'au moins une seconde
avant et une seconde après durant lequel aucun autre caractère n'est
envoyé au module. Notez que cela inclus le caractère "newlines" (10) ou
retour clavier (13).

Donc, si vous voulez configurer le module XBee depuis un ordinateur,
vous devez utiliser un logiciel qui envoi exactement comme vous les
tapez... sans attendre que pressiez la touche Enter/Entrée. Sinon il
enverra les caractères '+' suivit d'un retour à la ligne (il n'y aura
donc pas le delay d'un seconde absolument nécessaire après le +++ et le
retour clavier qui aura été ajouté).

Lorsque vous passez en more de configuration, le module renvoi les deux
caractères 'OK', suivit d'un retour clavier (la touche "Enter"/Entrée).

Dans les exemples suivant, la touche Entrée/Enter est symbolisée par
("Carriage Return" en anglais, signifiant Retour Charriot comme sur les
vielle machines à écrire).

+------------------+------------------+
| Commande envoyée | Réponse Attendue |
+==================+==================+
| +++              | OK               |
+------------------+------------------+

Une fois de le mode de configuration, vous pouvez envoyer des commande
AT au module. Les chaines de commande ont la forme ATxx (où xx est le
nom du paramètre). Pour lire la valeur actuelle d'un paramètre, envoyez
la chaine de commande suivit de la touche Entrée/Enter. Pour écrire une
nouvelle valeur dans un paramètre, utilisez la chaine de commande
immédiatement suivie de la nouvelle valeur et pressez la touche
Entrée/Enter (pas d'espace ni ne retour clavier entre la commande et la
valeur).

Par exemple, pour lire l'identification réseau (network ID) du module
qui identifie quels sont les autres modules XBee avec lesquels le module
communique, il faut utiliser la commande *ATID* :

+------------------+------------------+
| Commande envoyée | Réponse Attendue |
+==================+==================+
| ATID             | 3332             |
+------------------+------------------+

Pour changer la valeur d'identification du réseau (network ID) du module
:

+------------------+------------------+
| Commande envoyée | Réponse Attendue |
+==================+==================+
| ATID3331         | OK               |
+------------------+------------------+

Vérifiez maintenant que la nouvelle valeur soit bien prise en compte par
le module XBee:

+------------------+------------------+
| Commande envoyée | Réponse Attendue |
+==================+==================+
| ATID             | 3331             |
+------------------+------------------+

A moins d'indiquer au module XBee d'enregistrer la nouvelle valeur du
paramètre dans sa mémoire non volatile, le paramètre modifié sera perdu
dès que le module est mis hors tension.

Pour sauver les modifications de façon permanente (dans la mémoire non
volatile), vous devez utiliser la commande **ATWR**:

+------------------+------------------+
| Commande envoyée | Réponse attendue |
+==================+==================+
| ATWR             | OK               |
+------------------+------------------+

Pour "resetter" le module aux paramètres d'usine, il faut utiliser la
commande **ATRE** :

+------------------+------------------+
| Commande envoyée | Réponse attendue |
+==================+==================+
| ATRE             | OK               |
+------------------+------------------+

Comme pour les autres commandes, le "reset" des paramètres ne sera
permanent que si la commande **ATWR** est exécutée.

Références
----------

Pour plus d'informations, vous pouvez consulter la page `Arduino
Wireless Shield <Arduino Wireless Shield>`__ qui accueille les modules
XBee sur Arduino, mais également la page `Xbee de
Digi <http://www.digi.com/products/wireless-wired-embedded-solutions/zigbee-rf-modules/point-multipoint-rfmodules/>`__.
Le texte orginal de "`Arduino getting started
guide <http://arduino.cc/en/Guide/ArduinoWirelessShield>`__\ " est sous
licence is `Creative Commons Attribution-ShareAlike
3.0 <http://creativecommons.org/licenses/by-sa/3.0/>`__. Les codes
d'exemples du guide sont abandonnés au domaine public.

