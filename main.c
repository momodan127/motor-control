#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <avr/interrupt.h>

#define ADC_PIN 0

int orientation;
int direction;

//function prototypes
void init_PWM(void);

//movement control
void forward(void); //1
void backwards(void); //2
void left(void); //3
void right(void); //4
void Left_diagonal_forward(void); //5
void left_diagonal_backwards(void); //6
void right_diagonal_forward(void); //7
void right_diagonal_backwards(void); //8
void brake(void);

int main()
{

  uart_init();
  io_redirect();
  init_PWM();
  
  DDRD |= (1<<PD6); // set as output
  
  DDRC = 0x00; // settin all to input, for virtual GND
  DDRB = 0x00;

  PORTD |= (1<<PD6); // set all but PD6 to low

//control for the 2 left side motors
  //DDRC |= ((1<<PC5) | (1<<PC4)); //wheel 1
  //DDRC |= ((1<<PC3) | (1<<PC2)); //wheel 2
  PORTC |= 0x00; // turn all low

// control for the 2 right side motors
  //DDRB |= ((1<<PB1) | (1<<PB2)); //wheel 3
  //DDRB |= ((1<<PB3) | (1<<PB4)); //wheel 4
  PORTB |= 0x00;

  while(1)
  {


    printf("what direction?\n");
    scanf("%d", &direction);

    if (direction == 1)
    {
      forward();
      _delay_ms(10000); // time it actually has to run

      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }

    if(direction == 2)
    {
      backwards();
      _delay_ms(2000); // time it acutally has to run
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }

    if(direction == 3)
    {
      left();
      _delay_ms(2000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }
    if(direction == 4)
    {
      right();
      _delay_ms(2000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }
    if(direction == 5)
    {
      Left_diagonal_forward();
      _delay_ms(2000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }
    if(direction == 6)
    {
      left_diagonal_backwards();
      _delay_ms(2000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }
    if(direction == 7)
    {
      right_diagonal_forward();
      _delay_ms(2000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }
    if(direction == 8)
    {
      right_diagonal_backwards();
      _delay_ms(2000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }

    if(direction == 9)
    {
      forward();
      _delay_ms(2000);
      brake();
      _delay_ms(1000);
      PORTC = 0x00;
      PORTB = 0x00;

      DDRC = 0x00;
      DDRB = 0x00;
    }

  }

}

void init_PWM(void)
{
// enable PWM on timer 1
TCCR0A |= (1<<WGM00);

//start timer, and prescaler 8
TCCR0B |= (1<<CS02) | (1<<CS01);

// set desired target value
OCR0A = 5;  // PWM speed
}

void forward(void)
{
  //all wheels turning forward
  DDRC |= ((1<<PC2) | (1<<PC4));
  DDRB |= ((1<<PB4) | (1<<PB2));

  PORTC ^= (1<<PC2);
  PORTC ^= (1<<PC4);
  PORTB ^= (1<<PB4);
  PORTB ^= (1<<PB2);
}

void backwards(void)
{
  //all wheels turning backwards
  DDRC |= ((1<<PC3) | (1<<PC5));
  DDRB |= ((1<<PB1) | (1<<PB3));

  PORTC ^= ((1<<PC3) | (1<<PC5));
  PORTB ^= ((1<<PB1) | (1<<PB3));
}

void left(void)
{
  //wheel 1 & 4 forwards
  //wheel 2 & 3 backwards

  DDRC |= ((1<<PC5) |(1<<PC2));
  DDRB |= ((1<<PB1) | (1<<PB4));

  PORTC ^= ((1<<PC5) | (1<<PC2));
  PORTB ^= ((1<<PB1) | (1<<PB4));
}

void right(void)
{
  //wheel 1 & 4 backwards
  //wheel 2 & 3 forwards

  DDRC |= ((1<<PC4) | (1<<PC3));
  DDRB |= ((1<<PB1) | (1<<PB4));

  PORTC ^= ((1<<PC4) | (1<<PC3));
  PORTB ^= ((1<<PB1) | (1<<PB4));
}

void Left_diagonal_forward(void)
{
  //wheel 2 & 3 forwards

  DDRC |= (1<<PC2);
  DDRB |= (1<<PB2);

  PORTC ^= (1<<PC2);
  PORTB ^= (1<<PB2);
}

void left_diagonal_backwards(void)
{
  //wheel 1 & 4 backwards
  DDRC |= (1<<PC5);
  DDRB |= (1<<PB3);

  PORTC ^= (1<<PC5);
  PORTB ^= (1<<PB3);
}

void right_diagonal_forward(void)
{
  //wheel 1 & 4 forwards

  DDRC |= (1<<PC4);
  DDRB |= (1<<PB4);

  PORTC ^= (1<<PC4);
  PORTB ^= (1<<PB4);
}

void right_diagonal_backwards(void)
{
  //wheel 2 & 3 backwards

  DDRC |= (1<<PC3);
  DDRB |= (1<<PB1);

  PORTC ^= (1<<PC3);
  PORTB ^= (1<<PB1);
}

void brake(void)
{
  //turn on all pins

  DDRC |= ((1<<PC5) | (1<<PC4) | (1<<PC3) | (1<<PC2));
  DDRB |= ((1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4));

  PORTC ^= ((1<<PC5) | (1<<PC4) | (1<<PC3) | (1<<PC2));
  PORTB ^= ((1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4));
}