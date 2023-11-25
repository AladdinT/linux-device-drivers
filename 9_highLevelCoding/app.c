#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/my_file"
#define BUFFER_SIZE 1024

int main() {
    int file_descriptor;
    char buffer[BUFFER_SIZE];

    // Open the device file for reading
    file_descriptor = open(DEVICE_FILE, O_RDONLY);
    ssize_t bytesRead = read(file_descriptor, buffer, sizeof(buffer));
    printf("Read from %s: %.*s\n", DEVICE_FILE, (int)bytesRead, buffer);
    close(file_descriptor);

    // Open the device file for writing
    file_descriptor = open(DEVICE_FILE, O_WRONLY);
    const char *dataToWrite = "Hello from C!";
    ssize_t bytesWritten = write(file_descriptor, dataToWrite, strlen(dataToWrite));
    printf("Write to %s: %.*s\n", DEVICE_FILE, (int)bytesWritten, dataToWrite);
    close(file_descriptor);

    return 0;
}
