# ShadowLogs
ShadowLog 🕵️‍♂️LD_PRELOAD-based logger that hooks execve to log executed commands, users, and TTY sessions .


 LD_PRELOAD-based command logger designed for process monitoring. By hooking the execve system call, it captures and logs every executed command along with user details and TTY session information.

Features
✅ Stealth Logging – Hooks execve to record commands without modifying binaries.

✅ User & TTY Tracking – Captures the username, TTY session, and timestamp for each command.

✅ Minimal Footprint – Runs as a shared library, injected dynamically with LD_PRELOAD.
