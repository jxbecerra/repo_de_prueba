parte_a.c
// Inclusión de bibliotecas
#include <biblioteca_necesaria.h>

// Definición de constantes para pines
#define PIN_SENSOR_TEMP A0
#define PIN_SENSOR_LUZ A1
#define PIN_POTENCIOMETRO A2
#define PIN_LED_ROJO 9
#define PIN_LED_AMARILLO 10
#define PIN_LED_VERDE 11
#define PIN_BUZZER 8
#define PIN_BOTON_MODO 2

// Definición de constantes para umbrales (valores iniciales)
#define TEMP_MIN 20
#define TEMP_MAX 30
#define LUZ_MIN 300
#define LUZ_MAX 700

// Definición de constantes para intervalos de tiempo
#define INTERVALO_LECTURA 1000   // 1 segundo entre lecturas
#define INTERVALO_ALARMA 500     // 0.5 segundos para parpadeo

// Declaración de variables globales
int valorTemperatura = 0;        // Valor leído del sensor de temperatura
int valorLuz = 0;                // Valor leído del sensor de luz
int valorPotenciometro = 0;      // Valor leído del potenciómetro
float temperaturaCelsius = 0.0;  // Temperatura convertida a grados Celsius
unsigned int nivelLuz = 0;       // Nivel de luz en porcentaje
int umbralTemperatura = 25;      // Umbral ajustable de temperatura

// Variables para control de tiempo (tipo unsigned long para evitar overflow)
unsigned long tiempoUltimaLectura = 0;
unsigned long tiempoUltimaAlarma = 0;

// Variables de estado
volatile byte modoOperacion = 0;  // Modo de operación (se modificará en interrupciones)
bool estadoAlarma = false;        // Estado actual del LED/buzzer de alarma
bool alarmaActivada = false;      // Indica si hay condición de alarma

// Función de configuración
void setup() {
    // Inicialización de comunicación serial
    Serial.begin(9600);
    
    // Configuración de pines de entrada
    pinMode(PIN_SENSOR_TEMP, INPUT);
    pinMode(PIN_SENSOR_LUZ, INPUT);
    pinMode(PIN_POTENCIOMETRO, INPUT);
    pinMode(PIN_BOTON_MODO, INPUT_PULLUP);  // Con resistencia pull-up interna
    
    // Configuración de pines de salida
    pinMode(PIN_LED_ROJO, OUTPUT);
    pinMode(PIN_LED_AMARILLO, OUTPUT);
    pinMode(PIN_LED_VERDE, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    
    // Configuración de interrupción para cambio de modo
    attachInterrupt(digitalPinToInterrupt(PIN_BOTON_MODO), cambiarModo, FALLING);
    
    // Mensaje inicial
    Serial.println("Sistema de Monitoreo y Control Ambiental");
    Serial.println("----------------------------------------");
    Serial.println("Modos de operación:");
    Serial.println("0: Monitoreo de temperatura");
    Serial.println("1: Monitoreo de luminosidad");
    Serial.println("2: Modo combinado");
    Serial.println("----------------------------------------");
}
