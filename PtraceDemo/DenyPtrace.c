//
//  DenyPtrace.c
//  PtraceDemo
//
//  Created by Yaqing Wang on 9/16/15.
//  Copyright © 2015 billwang1990.github.io. All rights reserved.
//

#include <stdio.h>
#import <string.h>
#import <dlfcn.h>
#import <sys/types.h>
#define A(c)            (c) - 0x19
#define UNHIDE_STR(str) do { char *p = str;  while (*p) *p++ += 0x19; } while (0)
#define HIDE_STR(str)   do { char *p = str;  while (*p) *p++ -= 0x19; } while (0)
typedef int (*ptrace_ptr_t)(int _request, pid_t _pid, caddr_t _addr, int _data);
#if !defined(PT_DENY_ATTACH)
#define PT_DENY_ATTACH 31
#endif  

void disable_gdb() {
    void* handle = dlopen(0, RTLD_GLOBAL | RTLD_NOW);
    //Obsficate 'ptrace'string
    char str[  ] = {
        A('p'), A('t'), A('r'), A('a'), A('c'),
        A('e'), 0
    };
    UNHIDE_STR(str);
    char string[6];
    strcpy(string, str);
    ptrace_ptr_t ptrace_ptr = dlsym(handle, string);
    ptrace_ptr(PT_DENY_ATTACH, 0, 0, 0);
    dlclose(handle);
}
