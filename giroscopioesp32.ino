#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t IR_LED_PIN = 4;    // GPIO al transistor (Base vía R2)
const uint16_t BUTTON_PIN = 5;    // GPIO al pulsador

IRsend irsend(IR_LED_PIN);

bool estadoAnterior = HIGH;
unsigned long ultimoCambio = 0;
const unsigned long DEBOUNCE = 50; // ms

void setup() {
  Serial.begin(115200);
  irsend.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Listo. Apretá el botón para mandar POWER.");
}

void enviarPower() {
  uint32_t data = irsend.encodeNEC(0x3000, 0x2);
  irsend.sendNEC(data, 32);
  Serial.println("POWER enviado");
}

void loop() {
  bool estadoActual = digitalRead(BUTTON_PIN);

  // Detecta el flanco de bajada (botón presionado) con antirrebote
  if (estadoActual == LOW && estadoAnterior == HIGH) {
    if (millis() - ultimoCambio > DEBOUNCE) {
      enviarPower();
      ultimoCambio = millis();
    }
  }

  estadoAnterior = estadoActual;
  delay(10);
}