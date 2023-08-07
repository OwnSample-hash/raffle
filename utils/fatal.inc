#if defined __fatal
#endinput
#endif
#define __fatal

void fatal(const char[] msg, any ...){
    char buffer[1024];
    VFormat(buffer, sizeof(buffer), msg, 2);
    PrintToServer("fatal:%s", buffer);
    ThrowError("fatal:%s", buffer);
}
