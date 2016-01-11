
#include <primitive_scheduler.h>

PrimitiveScheduler example_schedule(6);

double division;
double multiplication;
double add;
double subtract;

void setup()
{
  Serial.begin(9600);
  
  delay(2000);

  example_schedule.addTask(do_something,500);
  example_schedule.addTask(wait_89,120);
  example_schedule.addTask(wait_32,750);
  example_schedule.addTask(print_stuff,5000);

}


void loop()
{
  example_schedule.run();
}

/* A task that will do some math 
 */
void do_something (void)
{
  double top = 859.45;
  double bottom = 53.72;
  
  division = top / bottom;
  multiplication = top * bottom;
  add = top + bottom;
  subtract = top - bottom;
}

/* A task that will print stuff 
 */
void print_stuff(void)
{
  int i;
  
  Serial.print("Division       : ");
  Serial.println(division);
  
  Serial.print("Multiplication : ");
  Serial.println(multiplication);
  
  Serial.print("Addition       : ");
  Serial.println(add);
  
  Serial.print("Subtraction    : ");
  Serial.println(subtract);
  
  Serial.print("Schedule Interval : ");
  Serial.println(example_schedule.getIntervalTime());
  
  for(i = 0; i < example_schedule.getTaskCount(); i++)
  {
  
    Serial.print("Task # ");
    Serial.print(i);
    Serial.print(" eTime : ");
    Serial.println(example_schedule.getTaskExecutionTime(i));

  }
  
}

/* A task that will take 89ms to run 
 */
void wait_89 (void)
{

  delay(89);

}

/* A task that will take 32ms to run 
 */
void wait_32 (void)
{

  delay(32);

}

