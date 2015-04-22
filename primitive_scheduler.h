/*************************************************************
 * Derek Schacht
 * 2015/04/21
 *
 * *** Use Statement and License ***
 * Free for non commercial use! Anything else is not authorized without consent.
 *  Contact [dschacht ( - at - ) gmail ( - dot - ) com] for use questions.
 *************************************************************
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
  void run();
  
private:

  unsigned long current_time;
  unsigned long taskInterval[MAX_TASK];
  unsigned long taskLastExecution[MAX_TASK];
  func_ptr tasks[MAX_TASK];
  
  unsigned char emptyPosition;
};

#endif
