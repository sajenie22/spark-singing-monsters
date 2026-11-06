#ifndef SPARK_MOTOR_H
#define SPARK_MOTOR_H
 
#include <stdint.h>

public:
    // Set up and loop (get array from ece1)
    // set up runs once
    // loop and keep taking calls from the array
    // so do i just keep calling the wrapper func and see if its playing 
    // esp32 pwm so i dont take control of the cpu
    void run_character_movement();

private:
    void start_rocker_motor();
    void start_updown_motor();
    void start_turning_motor();


#endif
/*init function and a loop
loop do wtv it needs to do*/