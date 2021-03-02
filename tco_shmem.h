#ifndef _TCO_SHMEM_H_
#define _TCO_SHMEM_H_

#include <stdint.h>

/* 
Store output of the control daemon and any related data needed by the io daemon to control the
hardware.
*/
#define TCO_SHMEM_NAME_CONTROL "tco_shmem_control"
#define TCO_SHMEM_NAME_SEM_CONTROL "tco_shmem_sem_control"
struct tco_shmem_data_control
{
    uint8_t valid;     /* =0 means shared memory is invalid, >0 means valid */
    uint8_t emergency; /* =0 mean no emergency, >1 means there is an emergency */
    struct
    {
        uint8_t active; /* =0 means inactive, >0 active */
        float pulse_frac;
    } ch[16];
} __attribute__((packed));
#define TCO_SHMEM_SIZE_CONTROL sizeof(struct tco_shmem_data_control)

#ifdef TRAINING
/*
Store state of the simulated car. This is only used when training hence the ifdef.
*/
#define TCO_SIM_WIDTH 640
#define TCO_SIM_HEIGHT 480
#define TCO_SHMEM_NAME_TRAINING "tco_shmem_training"
#define TCO_SHMEM_NAME_SEM_TRAINING "tco_shmem_sem_training"
struct tco_shmem_data_training
{
    uint8_t valid;                                /* =0 means shared memory is invalid, >0 means valid */
    uint8_t state;                                /* =0 means simulator is paused. =1 means request to step once. =2 means request to hard reset. Gym will wait until this is returned back to 0 before proceeding. */
    uint8_t wheels_off_track[4];                  /* [0] = FL, [1] = FR, [2] = RL, [3] = RR */
    uint8_t drifting;                             /* =0 when not drifting and >0 when drifting */
    float speed;                                  /* meters per second */
    float pos[3];                                 /* [0] = x, [1] = y, [2] = z */
    uint8_t video[TCO_SIM_HEIGHT][TCO_SIM_WIDTH]; /* Grayscale camera feed from the simulator */
} __attribute__((packed));
#define TCO_SHMEM_SIZE_TRAINING sizeof(struct tco_shmem_data_training)
#endif /* TRAINING */

/* Shared memory array constructors */
#ifdef TRAINING
#define TCO_SHMEM_ARR_NAME          \
    {                               \
        TCO_SHMEM_NAME_CONTROL,     \
            TCO_SHMEM_NAME_TRAINING \
    }
#define TCO_SHMEM_ARR_SEM_NAME          \
    {                                   \
        TCO_SHMEM_NAME_SEM_CONTROL,     \
            TCO_SHMEM_NAME_SEM_TRAINING \
    }
#define TCO_SHMEM_ARR_SIZE          \
    {                               \
        TCO_SHMEM_SIZE_CONTROL,     \
            TCO_SHMEM_SIZE_TRAINING \
    }
#else
#define TCO_SHMEM_ARR_NAME      \
    {                           \
        TCO_SHMEM_NAME_CONTROL, \
    }
#define TCO_SHMEM_ARR_SEM_NAME      \
    {                               \
        TCO_SHMEM_NAME_SEM_CONTROL, \
    }
#define TCO_SHMEM_ARR_SIZE      \
    {                           \
        TCO_SHMEM_SIZE_CONTROL, \
    }
#endif /* TRAINING */

#endif /* _TCO_SHMEM_H_ */
