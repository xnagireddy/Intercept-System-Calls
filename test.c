#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/* Define ioctl commands */
#define IOCTL_PATCH_TABLE 0x00000001
#define IOCTL_FIX_TABLE   0x00000004


int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <opcode>\n", argv[0]);
        return 1;
    }

    int device = open("/dev/MyDevice", O_RDWR);
    printf("device: [%d]\n", device);
    int opcode = atoi(argv[1]);
    switch(opcode) {
        case 1:
            fprintf(
                stdout,
                "Send ioctl request [%x] to patch the syscall table.\n",
                IOCTL_PATCH_TABLE
            );
            ioctl(device, IOCTL_PATCH_TABLE);
            break;
        case 4:
            fprintf(
                stdout,
                "Send ioctl request [%x] to fix the syscall table.\n",
                IOCTL_FIX_TABLE
            );
            ioctl(device, IOCTL_FIX_TABLE);
            break;
        default:
            fprintf(stderr, "Unsupported opcode [%d]\n", opcode);
            break;
    }

    close(device);
    return 0;
}

