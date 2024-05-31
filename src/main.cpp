#include <Arduino.h>
#include <FastLED.h>

// Definir pines
#define LASER_PIN 3
#define LDR_PIN A0
#define LED_PIN 6

// Configuración de la tira LED
#define NUM_LEDS 50
#define BRIGHTNESS 150
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// Umbral para detectar la interrupción del láser
#define THRESHOLD 500

void lightSequence();

void setup()
{
  // Configurar el pin del láser como salida
  pinMode(LASER_PIN, OUTPUT);

  // Inicializar la comunicación serie para depuración
  Serial.begin(9600);

  // Configurar la tira LED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Encender el láser
  digitalWrite(LASER_PIN, HIGH);
}

void loop()
{
  // Leer el valor analógico de la fotorresistencia
  int sensorValue = analogRead(LDR_PIN);

  // Imprimir el valor en el monitor serie para depuración
  Serial.print("Valor del sensor: ");
  Serial.println(sensorValue);

  // Verificar si el valor del sensor está por debajo del umbral
  if (sensorValue > THRESHOLD)
  {
    // Ejecutar secuencia de luces
    lightSequence();
  }
  else
  {
    // Apagar la tira LED
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
  }

  // Esperar 100 ms antes de la próxima lectura
  delay(10);
}

// Función para ejecutar una secuencia de luces
void lightSequence()
{
  // Secuencia de luces
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(20); // Ajusta el tiempo de retardo según la velocidad deseada
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Green;
    FastLED.show();
    delay(20);
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(20);
  }
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(20);
  }
}
