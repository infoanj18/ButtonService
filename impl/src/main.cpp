//
// CONFIDENTIAL - FORD MOTOR COMPANY
//
// This is an unpublished work, which is a trade secret, created in
// 2026. Ford Motor Company owns all rights to this work and intends
// to maintain it in confidence to preserve its trade secret status.
// Ford Motor Company reserves the right to protect this work as an
// unpublished copyrighted work in the event of an inadvertent or
// deliberate unauthorized publication. Ford Motor Company also
// reserves its rights under the copyright laws to protect this work
// as a published work. Those having access to this work may not copy
// it, use it, or disclose the information contained in it without
// the written authorization of Ford Motor Company.
//

#include <iostream>
#include "ford/utils/logger.hpp"

int main() {
    ford::utils::Logger logger("ButtonService");
    
    LogI(logger, "ButtonService starting...");
    LogI(logger, "Hello World");
    LogI(logger, "ButtonService exiting.");
    
    std::cout << "Hello World" << std::endl;
    return 0;
}
