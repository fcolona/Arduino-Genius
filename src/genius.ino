#define MAX 100
#define BR 13
#define BB 10
#define BY 8
#define BG 9
#define LY 2
#define LG 3
#define LB 4
#define LR 5
#define BUZZER 6

int on[4] = {0,0,0,0};

int sequencia[MAX];
int tam_sequencia = 0;
bool emjogo = false;
int atual = 0;
int perdeu = false;

void setup()
{
  //Inicializa os pins
  pinMode(BUZZER, OUTPUT);
  pinMode(BR, INPUT);
  pinMode(BB, INPUT);
  pinMode(BG, INPUT);
  pinMode(BY, INPUT);
  pinMode(LR, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(LG, OUTPUT);
  pinMode(LY, OUTPUT);
  //Inicializa a sequencia
  for(int i=0; i<MAX; i++){
    sequencia[i]=0;
  }
  Serial.begin(3600);
  randomSeed(analogRead(A1));
}

int detectarinput(void){
  //Inicializa os valores
  bool pressionou = false;
  int resposta = 0;
  //Loopa até um botão ser pressionado
  while(1){
    on[0] = digitalRead(BY);
    on[1] = digitalRead(BG);
    on[2] = digitalRead(BB);
    on[3] = digitalRead(BR);
    if(!pressionou){
      if(on[0] == HIGH){
        resposta = 0;
        pressionou = true;
        digitalWrite(resposta+2, HIGH);
      }
      else if(on[1] == HIGH){
        resposta = 1;
        pressionou = true;
        digitalWrite(resposta+2, HIGH);
      }
      else if(on[2] == HIGH){
        resposta = 2;
        pressionou = true;
        digitalWrite(resposta+2, HIGH);
      }
      else if(on[3] == HIGH){
        resposta = 3;
        pressionou = true;
        digitalWrite(resposta+2, HIGH);
      }
    }
    //Se deixou de pressionar quebra o loop
    if(pressionou && on[resposta] == LOW){
      digitalWrite(resposta+2, LOW);
      break;
    };

  }
  delay(10);
  return(resposta);
}

void loop(void)
{
  if(!emjogo){
    delay(1000);
    //Decide aleatoriamente qual LED irá acender
  	sequencia[tam_sequencia] = random(2,6);
    emjogo = true;
    for(int i = 0; i < tam_sequencia + 1; i++){
        //Acende o LED escolhido
      	digitalWrite(sequencia[i], HIGH);
        //Aciona o buzzer
        tone(6, sequencia[i] * 2000, 150);
        delay(300);
        //Apaga o resto dos LEDs
        digitalWrite(LB, LOW);
        digitalWrite(LR, LOW);
        digitalWrite(LY, LOW);
        digitalWrite(LG, LOW);
        if(i != tam_sequencia) delay(300);
    }
  }
  if(emjogo){
    //Obtém o pin do LED que foi pressionado
    int qpressionou = detectarinput() + 2; //O +2 é para transformar de índice para pin
    Serial.print(qpressionou);
    Serial.print("\n");
    //Liga o LED para dar um feedback visual
    tone(6, qpressionou * 2000, 150); //Aciona o buzzer para dar um feedback sonoro
    //Se o botão pressionado corresponder ao LED correto
    if(qpressionou == sequencia[atual]){
      	atual++;
    }else{
     //Se perdeu, reseta tudo e aciona o buzzer
      	perdeu = true;
        emjogo = false;
        atual = 0;
        tam_sequencia = 0;
      	for(int i=0; i<MAX; i++){
        	sequencia[i]=0;
      	}
        tone(6, 31, 700);
    }
    //Acaba a rodada
    if(atual == tam_sequencia + 1){
      	tam_sequencia++;
        emjogo = false;
        atual = 0;
    }
  }
  //Reseta os LEDs
  digitalWrite(LB, LOW);
  digitalWrite(LR, LOW);
  digitalWrite(LY, LOW);
  digitalWrite(LG, LOW);
  delay(10);
}