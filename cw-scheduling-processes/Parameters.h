#pragma once
//This file stores the parameters needed for the simulation. You can play with the values here when develloping the answer, but your code will be tested with a file that contains different values. 
//This file should therefore not be changed eventually (e.g., adding variables) and not be submitted.

#define PRINT_TERMINATION_OUTPUT true 
#define NB_SIMULATION_REPEATS 1
#define NB_PROCESSORS 4
#define NB_TASKS 30
#define TIME_QUANTUM_MS 10  /*CPU time allocated to one process when scheduled to run on the processor*/
#define CONTEXT_SWITCHING_PENALTY_MS 2  /*This value is to simulate algorithmic time required for a scheduling operation*/

#define SIMULATION_EXECUTION_LENGTH_MIN_PARAM 50 /*A Parameter for simulation execution*/
#define SIMULATION_EXECUTION_LENGTH_MAX_PARAM 300 /*A Parameter for simulation execution */

#define IO_EXECUTION_LENGTH_MIN_PARAM 10 /*A Parameter for simulation execution*/
#define IO_EXECUTION_LENGTH_MAX_PARAM 30 /*A Parameter for simulation execution */
#define IO_TIME_EXECUTION_LENGTH_MIN_PARAM 30 /*A Parameter for simulation execution*/
#define IO_TIME_EXECUTION_LENGTH_MAX_PARAM 150 /*A Parameter for simulation execution */

#define SERVICE_EXECUTION_LENGTH_MAX_PARAM 40 /*A Parameter for simulation execution*/
#define SERVICE_EXECUTION_TIME_PARAM 6 /*A Parameter for simulation execution */

