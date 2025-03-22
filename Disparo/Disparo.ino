#define ZERO_CROSS_PIN 2  // Pin de interrupción para cruce por cero
#define TRIAC_PIN 9       // Pin que activa el TRIAC
#define POT_PIN A0        // Potenciómetro para regular potencia

volatile bool zeroCrossDetected = false;

void zeroCrossInterrupt() {
    zeroCrossDetected = true; // Marca el cruce por cero
}

void setup() {
    pinMode(ZERO_CROSS_PIN, INPUT);
    pinMode(TRIAC_PIN, OUTPUT);
    pinMode(POT_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN), zeroCrossInterrupt, RISING);
}

void loop() {
    int potValue = analogRead(POT_PIN);  // Leer potenciómetro (0-1023)
    
    // Mapear a retardo adecuado (máximo 8.33ms en 60Hz o 10ms en 50Hz)
    int delayTime = map(potValue, 0, 1023, 9500, 500);  // Ajusta para 50Hz o 60Hz

    if (zeroCrossDetected) {
        delayMicroseconds(delayTime); // Ajuste del ángulo de fase
        digitalWrite(TRIAC_PIN, HIGH);
        delayMicroseconds(100);  // Pulso corto de disparo (ajustable)
        digitalWrite(TRIAC_PIN, LOW);
        zeroCrossDetected = false;
    }
}