===============================================
Message des modules SimpleBee pour Open The Box
===============================================

Principe
--------

Les messages sont émis en caractère imprimable, Tous les modules les reçoivent et doivent donc veiller à leur bonne interprétation.


Message d’identification
------------------------

**Attention ce type de message n'est pas utilisé par l'implementation de Open The Box**. 

Il faut arbitrairement allouer une adresse dans le device et
donc faire attention de ne pas allouer plusieurs fois la même adresse.

Les modules neuf ont une adresse ‘0000’ et restent muets à la mise sous
tension.

Après demande d'adresse, si la réponse est correcte, il fonctionne normalement et commence à
envoyer des données. L’adresse est conservée dans le module et celui-ci
fonctionnera normalement à une prochaine mise sous tension.

Message :
 * ‘\ **I**\ ’ pour identification
 * ‘\ **C**\ xxx’ ou ‘\ **A**\ xxx’ ‘C’ pour capteur, ‘A’ pour actionneur, xxx type de module ‘000’ à ‘999’
 * ‘xx’ xx = checksum
 * ‘\ **\\r’** fin de message

**Modules actuels :**

+-----------------------------+-----------------+
| C001 bouton poussoir        | A001 Led simple |
+-----------------------------+-----------------+
| C002 interrupteur           | A002 Sandtimer  |
+-----------------------------+-----------------+
| C003 détecteur de mouvement |                 |
+-----------------------------+-----------------+
| C004 détecteur lumière      |                 |
+-----------------------------+-----------------+
| C005 capteur température    |                 |
+-----------------------------+-----------------+
| C006 capteur présence       |                 |
+-----------------------------+-----------------+

 
Réponse :
 * ‘i’ identification
 * ‘xxxx’ adresse ‘0001’ à ‘9999’
 * ‘xx’ xx = checksum
 * ‘\ **\\r’** fin de message

Message watchdog
----------------

Les capteurs se signalent par un message toutes les minutes, si pas de
réponse, ils recommencent toutes les 2 secondes jusqu’à réponse
correcte.

Message :
 * ‘\ **W**\ ’ watchdog
 * ‘xxxx’ xxxx = adresse
 * ‘v’ v = état capteur
 * ‘\ **B**\ ’ B pour batterie
 * ‘v’ v valeur batterie 0(vide) à 9(pleine)
 * ‘Cxxx’ ou ‘Axxx’ type de capteur : Cxxx ou actionneur Axxx
 * ‘xx’ xx checksum
 * ‘\ **\\r’** fin de message

Réponse :
 * ‘\ **w**\ ’ watchdog
 * ‘xxxx’ adresse
 * ‘xx’ xx checksum
 * ‘\ **\\r’**

Message data
------------

Les capteurs envoient leur valeurs si changement d’état. Ils essayent
pendant 2 seconde jusqu’à obtenir un acquittement, sinon attendent le
prochain changement d’état.

Message :
 * ‘\ **D**\ ’ data
 * ‘xxxx’ adresse
 * ‘v’ valeur capteur
 * ‘\ **B**\ ’ B pour batterie
 * ‘v’ v valeur batterie 0(vide) à 9(pleine)
 * ‘Cxxx’ ou ‘Axxx’ type de capteur : Cxxx ou actionneur Axxx
 * ‘xx’ xx checksum
 * ‘\ **\\r’** fin de message

Réponse :
 * ‘\ **d**\ ’ data
 * ‘xxxx’ adresse
 * ‘xx’ xx checksum
 * ‘\ **\\r’** fin de message

Message request
---------------

Les actionneurs envoient toutes les 500 ms une requête, ils attendent
pendant 100 ms une réponse.

Message :
 * ‘\ **R**\ ’ request
 * ‘xxxx’ adresse
 * ‘v’ valeur actionneur
 * ‘\ **B**\ ’ B pour batterie
 * ‘v’ v valeur batterie 0(vide) à 9(pleine)
 * ‘Cxxx’ ou ‘Axxx’ type de capteur : Cxxx ou actionneur Axxx
 * ‘xx’ xx checksum
 * ‘\ **\\r’** fin de message

Réponse :
 * ‘\ **r**\ ’ request
 * ‘xxxx’ adresse
 * ‘v’ valeur actionneur désirée
 * ‘xx’ xx checksum
 * ‘\ **\\r’** fin de message

Calcul checksum
---------------

C’est la somme des octets précédent tronquée à 8 bit.

Le premier octet : (valeur >> 4) + 0x30

Le deuxième : (valeur & 0x0F) + 0x30

On obtient des valeurs comprises entre 0x30 et 0x3F.

Cette façon de faire est économe en code sur des petits
microcontrôleurs.

**Charge batterie :** il est préférable de couper les modules pour les
recharger.

La Led de charge s’éteint quand la batterie est pleine.

**Les réponses aux messages** sont impératives pour assurer un bon
fonctionnement.

Cela permet de réduire les renvois de messages, diminuer la consommation
des modules.

License
-------


Copyright (c) 2015 [Orange Labs]