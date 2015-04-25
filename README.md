# PrimitiveScheduler
## Description

Small library that brings super basic scheduling to the Arduino platform. This scheduler does not use interrupts and is not preemptive. This scheduler will gracefully handle and detect “tasks” that hog CPU time, and disable them. A disabled task may be reenabled (reset) but will probably get disabled again unless the schedule is modified. The scheduler collects basic statistics about each “task” and exposes them to the user.

## Installation

Copy the project directory to the library folder in the Arduino working directory.

## Use Details

To use this library the user must create a schedule object and then add tasks to the schedule. The tasks are local functions that are defined in the sketch and passed to the schedule with the addTask function.

### Example

In the main body of the sketch:  

``#include <primitive_scheduler.h> /* Include the schedule library``  
``PrimitiveScheduler schedule; /* Declare a schedule.``  

In the setup function of the sketch:  

``schedule.addTask(do_something, 125) /* Add ‘do_something’ to the schedule and run every 125ms’’  

In the loop function of the sketch:  

``schedule.run() /* run the schedule’’  

At this point the scheduler will start collecting stats on each of the tasks that execute as well as statistics about the scheduler itself.




