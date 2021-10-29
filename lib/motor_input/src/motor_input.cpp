/**
 * @file: motor_input.cpp
 * @author: Noman5237
 * @date: 29/10/2021; 12:24
 */

#include "motor_input_internal.h"

void motor_input_send() {
    pid_control_calculate_motor_speed();
}