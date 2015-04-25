
#include <primitive_scheduler.h>

PrimitiveScheduler example_schedule;

void setup()
{
  Serial.begin(9600);
  
  example_schedule.addTask(do_something,500);
  example_schedule.addTask(print_stuff,1000);
  example_schedule.addTask(wait_89,125);
  example_schedule.addTask(wait_32,750);
}


void loop()
{
  example_schedule.run();
}


void do_something (void)
{
  double top = 859.45;
  double bottom = 53.72;
  
  Serial.print(top/bottom);
}


void print_stuff(void)
{
  int i;
  
  for(i = 0; i < example_schedule.getTaskCount(); i++)
  {
    Serial.println(example_schedule.getTaskExecutionTime(i));
  
  }
  
}


void wait_89 (void)
{

  delay(89);

}


void wait_32 (void)
{

  delay(89);

}

