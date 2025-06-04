/* 
** Monty Hall Problem Simulator
** 
** Input:  num_trials, integers greater than 1. 
** Output: 0 for successful execution. 
**         1 for input error. 
**         2 for memory error. 
**         Program will print results to the output stream.
** 
** The program will run num_trials simulations of one strategy and num_trials
** of the other strategy. 
** The simulations are completely statistically independent. 
** 
** For this reason, it is best to use a large number of trials to get 
** results consistent with the theoretical. 
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>  

#define SWITCH 0 
#define KEEP 1

int parse_num_trials(const int& argc, const char* const argv[], int* num_trials) {
    for(int i = 1; i < argc; i++) {
        std::string::size_type end_pos; 
        try {
            num_trials[i-1] = std::stoi(argv[i], &end_pos);
        }
        catch (std::invalid_argument e) {
            std::cerr << "monty_hall_sim: invalid argument, num_trials needs to be a number greater than 1." << std::endl; 
            std::cerr << "monty_hall_sim: Got " << argv[i] << " instead." << std::endl;
            std::cerr << e.what() << std::endl;
            return 1; 
        }
        catch(std::out_of_range e) {
            std::cerr << "monty_hall_sim: invalid argument, num_trials out of range for int." << std::endl; 
            std::cerr << "monty_hall_sim: Got " << argv[i] << "." << std::endl;
            std::cerr << e.what() << std::endl;
            return 1; 
        }
        catch(std::exception e) {
            std::cerr << "monty_hall_sim: error: " << e.what() << std::endl; 
        }

        if(num_trials[i-1] < 1) {
            std::cerr << "monty_hall_sim: invalid argument, num_trials needs to be a number greater than 1. " << std::endl;
            std::cerr << "monty_hall_sim: Got " << argv[i] << " instead." << std::endl;
            return 1;
        }

        if(end_pos < strlen(argv[i])) {
            std::cerr << "monty_hall_sim: warning: got  " << argv[i] << ", interpreted as " << num_trials[i-1] << "." << std::endl;
        }

    }
    return 0; 
}

void run_sims(const int num_sims, const int* const num_trials, int* const wins) {
        for(int sim = 0; sim < num_sims; sim++) {
            for(int i = 0; i < num_trials[sim]*2; i++) {
                // Dealer places the car
                bool doors[3] = {false, false, false};
                int car_location = std::rand() % 3;
                doors[car_location] = true;

                // Player makes initial choice 
                int choice = std::rand() % 3;
                
                // Dealer reveals one of the losing doors
                // Always the one to left of the car. This should not affect the randomness of simulation 
                int revealed = (car_location + 1) % 3; 
                if(revealed == choice) revealed = (car_location + 2 ) % 3;

                // Player makes next choice; half the time, they switch
                int strategy = i % 2;
                if(strategy == SWITCH) choice = 3 - choice - revealed; 

                if(doors[choice])
                    wins[sim*2 + strategy]++; 
            }
    }
}

void print_results(const int num_sims, const int* const num_trials, const int* const wins){
    std::cout  << std::endl;
    std::cout << "          MONTY HALL SIM RESULTS           " << std::endl; 
    std::cout << "===========================================" << std::endl;
    std::cout << "# of trials | SWITCH, % wins | STAY, % wins" << std::endl; 
    for(int sim = 0; sim < num_sims; sim++) {
        std::cout << "------------|----------------|-------------" << std::endl;
        int len_trials_number = std::to_string(num_trials[sim]).length();
        std::string padding = std::string((12 - len_trials_number)/2, ' '); 
        std::string extra = std::string(len_trials_number%2, ' ');
        std::cout << std::left << padding << extra << num_trials[sim] << padding << "|";
        std::cout << std::setprecision(2) << std::fixed; 
        padding = std::string((16 - 5)/2, ' '); 
        std::cout << padding << float(wins[sim*2 + SWITCH]) / (num_trials[sim]) * 100 << "%" << padding << "|";
        padding = std::string((13 - 5)/2, ' '); 
        std::cout << padding << float(wins[sim*2 + KEEP]) / (num_trials[sim])*100 << "%" << std::endl;
    }
    std::cout << std::endl; 
}


int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cout << "monty_hall_sim: need at least one argument, number of trials, to run." << std::endl; 
        return 1; 
    }

    int num_sims = argc - 1; 
    int* num_trials;
    
    try {
        num_trials = new int[num_sims];
    }
    catch (std::bad_alloc e) {
        std::cerr << "monty_hall_sim: not enough memory to allocate array for simulation information." << std::endl;
        return 2;
    }

    if(parse_num_trials(argc, argv, num_trials) != 0)
        return 1;

    
    int* wins;
    try {
        wins = new int[num_sims * 2];
    }
    catch (std::bad_alloc e) {
        std::cerr << "monty_hall_sim: not enough memory to allocate array for results." << std::endl;
        return 2;
    }
    
    std::srand(std::time(0)); 
    
    run_sims(num_sims, num_trials, wins);

    print_results(num_sims, num_trials, wins);

    return 0; 
}
