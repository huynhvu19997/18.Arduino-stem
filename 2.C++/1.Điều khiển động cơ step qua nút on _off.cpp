#include<Arduino.h>
#include <AccelStepper.h>
#include <Pushbutton.h>


AccelStepper stepper(AccelStepper::DRIVER, 9, 8); // STEP=9, DIR=8

Pushbutton but_stas(2);
Pushbutton but_stop(3);
// Trạng thái nút nhấn
int buttonRunState = 0;
int buttonStopState = 0;

// Biến kiểm tra trạng thái động cơ
bool isMotorRunning = false;

void setup() 
{
  // Khởi động Serial Monitor (tuỳ chọn để debug)
  Serial.begin(115200);
  // Thiết lập động cơ bước (TB6600)
  stepper.setMaxSpeed(2000);    // Tốc độ tối đa (steps/second)
  stepper.setSpeed(1000);
  stepper.setAcceleration(500); // Gia tốc (steps/second^2)  
}

  void loop()
{
  if (but_stas.getSingleDebouncedPress())
  {
    if (!isMotorRunning)
    {
      isMotorRunning = true;

    }
  }

  if (but_stop.getSingleDebouncedPress())
  {
    if (isMotorRunning)
    {
      isMotorRunning = false;
      stepper.stop();
    }
  }

  if (isMotorRunning)
  {
    stepper.setSpeed(1000);
    stepper.runSpeed();
  }  

}
