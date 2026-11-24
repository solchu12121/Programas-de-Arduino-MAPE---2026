
const int PIN_SENSOR = A5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long suma = 0;

  // Tomar 20 mediciones del sensor
  for (int i = 0; i < 20; i++) {
    suma += analogRead(PIN_SENSOR);
    delay(20);
  }

  // Calcular el promedio
  float lectura = suma / 20.0;

  // Convertir la lectura analógica a voltaje
  float voltaje = lectura * 5.0 / 1023.0;

  // Mostrar los resultados en el Monitor Serie
  Serial.print("Lectura analogica: ");
  Serial.println(lectura);

  Serial.print("Voltaje: ");
  Serial.print(voltaje, 3);
  Serial.println(" V");

  delay(1000);
}


