/* 
** Monty Hall Problem Simulator
** The doors are represented as an array of 3 bools. 
** 
*/

#include <cstdlib>
#include <ctime>
#include <iostream>

#define SWITCH 0 
#define KEEP 1


int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Need exactly one argument, the number of trials to simulate" << std::endl; 
        std::cerr << "Got " << argc << " instead" << std::endl; 
        return 1; 
    }

    int NUM_SIMS = atoi(argv[1]);

    bool doors[3] = {false, false, false};
    float wins[2] = {0};

    std::srand(std::time(0));

    for(int i = 0; i < NUM_SIMS; i++) {
        int car_location = std::rand() % 3;

        // Dealer places the car
        doors[car_location] = true;

        // Player makes initial choice 
        int choice = std::rand() % 3;
        
        // Dealer reveals one of the losing doors
        // Always the one to left. This should not randomness of simulation 
        int revealed = (car_location + 1) % 3; 
        if(revealed == choice) revealed = (car_location + 2 ) % 3;

        // Player makes next choice; half the time, they switch
        int strategy = i % 2;
        if(strategy == SWITCH) choice = 3 - choice - revealed; 

        if(doors[choice])
            wins[strategy]++; 
        
        //Reset state for next iteration 
        doors[car_location] = false;
    }
    std::cout << "Trials: " << NUM_SIMS << std::endl; 
    std::cout << "   Switch: " << (wins[SWITCH]) / (NUM_SIMS / 2) << std::endl; 
    std::cout << "   Stay:   " << (wins[KEEP]) / (NUM_SIMS / 2) << std::endl; 

    return 0; 
}