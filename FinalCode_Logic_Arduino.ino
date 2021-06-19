//Code by Satyam Pandey, Rishi Singh, Vamshi, Harsha
#define triac_gate   8
#define pot         A0
#define iot         A1
int ldr=0;
int app=0;
bool ZC = 0;
uint16_t alpha;
int value=0;

void setup(void) {
  pinMode(triac_gate, OUTPUT);
  digitalWrite(triac_gate, LOW);
  attachInterrupt(0, ZC_detect, CHANGE);       // Enable external interrupt (INT0)
}

void ZC_detect() {
  ZC = 1;
}

void loop() {

  if( ZC){
    if(alpha < 9500) {
      delayMicroseconds(alpha);
      digitalWrite(triac_gate, HIGH);
      delayMicroseconds(200);
      digitalWrite(triac_gate, LOW);
    }
    ZC = 0;

     ldr=analogRead(pot);
     app=analogRead(iot);
      if(app<60)
      {alpha=9000;
      }
     else if(app>660)
      {alpha=2000;
      }
      else if(app>140 && app<270)//sleep
      { if(ldr<780)
        alpha=alpha+1;
        else if(ldr>830)
        alpha=alpha-1;
        else
        {alpha=map(ldr,0,680,9600,0);
         if(alpha > 9500)
         alpha = 9500;
         }
       }
       else if(app>320 && app<440)//study
      { if(ldr<920)
        alpha=alpha+1;
        else if(ldr>980)
        alpha=alpha-1;
        else
        {alpha=map(ldr,0,680,9600,0);
         if(alpha > 9500)
         alpha = 9500;
         }
       }
      if(alpha > 9500)
      alpha = 9500;
      else if (alpha<0)
      alpha=0;
  }
}
