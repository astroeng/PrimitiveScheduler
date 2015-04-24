/*************************************************************
 * Derek Schacht
 * 2015/04/21
 *
 * *** Use Statement and License ***
 * Free for non commercial use! Anything else is not authorized without consent.
 *  Contact [dschacht ( - at - ) gmail ( - dot - ) com] for use questions.
 *************************************************************
 */


/* This is a primitive scheduler for the Arduino platform. It is very
 * basic only allowing a few tasks to be run on a given periodicity. The
 * period is not guarateed since the shortest interval is dictated by 
 * the execution time of all of the schedule tasks. If the first task
 * is supposed to run every 10ms but the second task takes 30ms to 
 * perform it's job then the first task will be delayed by 30ms. However,
 * if a task is setup to run every 15ms and really takes 20ms to execute.
 * Then this scheduler will ignore the task until it is reset.
 * 
 * This scheduler is not preemptive!
 * This scheduler has no concept of priority!
 * This scheduler will "kill" a misbehaving task!
 * This scheduler is simple and crude!!
 * This scheduler makes it very simple to read IO on a schedule.
 */

#ifndef PRIMITIVE_SCHEDULER_H
#define PRIMITIVE_SCHEDULER_H

#define MAX_TASK 6

#define ADD_SUCCESS 1
#define ADD_FAIL    0

typedef void (*func_ptr)();

class PrimitiveScheduler
{
public:
  PrimitiveScheduler();

  char addTask(func_ptr new_func, unsigned long interval);
  unsigned long getTime();
  unsigned long getIntervalTime();
  unsigned long getTaskExecutionTime(char i);
  unsigned long getTaskSkipped(char i);
  unsigned char getTaskCount();

  void resetTask(char i, int additional_time);
  void run();
  
private:

  unsigned long current_time;
  unsigned long interval_time;
  unsigned long taskInterval[MAX_TASK];
  unsigned long taskExecutionTime[MAX_TASK];
  unsigned long taskLastExecution[MAX_TASK];
  unsigned long taskSkipped[MAX_TASK];
  
  func_ptr tasks[MAX_TASK];
  
  unsigned char emptyPosition;

};

#endif
