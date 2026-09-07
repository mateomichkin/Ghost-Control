#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

String ultimoEstado = "";

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);   // SDA, SCL

  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error al conectar el MPU6050");
    while (1);
  }

  Serial.println("MPU6050 listo");
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  String estado = "CENTRO";

  if (ax > 12000)
    estado = "ARRIBA";
  else if (ax < -12000)
    estado = "ABAJO";
  else if (ay > 12000)
    estado = "DERECHA";
  else if (ay < -12000)
    estado = "IZQUIERDA";

  if (estado != ultimoEstado) {
    ultimoEstado = estado;

    if (estado == "ARRIBA")
      Serial.println("Enviar ARRIBA");

    else if (estado == "ABAJO")
      Serial.println("Enviar ABAJO");

    else if (estado == "DERECHA")
      Serial.println("Enviar DERECHA");

    else if (estado == "IZQUIERDA")
      Serial.println("Enviar IZQUIERDA");
  }

  delay(100);
}