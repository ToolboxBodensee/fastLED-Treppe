# Momentan läuft nicht dieser code, sondern der hier: [ToolboxBodensee/McLighting-Treppe](https://gitlab.com/ToolboxBodensee/die-erleuchteten/McLighting)

**Entwicklung nur auf [GitLab](https://gitlab.com/ToolboxBodensee/die-erleuchteten/fastLED-Treppe). Auf GitHub befindet sich lediglich ein Mirror**

# fastLED-Treppe
Code für die Steuerung der LEDs, die in der treppe in den 1. Stock eingebaut sind.

Für das Projekt wird die **FastLED** Library mit den grundlagen des "XY MATRIX" beispiels verwendet. 


### Hardware:
- Die LEDs auf der Treppe bilden eine **11x17** Matrix, verbunden in einer Schlangenform.
- Es sind **WS2811** LED-Streifen verbaut mit **30 LEDs/Meter**.
- Die Kontrolle übernimmt ein ESP8266, der oberhalb der Treppe befestigt ist.
- Die Stromversorgung regelt ein **12V 3A Netzteil**, dass sich ebenfalls oberhalb der Treppe befindet... Und ja, 3A sind eigentlich nicht ausreichend, wenn man wirklich sicher gehen möchte... deshalb sollten **NICHT alle LEDs gleichzeitig in Weiß leuchten!**

### Arduino-Pinbelegung:


- VIN: 12V Stromversorgung
- GND: GND..
