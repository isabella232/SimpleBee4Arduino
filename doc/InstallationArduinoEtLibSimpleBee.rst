=========================================
Installation Arduino et Lib SimpleBee4OTB
=========================================

Configuration de l'IDE |Arduinologo| avec pour l'utilisation du kit SimpleBee4OTB.

.. |OTBlogo| image:: http://openthebox.org/wp-content/uploads/2014/06/OB-Logo.png
.. |Arduinologo| image:: http://upload.wikimedia.org/wikipedia/commons/4/42/Arduino_Uno_logo.png
.. _Arduino: http://www.arduino.cc/

Références
----------
   * Le site arduino |Arduinologo| http://www.arduino.cc
   * La `bibliothèque XBee pour Arduino`_
   * `Arduino guide pour Xbee Shield`_
   * La bilibithèque Simple Bee pour OpenTheBox : `SimpleBee4OTB Release`_
   * `Xbee et Arduino , un tutorial <http://jeromeabel.net/ressources/xbee-arduino>`_
   
.. _`SimpleBee4OTB Release`: https://github.com/franckOL/XbeeTuto/releases/latest
.. _`Arduino guide pour Xbee Shield`: http://arduino.cc/en/Guide/ArduinoWirelessShield
.. _`bibliothèque XBee pour Arduino`: https://code.google.com/p/xbee-arduino/

Requirements
------------
   * |Arduinologo| IDE Arduino 1.6
   * une carte Arduino_ Uno
   * Arduino Wireless Proto Shield
   * un module XBee S1 de digi http://www.digi.com/products/wireless-wired-embedded-solutions/zigbee-rf-modules/xctu

   
Téléchargement et installation de |Arduinologo| IDE
---------------------------------------------------

Aller sur le site de Arduino_ et télécharge la dernière version en fonction de votre OS.

Installer selon l'OS:
   * `Windows <http://arduino.cc/en/Guide/Windows>`_
   * `Mac OS X <http://arduino.cc/en/Guide/MacOSX>`_
   * `Linux (on the playground wiki) <http://www.arduino.cc/playground/Learning/Linux>`_


Et lancer l'IDE:

|arduinoblink|

.. |arduinoblink| image::http://arduino.cc/en/uploads/Guide/Arduino1Blink.png 

Téléchargement et installation de la biliothèque XBee
-----------------------------------------------------

Aller sur le site de `bibliothèque XBee pour Arduino`_ et télécharge la dernière version (0.5 et +)

Dans l'IDE, aller dans croquis > Importer bibliothèque > Ajouter bibliothèque et selectionner le .zip téléchargé.

Dans croquis > Importer bibliothèque, vous avez maintenant la bibliothèque XBee et dans fichier > exemples > XBee, vous avez des exemples XBee.


Téléchargement et installation de la biliothèque SimpleBee4OTB
--------------------------------------------------------------

NYI


Hello Word ?
------------

NYI 

.. code-block:: c

   /** Sketch pour le maître
    * A flasher en enlevant le module XBee.
    **/
   void setup() {
   }
   
   void loop() {
   }
   
