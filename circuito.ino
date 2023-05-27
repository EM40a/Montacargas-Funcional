#define BOTON_FRENAR 16  // A2
#define BOTON_BAJAR 15  // A1
#define BOTON_SUBIR 14 // A0
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

int pisoActual = 0;
bool estaEnMovimiento = false;

void setup()
{
  for (int i = 5; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BOTON_SUBIR, INPUT_PULLUP);
  pinMode(BOTON_BAJAR, INPUT_PULLUP);
  pinMode(BOTON_FRENAR, INPUT_PULLUP);
  Serial.begin(9600); // Inicializo el puerto Serial
}

void loop()
{
  if (digitalRead(BOTON_SUBIR) == LOW) {
    controlarMontacargas("Subir");
  }
  if (digitalRead(BOTON_BAJAR) == LOW) {
    controlarMontacargas("Bajar");
  }
  if (digitalRead(BOTON_FRENAR) == LOW) {
    frenarMontacargas();
  }
}

void controlarMontacargas(String modo)
{
  if (estaEnMovimiento) {
    encenderluzDeMovimiento(estaEnMovimiento);
    delay(3000);

    if (modo == "Subir") {
      [](){(pisoActual < 9) ? pisoActual++ : estaEnMovimiento == false;}();
    } 
    
    else if (modo == "Bajar") {
      [](){(pisoActual > 0) ? pisoActual-- : estaEnMovimiento == false;}();
    }

    informarEstado(pisoActual);
    encenderluzDeMovimiento(false);
  }
}

void frenarMontacargas()
{
  informarEstado(pisoActual);
  (!estaEnMovimiento) ? estaEnMovimiento = true : estaEnMovimiento = false;
  delay(100); //Para evitar el rebote del loop
}

void informarEstado(int piso)
{
  ImprimirPiso(piso);
  CuentaRegresiva(piso);
}

void ImprimirPiso(int piso)
{
  Serial.print("Estás en el piso: ");
  Serial.println(piso);
}

void encenderluzDeMovimiento(bool prendeApaga)
{
  if (prendeApaga) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
  } else if (!prendeApaga) {
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_VERDE, LOW);    
  }
}

void ApagarPrender7Segmentos(int apagarPrender)
{
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