#include <Arduino.h>
#include <TimerOne.h>

// Define the maximum number of tasks that can be scheduled
#define MAX_TASKS 10

// Structure to represent a task
struct Task {
  void (*task)(void);
  unsigned long period;     // Period of the task in milliseconds
  unsigned long deadline;   // Deadline of the task in milliseconds
  unsigned long last_time;  // Last execution time of the task in milliseconds
  byte led_pin;             // Pin of the LED used to indicate task overrun
};

// Array to hold the list of tasks
Task tasks[MAX_TASKS];

// Index of the highest priority task that is currently running
byte current_task;

// Define the interrupt service routine for the timer
void timer_isr() {
  // Disable interrupts to avoid nested interrupts
  noInterrupts();

  // Get the current time in milliseconds
  unsigned long current_time = millis();

  // Check if any task has missed its deadline
  for (byte i = 0; i < MAX_TASKS; i++) {
    if (current_time >= tasks[i].deadline) {
      // Task has missed its deadline, turn on the LED
      digitalWrite(tasks[i].led_pin, HIGH);
    }
  }

  // Switch to the next highest priority task
  byte next_task = current_task;
  for (byte i = 0; i < MAX_TASKS; i++) {
    next_task = (next_task + 1) % MAX_TASKS;
    if (current_time >= tasks[next_task].last_time + tasks[next_task].period) {
      // Task is ready to run, update its deadline and last time
      tasks[next_task].deadline = current_time + tasks[next_task].period;
      tasks[next_task].last_time = current_time;
      tasks[next_task].task();

      // Switch to the new task and turn off the LED
      digitalWrite(tasks[current_task].led_pin, LOW);
      current_task = next_task;
      digitalWrite(tasks[current_task].led_pin, LOW);

      // Break out of the loop
      break;
    }
  }

  // Enable interrupts again
  interrupts();
}

void testTask(){
    Serial.println("FUCK Asier");
}

void setup() {
    tasks[0] = Task{
        .task = &testTask,
        .period = 1000,
        .deadline = 2,
        .last_time = 0,
    } ;
    
    Serial.begin(9600);
  // Initialize the LED pins and turn them off
  for (byte i = 0; i < MAX_TASKS; i++) {
    pinMode(tasks[i].led_pin, OUTPUT);
    digitalWrite(tasks[i].led_pin, LOW);
  }

  // Initialize the timer to trigger the interrupt every millisecond
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timer_isr);
}

void loop() {
  // Add your code here to perform the tasks
  // Each task should not block for more than its period
}
