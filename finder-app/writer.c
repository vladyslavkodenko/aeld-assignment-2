#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>

#define EXPECTED_ARGC 3

int main(int argc, char *argv[]) {
    openlog(NULL, LOG_PID | LOG_CONS, LOG_USER);

    if (argc != EXPECTED_ARGC) {
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        syslog(LOG_ERR, "Invalid Number of arguments: %d", argc);
        closelog();
        return 1;
    }

    const char* filename = argv[1];
    const char* file_content = argv[2];

    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if (fd == -1) {
        int err = errno;
        char* error = strerror(err);
        fprintf(stderr, "%s\n", error);
        syslog(LOG_ERR, "%s", error);
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", file_content, filename);
    size_t len = strlen(file_content);
    ssize_t wr = write(fd, file_content, len);

    if (wr == -1 || (size_t)wr != len) {
        int err = errno;
        char* error = strerror(err);
        fprintf(stderr, "%s\n", error);
        syslog(LOG_ERR, "Error writing to file %s: %s", filename, error);
        close(fd);
        closelog();
        return 1;
    }

    close(fd);
    closelog();
    return 0;
}
