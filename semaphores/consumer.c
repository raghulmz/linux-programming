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
#include <string.h>

void main()
{
    int shm_fd = shm_open(BACKING_FILE, O_RDONLY, BACKING_FILE_MODE);
    if (shm_fd < 0)
    {
        error(1, errno, "Unable to open backing file %s", BACKING_FILE);
    }

    mmap(NULL, SHM_BUFF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 1);

    sem_t *write_sem = sem_open(WRITE_SEM, O_CREAT | O_RDWR, BACKING_FILE_MODE, 1);
    sem_t *read_sem = sem_open(READ_SEM, O_CREAT | O_RDWR, BACKING_FILE_MODE, 0);

    for (;;)
    {
        char buf[2];
        memset(buf, 0, sizeof(buf));
        sem_wait(read_sem);
        read(shm_fd, buf, 2);
        printf("read: %s\n", buf);
        sem_post(write_sem);
    }
}