#include <iostream>
#include <random>
#include <future>
#include "TrafficLight.h"

template <typename T>
T MessageQueue<T>::receive()
{
    // Acquire the lock and guard against spurious wakes by checking the queue isn't empty
    std::unique_lock<std::mutex> ulock(_mutex);
    _condition.wait(ulock, [this]() { return !_queue.empty(); });

    // Move the first message out of the queue and return it
    T message = std::move(_queue.front());
    _queue.pop_front();
    return message;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> lck(_mutex);
    _queue.push_back(std::move(msg));
    _condition.notify_one();
}

TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    while (true) {
        TrafficLightPhase lightChange = _messages.receive();
        if (lightChange == TrafficLightPhase::green)
            break;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    double cycleDuration = 4000 + (rand() % 6000); // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            _currentPhase = getCurrentPhase() == TrafficLightPhase::red
                ? TrafficLightPhase::green
                : TrafficLightPhase::red;

            _messages.send(std::move(_currentPhase));

            // reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();
        }
    }
}