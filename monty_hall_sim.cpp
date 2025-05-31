/* 
** Monty Hall Problem Simulator
** 
** Input:  NUM_SIMS, an integer representing the number of trials. 
** Output: N/A. Program will print results to the output stream. 
** 
** Half of NUM_SIMS trials will use the 'switch' strategy and the other half 
** will use the 'stay' strategy. The trials are completely independent of each 
** other. 
** 
** For this reason, it is best to use a large number of trials to get 
** significant results. 
*/

#include <cstdlib>
#include <ctime>
#include <iostream>

#define SWITCH 0 
#define KEEP 1


int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "ERROR: Need exactly one argument, the number of trials to simulate" << std::endl; 
        std::cerr << "Got " << argc << " instead" << std::endl; 
        return 1; 
    }

    int NUM_SIMS;

    try {
        NUM_SIMS = std::stoi(argv[1]);
    }
    catch (std::invalid_argument e) {
        std::cerr << "ERROR: Argument needs to be a number." << std::endl; 
        std::cerr << e.what() << std::endl;
        return 1; 
    }

    if(NUM_SIMS < 2) {
        std::cerr << "ERROR: Need to simulate at least two trials. " << std::endl;
        return 1;
    }

    if(NUM_SIMS < 200) {
        std::cerr << "Warning: small amount of trials will not produce consistent results." << std::endl;
    }

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
        // Always the one to left of the car. This should not affect randomness of simulation 
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
    std::cout << "   Switch: " << (wins[SWITCH]) / (NUM_SIMS / 2 + NUM_SIMS % 2) << std::endl; 
    std::cout << "   Stay:   " << (wins[KEEP]) / (NUM_SIMS / 2) << std::endl; 

    return 0; 
}