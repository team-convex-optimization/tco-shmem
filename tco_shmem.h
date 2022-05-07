#ifndef _TCO_SHMEM_H_
#define _TCO_SHMEM_H_

#include <stdint.h>
#define TCO_FRAME_WIDTH 640U
#define TCO_FRAME_HEIGHT 280U

/*
Store output of the plan daemon which is a description of the desired path to be taken by the
control daemon.
*/
#define TCO_SHMEM_NAME_PLAN "tco_shmem_plan"
#define TCO_SHMEM_NAME_SEM_PLAN "tco_shmem_sem_plan"
struct tco_shmem_data_plan
{
    _Alignas(4) float target_pos;   /* Desired position. -1 left edge of frame, 1 right edge of frame, 0 is center.  */
    _Alignas(4) float target_speed; /* Desired speed in meters per second. */
    _Alignas(1) uint8_t lap_of_honor; /* Set to 1 once the finish line is detected */
    _Alignas(4) uint32_t frame_id;
};
#define TCO_SHMEM_SIZE_PLAN sizeof(struct tco_shmem_data_plan)

/*
Store output of the sensor daemon which stores all of the sensor outputs for the control daemon.
*/
#define TCO_SHMEM_NAME_SENSOR "tco_shmem_sensor"
#define TCO_SHMEM_NAME_SEM_SENSOR "tco_shmem_sem_sensor"
struct tco_shmem_data_sensor
{
    _Alignas(4) uint32_t time_step; /* Similar to ID, increments with every reading of sensord main thread */
    _Alignas(8) double ultrasound_left;
    _Alignas(8) double ultrasound_right;
    _Alignas(8) double hall_effect_rpm; /* RPM, scaled to rear wheel ratio, of the car */
};
#define TCO_SHMEM_SIZE_SENSOR sizeof(struct tco_shmem_data_sensor)

/* 
Store output of the control daemon and any related data needed by the io daemon to control the
hardware.
*/
#define TCO_SHMEM_NAME_CONTROL "tco_shmem_control"
#define TCO_SHMEM_NAME_SEM_CONTROL "tco_shmem_sem_control"
struct tco_shmem_data_control
{
    _Alignas(4) struct
    {
        _Alignas(4) float pulse_frac;
        _Alignas(1) uint8_t active; /* =0 means inactive, >0 active */
    } ch[16];
    _Alignas(1) uint8_t emergency; /* =0 mean no emergency, >1 means there is an emergency */
};
#define TCO_SHMEM_SIZE_CONTROL sizeof(struct tco_shmem_data_control)

/*
Store state of the car.
*/
#define TCO_SHMEM_NAME_STATE "tco_shmem_state"
#define TCO_SHMEM_NAME_SEM_STATE "tco_shmem_sem_state"
struct tco_shmem_data_state
{
    _Alignas(4) uint32_t frame_id;
    _Alignas(4) float speed;                                      /* Meters per second */
    _Alignas(4) uint8_t wheels_off_track[4];                      /* [0] = FL, [1] = FR, [2] = RL, [3] = RR */
    _Alignas(4) uint8_t frame[TCO_FRAME_HEIGHT][TCO_FRAME_WIDTH]; /* Grayscale camera feed */
    _Alignas(4) float pos[3];                                     /* [0] = x, [1] = y, [2] = z */
    _Alignas(1) uint8_t drifting;                                 /* =0 when not drifting and >0 when drifting */
    _Alignas(1) uint8_t state_sim;                                /* =0 means simulator is paused. =1 means request to step once. =2 means request to hard reset. Gym will wait until this is returned back to 0 before proceeding. */
};
#define TCO_SHMEM_SIZE_STATE sizeof(struct tco_shmem_data_state)

/* Shared memory array constructors */
#define TCO_SHMEM_ARR_NAME        \
    {                             \
        TCO_SHMEM_NAME_CONTROL,   \
            TCO_SHMEM_NAME_STATE, \
            TCO_SHMEM_NAME_PLAN,   \
            TCO_SHMEM_NAME_SENSOR   \
    }
#define TCO_SHMEM_ARR_SEM_NAME        \
    {                                 \
        TCO_SHMEM_NAME_SEM_CONTROL,   \
            TCO_SHMEM_NAME_SEM_STATE, \
            TCO_SHMEM_NAME_SEM_PLAN,   \
            TCO_SHMEM_NAME_SEM_SENSOR   \
    }
#define TCO_SHMEM_ARR_SIZE        \
    {                             \
        TCO_SHMEM_SIZE_CONTROL,   \
            TCO_SHMEM_SIZE_STATE, \
            TCO_SHMEM_SIZE_PLAN,   \
            TCO_SHMEM_SIZE_SENSOR   \
    }

#endif /* _TCO_SHMEM_H_ */
