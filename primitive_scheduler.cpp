/*************************************************************
 * Derek Schacht
 * 2015/04/21
 *
 * *** Use Statement and License ***
 * Free for non commercial use! Anything else is not authorized without consent.
 *  Contact [dschacht ( - at - ) gmail ( - dot - ) com] for use questions.
 *************************************************************
 */

#include <Arduino.h>
#include "primitive_scheduler.h"


PrimitiveScheduler::PrimitiveScheduler()
{
  emptyPosition = 0;
  current_time = millis();
}

char PrimitiveScheduler::addTask(void (*new_func)(), unsigned long interval)
{
  if (emptyPosition < MAX_TASK)
  {
    tasks[emptyPosition] = (int)new_func;
    taskInterval[emptyPosition] = interval;
  
    emptyPosition++;
    
    return ADD_SUCCESS;
  }
  return ADD_FAIL;
}


unsigned long PrimitiveScheduler::getTime()
{
  return current_time;
}


void PrimitiveScheduler::run()
{
  int i;
  current_time = millis();
  
  for (i = 0; i < emptyPosition; i++)
  {
    if ((taskLastExecution[i] + taskInterval[i]) <= current_time)
    {
      ((void (*)()) tasks[i])();
      taskLastExecution[i] = current_time;
    }
  }
}