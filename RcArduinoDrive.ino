unsigned long timer[5];
byte last_channel[4];
int input[4];
int motor[2];

long loop_timer; // Loop timer to set at 50Hz

int IN1=8;
int IN2=9;
int ENA=3;

int IN3=10;
int IN4=11;
int ENB=4;

void motor_drive(int V, int W){
      if ((velocityXcmd != 0 || velocityXcmd != -0) && (velocityZcmd != 0 || velocityZcmd != -0))
  {
    vZ = velocityZcmd/2;
    
    cmdA = velocityXcmd - vZ;
    if (cmdA > 1)
      cmdA = 1;
    else if(cmdA < -1)
      cmdA = -1;

    cmdB = velocityXcmd + vZ;
    if (cmdB > 1)
      cmdB = 1;
    else if (cmdB < -1)
      cmdB = -1;
    
    cout << "cA: ";
  }
  else 
  {
    cmdA = velocityXcmd - velocityZcmd;
    cmdB = velocityXcmd + velocityZcmd;
    cout << "cB: "; 
  }

  phi_l = max_wheel_rot*cmdA;
  phi_r = max_wheel_rot*cmdB;   
  
  cout << "L_Motor: "<< phi_l <<  "\tR_Motor: " << phi_r << endl;
}

void setup() {
  // put your setup code here, to run once:
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0); // Mega pin 53
  PCMSK0 |= (1 << PCINT1); // Mega pin 52
  PCMSK0 |= (1 << PCINT2); // Mega pin 51
  PCMSK0 |= (1 << PCINT3); // Mega pin 50
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT); 
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  loop_timer = millis()+20;
  // put your main code here, to run repeatedly:
//  print();


  while(millis()-loop_timer<0); //50hz update rate. 
}


ISR(PCINT0_vect)
{
//  Serial.println("interrupt");
  timer[0] = micros();

  // CH1
  if(last_channel[0] == 0 && PINB & B00000001){
    last_channel[0] = 1;
    timer[1] = timer[0];
  }
  else if(last_channel[0] == 1 && !(PINB & B00000001)){
    last_channel[0] = 0;
    input[0] = timer[0] - timer[1];
  }

  // CH2
  if(last_channel[1] == 0 && PINB & B00000010){
    last_channel[1] = 1;
    timer[2] = timer[0];
  }
  else if(last_channel[1] == 1 && !(PINB & B00000010)){
    last_channel[1] = 0;
    input[1] = timer[0] - timer[2];
  }

  // CH3
  if(last_channel[2] == 0 && PINB & B00000100){
    last_channel[2] = 1;
    timer[3] = timer[0];
  }
  else if(last_channel[2] == 1 && !(PINB & B00000100)){
    last_channel[2] = 0;
    input[2] = timer[0] - timer[3];
  }

  // CH1
  if(last_channel[3] == 0 && PINB & B00001000){
    last_channel[3] = 1;
    timer[4] = timer[0];
  }
  else if(last_channel[3] == 1 && !(PINB & B00001000)){
    last_channel[3] = 0;
    input[3] = timer[0] - timer[4];
  }
 
}
