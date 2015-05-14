#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define KEY_PRESSED 1
#define KEY_RELEASED 0
#define True 1
#define False 0

int capslock = 0;

int main (int argc, char *argv[]) {
    struct input_event ev[64];
    int fd, rd, value, size = sizeof (struct input_event);
    FILE* ledfd;
    char name[256] = "Unknown";
    char *device = NULL;

    // Open keyboard device.
    if ((fd = open ("/dev/input/event3", O_RDONLY)) == -1)
        perror("Cannot open keyboard input device!\n");

    // Open led file.
    if((ledfd = fopen("/proc/acpi/ibm/led", "w")) == NULL)
        perror("Cannot open led control file!\n");

    // Set daemon mode.
    daemon(0, 0);

    while (1){
        if ((rd = read (fd, ev, size * 64)) < size) {
            perror("Error reading keystrokes...exiting!");
            exit(0);
        }

        if (ev[0].value == KEY_CAPSLOCK && ev[1].value == KEY_PRESSED) {
            if(capslock) {
                capslock = False;
                // turn on the LED
                fprintf(ledfd, "0 on");
                fflush(ledfd);
            }
            else {
                capslock = True;
                // turn off the LED
                fprintf(ledfd, "0 off");
                fflush(ledfd);
            }
        }
    }
// This code should never be executed.
return 0;
}
