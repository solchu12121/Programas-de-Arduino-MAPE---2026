
const int PIN_SENSOR = A5;

// Valores medidos con tus soluciones de calibración
const float V_PH686 = 1.2405;
const float PH_REF686 = 6.86;
const float V_PH4 = 1.701;
const float PH_REF4 = 4.00;

float leerVoltaje() {
  long suma = 0;

  for (int i = 0; i < 20; i++) {
    suma += analogRead(PIN_SENSOR);
    delay(5);
  }

  float promedio = suma / 20.0;
  return promedio * 5.0 / 1023.0;
}

float calcularPH(float voltaje) {
  float pendiente = (PH_REF4 - PH_REF686) /
                    (V_PH4 - V_PH686);

  float ph = PH_REF686 +
             pendiente * (voltaje - V_PH686);

  return constrain(ph, 0.0, 14.0);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltaje = leerVoltaje();
  float ph = calcularPH(voltaje);

  // Enviar solamente el pH al Arduino de la pantalla
  Serial.println(ph, 2);

  delay(500);
}


