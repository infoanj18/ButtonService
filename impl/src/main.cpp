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
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include "ford/utils/logger.hpp"

static std::atomic<bool> running{true};

void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        running = false;
    }
}

int main() {
    ford::utils::Logger logger("Button-Service");
    
    // Set up signal handlers for graceful shutdown
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    
    LogI(logger, "Button-Service starting...");
    std::cout << "Hello World" << std::endl;
    
    // Main service loop
    while (running) {
        // TODO: Add your service logic here
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    LogI(logger, "Button-Service exiting.");
    return 0;
}
