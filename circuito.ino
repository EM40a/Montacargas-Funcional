#define BTN_FRENAR 16 // A2
#define BTN_BAJAR 15 // A1
#define BTN_SUBIR 14 // A0
#define LED_VERDE 13
#define LED_ROJO 12
// Cada letra representa una luz del display de 7 segmentos
#define a 11
#define b 10
#define c 9
#define d 8
#define e 7
#define f 5
#define g 6

int pisoActual;

void setup()
{
  for (int i = 5; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BTN_SUBIR, INPUT_PULLUP);
  pinMode(BTN_BAJAR, INPUT_PULLUP);
  pinMode(BTN_FRENAR, INPUT_PULLUP);

  Serial.begin(9600);
  pisoActual = 0;
}

void loop()
{
  // Si se detecta que alguno de los botones BTN_SUBIR o BTN_BAJAR está presionado
  if (digitalRead(BTN_SUBIR) == LOW || digitalRead(BTN_BAJAR) == LOW) {
    PrenderLedVerdeRoja(true);
    SubirBajarPiso();
    PrenderLedVerdeRoja(false);
  }

  if (digitalRead(BTN_FRENAR) == LOW) {
    PrenderLedVerdeRoja(false);
  }
}

void SubirBajarPiso() {
  if (digitalRead(BTN_SUBIR) == LOW) {
    SubirPiso();
  }
  else if (digitalRead(BTN_BAJAR) == LOW) {
    BajarPiso();
  }
}

void SubirPiso(){
  while(pisoActual < 10) {
    ImprimirPiso(pisoActual);
    CuentaRegresiva(pisoActual);
    delay(3000);
    pisoActual++;
  }
}

void BajarPiso(){
  while(pisoActual >= 0){
    ImprimirPiso(pisoActual);
    CuentaRegresiva(pisoActual);
    delay(3000);
    pisoActual--;
  }
}

void ImprimirPiso(int piso) {
  Serial.print("Estas en el piso: ");
  Serial.println(piso);
}

void PrenderLedVerdeRoja(bool estaEnMovimiento){
  if (estaEnMovimiento){
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  }

  else {
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_VERDE, LOW);    
  }
}

// La función apaga o enciende cada pin del display según el parámetro recibido
void ApagarPrender7Segmentos(int apagarPrender)
{
  // Un array con cada pin del display
  int segmentos[] = {a, b, c, d, e, f, g};
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentos[i], apagarPrender);
  }
}

void CuentaRegresiva(int numero)
{
  switch (numero) {
    case 0:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(g, LOW);
      break;
      
    case 1:
      ApagarPrender7Segmentos(LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
      
    case 2:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(c, LOW);
      digitalWrite(f, LOW);
      break;
      
    case 3:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      break;
      
    case 4:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(a, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      break;
      
    case 5:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(b, LOW);
      digitalWrite(e, LOW);
      break;
      
    case 6:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(b, LOW);
      break;
      
    case 7:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(g, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      break;
      
    case 8:
      ApagarPrender7Segmentos(HIGH);
      break;
      
    case 9:
      ApagarPrender7Segmentos(HIGH);
      digitalWrite(e, LOW);
      break;
  }
}
