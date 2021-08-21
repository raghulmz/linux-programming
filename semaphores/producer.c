#include <sys/mman.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "common.h"

void main()
{
    int shm_fd = shm_open(BACKING_FILE, O_WRONLY | O_CREAT, BACKING_FILE_MODE);
    if (shm_fd < 0)
    {
        error(1, errno, "Unable to open backing file %s", BACKING_FILE);
    }

    mmap(NULL, SHM_BUFF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 1);

    sem_t *write_sem = sem_open(WRITE_SEM, O_CREAT | O_RDWR, BACKING_FILE_MODE, 1);
    sem_t *read_sem = sem_open(READ_SEM, O_CREAT | O_RDWR, BACKING_FILE_MODE, 0);

    for (int i = 0; i < 10; i++)
    {
        sem_wait(write_sem);
        char msg[2];
        sprintf(msg, "%d", i);
        write(shm_fd, msg, sizeof(msg));
        sem_post(read_sem);
    }

    close(shm_fd);
}