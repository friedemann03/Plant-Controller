// Taken from an example of Carmine Novellio's Book Mastering STM 2nd Edition.
// All unnecessary functionality removed.
// See the original: https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f446RE/system/src/retarget/retarget.c


#include "retarget.h"

#include "stdio.h"
#include "sys/unistd.h"
#include "sys/errno.h"


UART_HandleTypeDef *gHuart;


void RetargetInit(UART_HandleTypeDef*huart){
    gHuart = huart;
    /* Disable I/O buffering for STDOUT stream, so that
     * chars are sent out as soon as they are printed. */
    setvbuf(stdout, NULL, _IONBF, 0);
}

int _write(int fd,char *ptr,int len) {
    HAL_StatusTypeDef hstatus;
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        hstatus = HAL_UART_Transmit(gHuart, (uint8_t *) ptr, len, 100);
        if (hstatus == HAL_OK)
            return len;
        else
            return EIO;
    }
    errno = EBADF;
    return -1;
}

