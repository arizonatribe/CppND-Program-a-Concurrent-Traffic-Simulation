#include "Simulator.h"

int main() {
    Simulator* simulator = new Simulator(Cities::paris, 6);
    simulator->simulate();
}
