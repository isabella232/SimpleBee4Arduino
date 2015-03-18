

Pour tester sans OpenTheBox
---------------------------

Vous devez avoir **Python 2.X** installé, et **pip**.
puis installer fysom:

.. code-block:: bash

   pip install fyson

Brancher le dongle/montage arduino maître sur le PC.

Utiliser le simulateur python **simplebee.py** OpenTheBox qui de trouve https://github.com/Orange-OpenSource/SimpleBee4Arduino/tree/master/tools

Avant d'utiliser le simulateur, il faut identifier le port sur lequel est branché le dongle/montage arduino maître (celà dépends de  l'OS).

Lancer le simulateur, par exemple sur linux:

.. code-block:: bash

   $python simplebee.py --debug --baudrate 57600 --port /dev/ttyACM0
   2015-03-18 11:11:56,563 - DEBUG simplebee - debug is on
   2015-03-18 11:11:56,564 - DEBUG simplebee - Reading on /dev/ttyACM0
   2015-03-18 11:13:54,500 - ERROR simplebee -   ->Unknown device 2002 auto provide11:13:54,500 - DEBUG simplebee - 2015-03-18 11:13:54,500 - DEBUG simplebee - Build that C {'typemodule': u'C002', 'addr': '2002', 'ser': Serial<id=0x7f934e4cea50, open=True>(port='/dev/ttyACM0', baudrate=57600, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False)}
   2015-03-18 11:13:54,501 - DEBUG simplebee - PseudoDevice {'typemodule': u'C002', 'addr': '2002', 'ser': Serial<id=0x7f934e4cea50, open=True>(port='/dev/ttyACM0', baudrate=57600, bytesize=8, parity='N', stopbits=1, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False)}
   2015-03-18 11:13:54,501 - DEBUG simplebee - Module of type C002 at address 2002 detected
   2015-03-18 11:13:54,502 - INFO simplebee -      [Identified 2002]
   2015-03-18 11:13:54,502 - INFO simplebee -      [new value from 2002]
   2015-03-18 11:13:54,502 - INFO simplebee -       {'batteryLevel': u'9', 'value': u'1'}
   2015-03-18 11:13:54,502 - INFO simplebee - -> send sensor ack event d20021
   2015-03-18 11:13:54,503 - INFO simplebee -      [Identified 2002]
   2015-03-18 11:13:54,811 - DEBUG simplebee - Mesg type='D' len=14 'D20020B9C00288'
   2015-03-18 11:13:54,812 - INFO simplebee -      [new value from 2002]
   2015-03-18 11:13:54,812 - INFO simplebee -       {'batteryLevel': u'9', 'value': u'0'}
   2015-03-18 11:13:54,812 - INFO simplebee - -> send sensor ack event d20020
   2015-03-18 11:13:54,813 - INFO simplebee -      [Identified 2002]
   
Le simulateur permet:
* de voir les messages des devices sur le canal/PANID configuré
* de répondre au messages des devices:
 * Les leds clignotes au rythme du hearbeat (par défaut 500 ms)
 * acquittement de message des buttons et interupteur
   
