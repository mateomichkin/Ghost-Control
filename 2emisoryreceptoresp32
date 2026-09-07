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
bool estadoBotonEstable = HIGH;  // Guarda el último estado confirmado
bool ultimoEstadoLeido = HIGH;   // Guarda la lectura instantánea
unsigned long ultimoCambio = 0;
const unsigned long DEBOUNCE = 50;

// ===============================
// SETUP
// ===============================
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN);

  Serial.println("\n==============================");
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
    Serial.println("\n>>> SEÑAL RECIBIDA <<<");
    IrReceiver.printIRResultShort(&Serial);
    Serial.print("Address: 0x");
    Serial.println(IrReceiver.decodedIRData.address, HEX);
    Serial.print("Command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();
  }

  // --------------------------------
  // BOTÓN (Debounce Corregido)
  // --------------------------------
  bool lecturaActual = digitalRead(BUTTON_PIN);

  // Si el botón cambió por ruido o pulsación, reiniciamos el temporizador
  if (lecturaActual != ultimoEstadoLeido) {
    ultimoCambio = millis();
  }

  // Si pasó más tiempo que el DEBOUNCE, el estado es estable
  if ((millis() - ultimoCambio) > DEBOUNCE) {
    // Si el estado estable cambió respecto al que teníamos guardado
    if (lecturaActual != estadoBotonEstable) {
      estadoBotonEstable = lecturaActual;

      // Si el nuevo estado estable es LOW, significa que se presionó
      if (estadoBotonEstable == LOW) {
        enviarPower();
      }
    }
  }

  // Guardamos la lectura para comparar en la próxima vuelta
  ultimoEstadoLeido = lecturaActual;
}
