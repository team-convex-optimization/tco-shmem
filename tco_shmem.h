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
    uint32_t mem_size;
};

/* 
Store output of the control server any any related data needed by the io
server to control the hardware.
*/
#define TCO_SHMEM_NAME_CONTROL "tco_shmem_control"
#define TCO_SHMEM_NAME_SEM_CONTROL "tco_shmem_sem_control"
struct tco_shmem_data_control
{
    uint32_t mem_size;
    struct
    {
        uint16_t pulse_len_min;
        uint16_t pulse_len_max;
        uint8_t ch;
        float turn_frac;
    } steering;
};

/* Shared memory array constructors */
#define TCO_SHMEM_ARR_NAME {TCO_SHMEM_NAME_MODEL, TCO_SHMEM_NAME_CONTROL};
#define TCO_SHMEM_ARR_SEM_NAME {TCO_SHMEM_NAME_SEM_MODEL, TCO_SHMEM_NAME_SEM_CONTROL};
#define TCO_SHMEM_ARR_SIZE {sizeof(struct tco_shmem_data_model), sizeof(struct tco_shmem_data_control)};

#endif /* _TCO_SHMEM_H_ */
