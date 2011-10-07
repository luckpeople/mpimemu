/**
 * Copyright (c) 2010-2011 Los Alamos National Security, LLC.
 *                         All rights reserved.
 *
 * This program was prepared by Los Alamos National Security, LLC at Los Alamos
 * National Laboratory (LANL) under contract No. DE-AC52-06NA25396 with the U.S.
 * Department of Energy (DOE). All rights in the program are reserved by the DOE
 * and Los Alamos National Security, LLC. Permission is granted to the public to
 * copy and use this software without charge, provided that this Notice and any
 * statement of authorship are reproduced on all copies. Neither the U.S.
 * Government nor LANS makes any warranty, express or implied, or assumes any
 * liability or responsibility for the use of this software.
 */

#ifndef MPIMEMU_INCLUDED
#define MPIMEMU_INCLUDED

#include "constants.h"
#include "mpi.h"

/* mem info stuff */
typedef struct mem_info_t {
    const char **index_name_ptr;
    int num_elements;
} mem_info_t;

/**
 * mem info array
 * items should following the ordering specified by mem_info_type_t
 */
static mem_info_t mem_info[MMU_NUM_MEM_TYPES] = {
    /* node */
    {meminfo_name_list,  MMU_MEM_INFO_LEN},
    /* proc */
    {status_name_list, MMU_NUM_STATUS_VARS}
};

/* my rank */
static int my_rank;
/**
 * my color
 * either 0 (collects node mem info) or 1 (performs dummy collectives).
 */
static int my_color;
/* holds mpi return codes */
static int mpi_ret_code;
/* my pid */
static pid_t my_pid;
/* size of mpi_comm_world */
static int num_ranks;
/* worker communicator (see: my_color) */
static MPI_Comm worker_comm;
/* error string length */
/* time junk */
static struct tm *bd_time_ptr;
static time_t raw_time;
/* error string buffer */
/* hostname buffer */
static char hostname_buff[MPI_MAX_PROCESSOR_NAME];
/* holds values for each recorded value */
static unsigned long int *node_mem_vals = NULL, *proc_mem_vals = NULL;
/* holds meminfo sample values */
static unsigned long int **node_samples = NULL,
                         **pre_mpi_init_proc_samples = NULL,
                         **proc_samples = NULL;
/* holds min sample values */
static unsigned long int *node_min_sample_values = NULL,
                         *proc_min_sample_values = NULL;
/* holds max sample values */
static unsigned long int *node_max_sample_values = NULL,
                         *proc_max_sample_values = NULL;
/* holds sample averages */
static double *node_sample_aves = NULL, *proc_sample_aves = NULL;
/* holds sample averages */
static double *node_min_sample_aves = NULL, *proc_min_sample_aves = NULL;
/* holds sample averages */
static double *node_max_sample_aves = NULL, *proc_max_sample_aves = NULL;
/* number of processes that are doing work */
static int num_workers;
/* start time buffer */
static char start_time_buff[MMU_TIME_STR_MAX];

static int
init(void);

static int
init_mpi(int argc,
         char **argv);

static int
fini(void);

static int
fini_mpi(void);

static int
set_mem_info(int mem_info_type,
             unsigned long int *mem_vals,
             const char *mem_info_str);

static int
update_mem_info(int mem_info_type,
                unsigned long int *mem_vals);

static int
reduce_local(const unsigned long int *in_vec,
             unsigned long int *out,
             int in_vec_len,
             int op);

static unsigned long int
strtoul_wec(const char *nptr,
            char **endptr,
            int base,
            int *ret_code);

static int
is_valid_key(int mem_info_type,
             const char *key,
             int *index_if_valid);

static int
get_local_mma(unsigned long int **in_mat,
              int vec_len,
              unsigned long int **out_min_vec_ptr,
              unsigned long int **out_max_vec_ptr,
              double **out_ave_vec_ptr);

static int
get_global_mma(unsigned long int **in_out_min_vec_ptr,
               unsigned long int **in_out_max_vec_ptr,
               double **in_out_ave_vec_ptr,
               int vec_len,
               double **out_min_samp_vec_ptr,
               double **out_max_samp_vec_ptr,
               MPI_Comm comm,
               int num_members);

#if MMU_DO_SEND_RECV == 1
static int
do_send_recv_ring(void);
#endif

#endif /* ifndef MPIMEMU_INCLUDED */