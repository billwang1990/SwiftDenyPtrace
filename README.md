# SwiftDenyPtrace
An example of how to deny Ptrace attach in swift 3 project.

### [Ptrace](http://man7.org/linux/man-pages/man2/ptrace.2.html)

Ptrace provide a way to monitor your code, so we should disable the ptrace in our program.


### How to do?

* Open your project, create the `main.swift` file, and paste the code snippet below:
 
``` 
import Foundation
import UIKit

autoreleasepool {
    disable_gdb()
    UIApplicationMain(
        CommandLine.argc,
        UnsafeMutableRawPointer(CommandLine.unsafeArgv)
            .bindMemory(
                to: UnsafeMutablePointer<Int8>.self,
                capacity: Int(CommandLine.argc)),
        nil,
        NSStringFromClass(AppDelegate.self) //Or your class name
    )
}
```

* Copy the `DenyPtrace.c ` to you project, or create the file and paste the code:

```

#include <stdio.h>
#import <dlfcn.h>
#import <sys/types.h>

typedef int (*ptrace_ptr_t)(int _request, pid_t _pid, caddr_t _addr, int _data);
#if !defined(PT_DENY_ATTACH)
#define PT_DENY_ATTACH 31
#endif  

void disable_gdb() {
    void* handle = dlopen(0, RTLD_GLOBAL | RTLD_NOW);
    ptrace_ptr_t ptrace_ptr = dlsym(handle, "ptrace");
    ptrace_ptr(PT_DENY_ATTACH, 0, 0, 0);
    dlclose(handle);
}
```

* Add this lines to your project bridging header file.

``` 
#import "DenyPtrace.c"
void disable_gdb();
```

* Open `Appdelegate.swift`, and comment out the `@UIApplicationMain` label.

Done
