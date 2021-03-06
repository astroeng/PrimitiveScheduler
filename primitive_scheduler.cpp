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
#include <utilities.h>


PrimitiveScheduler::PrimitiveScheduler()
{
  PrimitiveScheduler(DEFAULT_TASK);
}
PrimitiveScheduler::PrimitiveScheduler(unsigned char num_tasks)
{
  task_count = num_tasks;

  taskInterval      = new unsigned long[task_count];
  taskExecutionTime = new unsigned long[task_count];
  taskLastExecution = new unsigned long[task_count];
  taskSkipped       = new unsigned long[task_count];

  tasks = new func_ptr[task_count];

  emptyPosition = 0;
  current_time = millis();
  interval_time = 0;
}

PrimitiveScheduler::~PrimitiveScheduler()
{
  delete[] taskInterval;
  delete[] taskExecutionTime;
  delete[] taskLastExecution;
  delete[] taskSkipped;
  delete[] tasks;
}

/* This function will add a task to the schedule. A function name should be
 * passed as the first parameter, the second parameter is the interval in
 * milliseconds that the function should be run.
 */
char PrimitiveScheduler::addTask(func_ptr new_func, unsigned long interval)
{

  if (emptyPosition < task_count)
  {
    tasks[emptyPosition]             = new_func;
    taskInterval[emptyPosition]      = interval;
    taskLastExecution[emptyPosition] = 0;
    taskExecutionTime[emptyPosition] = 0;
    taskSkipped[emptyPosition]       = 0;

    emptyPosition++;

    return ADD_SUCCESS;

  }
  return ADD_FAIL;

}

/* This will return the time from the scheduler's point of view.
 */
unsigned long PrimitiveScheduler::getTime()
{
  return current_time;
}

/* This will return how often the scheduler is called.
 */
unsigned long PrimitiveScheduler::getIntervalTime()
{
  return interval_time;
}

/* This will return the execution time of a particular task.
 */
unsigned long PrimitiveScheduler::getTaskExecutionTime(char i)
{
  return taskExecutionTime[i];
}

/* This will return the status of a task. If a task is skipped this
 * will be greater than 0, and set to the time the task ran over in
 * milliseconds. Once skipped a task will not be run again until reset.
 */
unsigned long PrimitiveScheduler::getTaskSkipped(char i)
{
  return taskSkipped[i];
}

/* This will return the current number of tasks.
 */
unsigned char PrimitiveScheduler::getTaskCount()
{
  return emptyPosition;
}

/* This will reset a task, effectively adding it back into the
 * schedule.
 */
void PrimitiveScheduler::resetTask(char i, int additional_time)
{
  taskInterval[i] += additional_time;
  taskSkipped[i] = 0;
}

/* This is the main part of the scheduler and should be called from the
 * Arduino loop function.
 */
void PrimitiveScheduler::run()
{

  unsigned long start_time;
  char i;

  /* Compute how long it has been since the last time the scheduler was run.
   */

  start_time = millis();
  interval_time = timeAge(start_time, current_time);
  current_time = start_time;

  /* Run through the array of "tasks" and run them. */

  for (i = 0; i < emptyPosition; i++)
  {

    /* Check to see if enough time has elapsed since the last time the
     * "task" was run. Also, make sure that the "task" is behaving. Basically
     * if the "task" takes 100ms to run and you tell it to run every 20ms
     * this will catch that and not run the "task".
     */

    start_time = millis();

    if ((taskLastExecution[i] + taskInterval[i]) <= start_time &&
        ((taskSkipped[i]>>2) < taskInterval[i]))
    {

      ((void (*)()) tasks[i])();

      taskLastExecution[i] = start_time;

      /* This delay is here as a debugging effort to try and figure
       * out why this sometimes reports 65535. The minimum value
       * should now always be 1.
       */
      /* TODO: figure this out and remove the delay. */
	    delay(1);

      taskExecutionTime[i] = timeAge(millis(), start_time);

    }

    /* If a "task" has been found to be misbehaving skip it and set the skipped
     * value to be the amount of time the task ran over.
     */

    else if (taskExecutionTime[i] >= taskInterval[i])
    {

      taskSkipped[i] += (taskExecutionTime[i] - taskInterval[i]);

    }

  }

}
