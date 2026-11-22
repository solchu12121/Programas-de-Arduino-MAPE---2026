
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

#define NEGRO    0x0000
#define BLANCO   0xFFFF
#define ROJO     0xF800
#define VERDE    0x07E0
#define AMARILLO 0xFFE0
#define CIAN     0x07FF

const float PH_BAJO = 4.0;
const float PH_ALTO = 5.0;

int estadoAnterior = -1;
float ph = 0.0;
bool hayDato = false;

void dibujarEstado(int estado) {
  tft.fillRect(0, 170, 320, 50, NEGRO);
  tft.setTextSize(4);
  tft.setCursor(30, 175);

  if (estado == 0) {
    tft.setTextColor(AMARILLO);
    tft.print("PH BAJO");
  } else if (estado == 1) {
    tft.setTextColor(VERDE);
    tft.print("PH OPTIMO");
  } else {
    tft.setTextColor(ROJO);
    tft.print("PH ALTO");
  }
}

void setup() {
  Serial.begin(9600);

  uint16_t id = tft.readID();
  tft.begin(id);
  tft.setRotation(1);
  tft.fillScreen(NEGRO);

  tft.setTextColor(CIAN);
  tft.setTextSize(3);
  tft.setCursor(10, 10);
  tft.print("Huerta hidroponica");

  tft.setTextColor(BLANCO);
  tft.setTextSize(3);
  tft.setCursor(220, 100);
  tft.print("pH");

  tft.setTextColor(AMARILLO);
  tft.setTextSize(2);
  tft.setCursor(20, 200);
  tft.print("Esperando sensor...");
}

void loop() {
  // Recibir una linea enviada por el Arduino del sensor
  if (Serial.available()) {
    String dato = Serial.readStringUntil('\n');
    dato.trim();

    if (dato.length() > 0) {
      float nuevoPH = dato.toFloat();

      if (nuevoPH >= 0.0 && nuevoPH <= 14.0) {
        ph = nuevoPH;
        hayDato = true;
      }
    }
  }

  if (!hayDato) {
    return;
  }

  char texto[8];
  dtostrf(ph, 4, 1, texto);

  tft.setTextColor(BLANCO, NEGRO);
  tft.setTextSize(7);
  tft.setCursor(20, 80);
  tft.print(texto);

  int estado;

  if (ph < PH_BAJO) {
    estado = 0;
  } else if (ph > PH_ALTO) {
    estado = 2;
  } else {
    estado = 1;
  }

  if (estado != estadoAnterior) {
    dibujarEstado(estado);
    estadoAnterior = estado;
  }
}

