//
//  main.swift
//  PtraceDemo
//
//  Created by Yaqing Wang on 9/16/15.
//  Copyright © 2015 billwang1990.github.io. All rights reserved.
//

import Foundation
import UIKit

autoreleasepool {
    disable_gdb()
    UIApplicationMain(Process.argc, Process.unsafeArgv, nil, NSStringFromClass(AppDelegate))
}
