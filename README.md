# Conexiones y Componentes

## Tabla 1: Conexiones del ESP32

| Componente       | Conexión                                          | Pin Arduino UNO / ESP32 | Observaciones                          |
|------------------|---------------------------------------------------|-------------------------|----------------------------------------|
| **Sensor PIR** | **VCC** &rarr; **Riel rojo** (5 V desde VIN del ESP32) |                         | **Alimentación** desde el riel de 5 V      |
|                  | **GND** &rarr; **Riel azul** (GND ESP32)          |                         | **Tierra común** |
|                  | **OUT** &rarr; Cable a **GPIO13** (ESP32)         | GPIO13                  | **Señal digital** al detectar **movimiento** |
| **Luz led** | **Ánodo** &rarr; **Resistencia 220&Omega;** &rarr; **GPIO 2** (ESP32) | GPIO 2 (ESP32)          | **Indicador visual de alarma** |
|                  | **Cátodo** &rarr; **GND** |                         | Conectado al **riel azul** |
| **Buzzer pasivo**| **Positivo** &rarr; **Colector transistor** |                         | **Controlado** por **GPIO 4** (ESP32)  |
|                  |                                                   | GPIO 4 (ESP32)          | **Activado** mediante **transistor NPN** |

## Tabla 2: Conexiones del Arduino UNO

| Componente       | Conexión                                                | Pin Arduino | Observaciones                                  |
|------------------|---------------------------------------------------------|-------------|------------------------------------------------|
| **Transistor NPN**| **Base** &rarr; **Resistencia 1K&Omega;** &rarr; **GPIO 4** (ESP32) | GPIO 4 (ESP32) | Permite **controlar buzzer** con **más potencia** |
|                  | **Emisor** &rarr; **GND** | GND         | **Tierra común** |
| **Arduino UNO** | **5V** &rarr; **Riel rojo** (desde VIN del ESP32)     | Pin 5V      | **Alimentado** por el **riel de 5 V** |
|                  | **GND** &rarr; **Riel azul** | GND         | **Tierra común con ESP32** |
|                  | **RX** &rarr; **TX ESP32** (con divisor resistivo)    | RX          | **Recibe datos UART** (ej. **IP del ESP32**)   |
| **LCD 16x2** | **VCC**, **GND**, **Rs**, **E**, **D4-D7**, **VO**, **RW** | Pines digitales del Arduino | **Modo paralelo** (sin **I2C**), usa ~6 pines + **control de contraste** |
