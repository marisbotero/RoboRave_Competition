
int infraPin1 = 10;    // pin del infrarrojos utilizado como entrada digital en el lado izquierdo(#1).
int infraPin2 = 11;    // pin del infrarrojos utilizado como entrada digital en el lado derecho(#2).
int valorInfra1 = 0;  // Valor inicial de la lectura digital del infrarrojos #1.
int valorInfra2 = 0;  // Valor inicial de la lectura digital del infrarrojos #2.
int OUTPUT4 = 4;    // Output4 conectada al pin 4.
int OUTPUT3 = 3;    // Ouput3 conectada al pin 3.
int OUTPUT2 = 6;    // Output3 conectada al pin 6.
int OUTPUT1 = 7;    // Output4 conectada al pin 7.
void setup() { 
  Serial.begin(9600); // Comenzamos comunicacion serial.
  pinMode(infraPin1, INPUT);     // Inicializa el pin 1 como entrada digital.
  pinMode(infraPin2, INPUT);     // Inicializa el pin 2 como entrada digital.
  pinMode (OUTPUT1, OUTPUT);     // Inicializa el pin 7  como entrada digital.
  pinMode (OUTPUT2, OUTPUT);     // Inicializa el pin 6 como entrada digital.
  pinMode (OUTPUT3, OUTPUT);     // Inicializa el pin 3 como entrada digital.
  pinMode (OUTPUT4, OUTPUT);     // Inicializa el pin 4 como entrada digital.  
  } 
void loop() { 
  valorInfra1 = digitalRead(infraPin1);   // Lee el valor de la entrada 10, esto es, el valor que lee el infrarrojos #1.
  Serial.println(valorInfra1);    //Imprimimos la lectura del infrarrojos #1.
  valorInfra2 = digitalRead(infraPin2);    // Lee el valor de la entrada 11, esto es, el valor que lee el infrarrojos #2.
  Serial.println(valorInfra2);    //Imprimimos la lectura del infrarrojos #2.
  if(valorInfra1==0)   // Si la lectura del infrarrojos#1 es 0, entonces se cumplira una de las siguientes condiciones:
  {
  if(valorInfra2==0)  // Si la lectura del infrarrojos#2 es 0, es decir los dos sensores estan sobre la linea negra, entonces los dos motores avanzaran en linea recta.
  {
  digitalWrite(OUTPUT1,0);
  digitalWrite(OUTPUT2,1);
  digitalWrite(OUTPUT3,1);
  digitalWrite(OUTPUT4,0); 
  }
  else // Si la lectura del infrarrojos#2 es 1, el sensor#1 esta sobre la linea negra y el sensor#2 esta fuera de la linea negra, entonces solo una rueda gira y esto causara el giro.
  {
  digitalWrite(OUTPUT1,0);
  digitalWrite(OUTPUT2,0);
  digitalWrite(OUTPUT3,1);
  digitalWrite(OUTPUT4,0); 
  }
  }
  else // Si la lectura del infrarrojos#1 no es 0, sera 1, se daran las siguientes posibilidades:
  {if(valorInfra2==0)  // Como el sensor#1 esta fuera de la linea negra y el sensor#2 esta sobre la linea negra, entonces solo una rueda gira y esto causara el giro.
  {
  digitalWrite(OUTPUT3,0);
  digitalWrite(OUTPUT4,0);
  digitalWrite(OUTPUT1,0);
  digitalWrite(OUTPUT2,1);
  }
  else{ // si ambos sensores dan lectura 1, los dos estan fuera de la linea negra, para que vuelva a su trayectoria tiene que retroceder.
  digitalWrite(OUTPUT1,1);
  digitalWrite(OUTPUT2,0);
  digitalWrite(OUTPUT3,0);
  digitalWrite(OUTPUT4,1);
  } 
  }
  }

