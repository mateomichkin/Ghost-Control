

#include <IRremote.hpp>

// ===============================
// PINES
// ===============================

#define IR_RECEIVE_PIN 27
#define IR_SEND_PIN 4
#define BUTTON_PIN 5


// ===============================
// VARIABLES DEL BOTÓN
// ===============================

bool estadoAnterior = HIGH;
unsigned long ultimoCambio = 0;

const unsigned long DEBOUNCE = 50;


// ===============================
// SETUP
// ===============================

void setup() {

Serial.begin(115200);

// Botón
pinMode(BUTTON_PIN, INPUT_PULLUP);

// Iniciar emisor y receptor
IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
IrSender.begin(IR_SEND_PIN);

Serial.println();
Serial.println("==============================");
Serial.println("ESP32 - EMISOR / RECEPTOR IR");
Serial.println("==============================");
Serial.println("Esperando señal IR o botón...");
}


// ===============================
// ENVIAR POWER
// ===============================

void enviarPower() {

Serial.println("ENVIANDO POWER...");

IrSender.sendNEC(0x3000, 0x02, 0);

Serial.println("POWER ENVIADO");
}


// ===============================
// LOOP
// ===============================

void loop() {

// --------------------------------
// RECEPCIÓN IR
// --------------------------------

if (IrReceiver.decode()) {

Serial.println();
Serial.println(">>> SEÑAL RECIBIDA <<<");

IrReceiver.printIRResultShort(&Serial);

Serial.print("Address: 0x");
Serial.println(IrReceiver.decodedIRData.address, HEX);

Serial.print("Command: 0x");
Serial.println(IrReceiver.decodedIRData.command, HEX);

IrReceiver.resume();
}


// --------------------------------
// BOTÓN
// --------------------------------

bool estadoActual = digitalRead(BUTTON_PIN);

if (estadoActual != estadoAnterior) {
ultimoCambio = millis();
}

if (millis() - ultimoCambio > DEBOUNCE) {

if (estadoActual == LOW && estadoAnterior == HIGH) {
enviarPower();
}
}

estadoAnterior = estadoActual;
}


	