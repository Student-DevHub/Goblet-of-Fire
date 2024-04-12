#pragma once
#ifndef WIZARD_H
#define WIZARD_H

#include <concurrent_queue.h>
#include <condition_variable>
#include <mutex>
#include "Spell.h"

namespace GobletOfFire{
  namespace Input {

    class Wizard {
    public:
      Wizard() {}

      void invokeSpells();
      void inscriptSpells(std::shared_ptr<Input::Spell> spell);
      void stopInvoking();
    
    private:
      Concurrency::concurrent_queue<Input::Spell> spell_book_;
      std::condition_variable mystic_notifier_;
    };
  }
}
#endif 

/*
#include <iostream>
#include <thread>
#include <concurrent_queue.h>
#include <condition_variable>
#include <mutex>

using namespace Concurrency;

class Invoker {
public:
    Invoker() : shouldStop(false) {}

    void addCommand(int command) {
        commandQueue.push(command);
        cv.notify_one();
    }

    void startExecution() {
        executionThread = std::thread([&]() {
            while (!shouldStop) {
                int command;
                if (commandQueue.try_pop(command)) {
                    std::cout << "Executing command: " << command << std::endl;
                } else {
                    std::unique_lock<std::mutex> lock(mutex);
                    cv.wait(lock);
                }
            }
        });
    }

    void stopExecution() {
        // Set the flag to signal the execution thread to stop
        shouldStop = true;

        // Notify the execution thread in case it's waiting
        cv.notify_one();

        // Clean up resources and join the execution thread
        if (executionThread.joinable()) {
            executionThread.join();
        }
    }

private:
    concurrent_queue<int> commandQueue;
    std::thread executionThread;
    std::mutex mutex;
    std::condition_variable cv;
    bool shouldStop;
};

int main() {
    Invoker invoker;
    invoker.startExecution();

    // Enqueue commands
    invoker.addCommand(1);
    invoker.addCommand(2);
    invoker.addCommand(3);

    // Stop execution
    std::this_thread::sleep_for(std::chrono::seconds(2));
    invoker.stopExecution();

    return 0;
}

*/