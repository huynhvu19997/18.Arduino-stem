#include <Arduino.h>

//định nghĩa các chân
int buttonpin = 2; //chân nút nhấn
int potPin = A0; // chân biến trở
int ledPins[] = {3,4,5,6,7,8,9,10}; // các chân led
int numberofLeds = 8;  // số lượng led

int buttonState = 0;
int prevButtonState = HIGH;
int mode = 0; //chế độ hoạt động
unsigned long debounceTime = 50; // thời gian chống rung
unsigned long lastDebounceTime = 0;

void ledChaser(int potvalue);
void ledBrightness(int potvalue);
void ledBlink(int potvalue);
void turnOffLEDs() ;
void ledBlinkContinuous(int potValue);

void setup() 
{
  pinMode(buttonpin, INPUT_PULLUP);
  pinMode(potPin, INPUT);

  // cài đặt các chân LED 
  for (int i =0; i< numberofLeds;i++)
  {
    pinMode(ledPins[i],OUTPUT);
  }
}

void loop() 
{
  int readButton = digitalRead(buttonpin);
  
  // Xử lý chống rung nút nhấn
  if (readButton != prevButtonState) 
  {
    lastDebounceTime = millis();
  }
  if (((millis() - lastDebounceTime)) > debounceTime) 
  {
    if (readButton == LOW && prevButtonState == HIGH) 
    {
      mode = (mode + 1) % 4; // Thay đổi chế độ (mode). Có 4 trạng thái: 0, 1, 2, 3
    }
    prevButtonState = readButton;
  }

  // Đọc giá trị từ biến trở
  int potValue = analogRead(potPin);
  // Có 4 chế độ hoạt động
  switch (mode) 
  {
    case 0:
      ledChaser(potValue);
      break;
    case 1:
      ledBrightness(potValue);
      break;
    case 2:
      ledBlink(potValue);
      break;
    case 3:
      turnOffLEDs(); // Tắt LED và chờ chuyển sang chế độ tiếp theo
      break;
  }
}

// Chế độ LED đuổi với tốc độ phụ thuộc giá trị biến trở
void ledChaser(int potvalue)
{
  int delayTime = map(potvalue,0,1023,50,500);
  for (int i = 0; i < numberofLeds; i++)
  {
    digitalWrite(ledPins[i],HIGH);
    delay(delayTime);
    digitalWrite(ledPins[i],LOW);
    delay(delayTime);
  }
}

// Chế độ LED sáng tương ứng với giá trị biến trở chia cho 7
void ledBrightness(int potvalue)
{
  int activeLEDs = potvalue / 7; // Giá trị biến trở chia cho 7
  for (int i = 0; i < numberofLeds; i++) 
  {
    if (i < activeLEDs) 
    {
      digitalWrite(ledPins[i], HIGH); // Bật LED
    }
    else
    {
      digitalWrite(ledPins[i], LOW); // Tắt LED
    }
  }
}


// Chế độ LED sáng nhấp nháy với số LED tương ứng giá trị biến trở chia cho 8
void ledBlink(int potvalue)
{
  int activeLEDs = potvalue / 8; // Giá trị biến trở chia cho 8
  for (int j = 0; j < 5; j++) 
  {  // Nhấp nháy 5 lần
    for (int i = 0; i < numberofLeds; i++) 
    {
      if (i < activeLEDs) 
      {
        digitalWrite(ledPins[i], HIGH); // Bật LED nhấp nháy
      } 
      else 
      {
        digitalWrite(ledPins[i], LOW); // Tắt LED
      }
    }
    delay(200); // Delay cho trạng thái bật
    for (int i = 0; i < numberofLeds; i++) 
    {
      digitalWrite(ledPins[i], LOW); // Tắt tất cả LED
    }
    delay(200); // Delay cho trạng thái tắt
  }
}

// Chế độ tắt toàn bộ LED
void turnOffLEDs() 
{
  for (int i = 0; i < numberofLeds; i++) 
  {
    digitalWrite(ledPins[i], LOW); // Tắt tất cả LED
  }
}


void ledBlinkContinuous(int potValue) 
{
  int activeLEDs = potValue / 128;

  while (digitalRead(buttonpin) == HIGH) 
  { // Lặp đến khi nút nhấn được nhấn
    for (int i = 0; i < numberofLeds; i++) 
    {
      if (i < activeLEDs) 
      {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
    delay(300);
    for (int i = 0; i < numberofLeds; i++) 
    {
      digitalWrite(ledPins[i], LOW);
    }
    delay(300);
  }
}
