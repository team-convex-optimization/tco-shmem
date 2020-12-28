#ifndef _TCO_SHMEM_H_
#define _TCO_SHMEM_H_

#include <stdint.h>

/* Shared memory regions */

/* 
Store output of the ML model and any related data needed by the control
server. 
*/
#define TCO_SHMEM_NAME_MODEL "tco_shmem_model"
#define TCO_SHMEM_NAME_SEM_MODEL "tco_shmem_sem_model"
struct tco_shmem_data_model
{
    uint8_t valid; /* =0 means shared memory is invalid, >0 means valid */
};
#define TCO_SHMEM_SIZE_MODEL sizeof(struct tco_shmem_data_model)

/* 
Store output of the control server any any related data needed by the io
server to control the hardware.
*/
#define TCO_SHMEM_NAME_CONTROL "tco_shmem_control"
#define TCO_SHMEM_NAME_SEM_CONTROL "tco_shmem_sem_control"
struct tco_shmem_data_control
{
    uint8_t valid; /* =0 means shared memory is invalid, >0 means valid */
    struct
    {
        uint8_t active; /* =0 means inactive, >0 active */
        float pulse_frac;
    } ch[16];
};
#define TCO_SHMEM_SIZE_CONTROL sizeof(struct tco_shmem_data_control)

/* Shared memory array constructors */
#define TCO_SHMEM_ARR_NAME                           \
    {                                                \
        TCO_SHMEM_NAME_MODEL, TCO_SHMEM_NAME_CONTROL \
    }
#define TCO_SHMEM_ARR_SEM_NAME                               \
    {                                                        \
        TCO_SHMEM_NAME_SEM_MODEL, TCO_SHMEM_NAME_SEM_CONTROL \
    }
#define TCO_SHMEM_ARR_SIZE                           \
    {                                                \
        TCO_SHMEM_SIZE_MODEL, TCO_SHMEM_SIZE_CONTROL \
    }

#endif /* _TCO_SHMEM_H_ */
