#ifndef _TCO_SHMEM_H_
#define _TCO_SHMEM_H_

#include <stdint.h>
#define TCO_FRAME_WIDTH 640U
#define TCO_FRAME_HEIGHT 480U
#define TCO_PLAN_WAYPTS_N 10U

/* 
Store output of the plan daemon which is a description of the desired path to be taken by the
control daemon.
*/
#define TCO_SHMEM_NAME_PLAN "tco_shmem_plan"
#define TCO_SHMEM_NAME_SEM_PLAN "tco_shmem_sem_plan"
struct tco_shmem_data_plan
{
    _Alignas(1) uint8_t valid;                         /* =0 means shared memory is invalid, >0 means valid */
    _Alignas(4) uint16_t waypts[TCO_PLAN_WAYPTS_N][2]; /* Each element contains x and y coordiantes of the waypoint on a frame */
    _Alignas(4) uint32_t frame_id;
};
#define TCO_SHMEM_SIZE_PLAN sizeof(struct tco_shmem_data_plan)

/* 
Store output of the control daemon and any related data needed by the io daemon to control the
hardware.
*/
#define TCO_SHMEM_NAME_CONTROL "tco_shmem_control"
#define TCO_SHMEM_NAME_SEM_CONTROL "tco_shmem_sem_control"
struct tco_shmem_data_control
{
    _Alignas(1) uint8_t valid;     /* =0 means shared memory is invalid, >0 means valid */
    _Alignas(1) uint8_t emergency; /* =0 mean no emergency, >1 means there is an emergency */
    _Alignas(4) struct
    {
        _Alignas(4) float pulse_frac;
        _Alignas(1) uint8_t active; /* =0 means inactive, >0 active */
    } ch[16];
};
#define TCO_SHMEM_SIZE_CONTROL sizeof(struct tco_shmem_data_control)

#ifdef TRAINING
/*
Store state of the simulated car. This is only used when training hence the ifdef.
*/
#define TCO_SHMEM_NAME_TRAINING "tco_shmem_training"
#define TCO_SHMEM_NAME_SEM_TRAINING "tco_shmem_sem_training"
struct tco_shmem_data_training
{
    _Alignas(1) uint8_t valid;                                    /* =0 means shared memory is invalid, >0 means valid */
    _Alignas(1) uint8_t state;                                    /* =0 means simulator is paused. =1 means request to step once. =2 means request to hard reset. Gym will wait until this is returned back to 0 before proceeding. */
    _Alignas(1) uint8_t drifting;                                 /* =0 when not drifting and >0 when drifting */
    _Alignas(4) float speed;                                      /* meters per second */
    _Alignas(4) float pos[3];                                     /* [0] = x, [1] = y, [2] = z */
    _Alignas(4) uint8_t wheels_off_track[4];                      /* [0] = FL, [1] = FR, [2] = RL, [3] = RR */
    _Alignas(4) uint8_t video[TCO_FRAME_HEIGHT][TCO_FRAME_WIDTH]; /* Grayscale camera feed from the simulator */
};
#define TCO_SHMEM_SIZE_TRAINING sizeof(struct tco_shmem_data_training)
#endif /* TRAINING */

/* Shared memory array constructors */
#ifdef TRAINING
#define TCO_SHMEM_ARR_NAME           \
    {                                \
        TCO_SHMEM_NAME_CONTROL,      \
            TCO_SHMEM_NAME_TRAINING, \
            TCO_SHMEM_NAME_PLAN      \
    }
#define TCO_SHMEM_ARR_SEM_NAME           \
    {                                    \
        TCO_SHMEM_NAME_SEM_CONTROL,      \
            TCO_SHMEM_NAME_SEM_TRAINING, \
            TCO_SHMEM_NAME_SEM_PLAN      \
    }
#define TCO_SHMEM_ARR_SIZE           \
    {                                \
        TCO_SHMEM_SIZE_CONTROL,      \
            TCO_SHMEM_SIZE_TRAINING, \
            TCO_SHMEM_SIZE_PLAN      \
    }
#else
#define TCO_SHMEM_ARR_NAME      \
    {                           \
        TCO_SHMEM_NAME_CONTROL, \
            TCO_SHMEM_NAME_PLAN \
    }
#define TCO_SHMEM_ARR_SEM_NAME      \
    {                               \
        TCO_SHMEM_NAME_SEM_CONTROL, \
            TCO_SHMEM_NAME_SEM_PLAN \
    }
#define TCO_SHMEM_ARR_SIZE      \
    {                           \
        TCO_SHMEM_SIZE_CONTROL, \
            TCO_SHMEM_SIZE_PLAN \
    }
#endif /* TRAINING */

#endif /* _TCO_SHMEM_H_ */