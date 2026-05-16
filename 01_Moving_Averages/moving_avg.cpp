// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <numeric>
// #include <queue>
// #include <chrono>

// using namespace std;

// int main(){
//     auto start_time = chrono::high_resolution_clock::now();
//     ifstream file("dummy_stock_prices.csv");
//     if (!file.is_open()) {
//         cerr << "Error opening file!" << endl;
//         return 1;
//     }
//     int window_size = 50;

//     queue<double> window;

//     double current_sum = 0.0;
//     string line;

//     while (getline(file, line)){
//         try{
//             double val = stod(line);
//             window.push(val);

//             current_sum += val;

//             if (window.size() > window_size){
//                 current_sum -= window.front();
//                 window.pop();
//             }
//             if (window.size() == window_size){
//                 double moving_avg = current_sum / window_size;
//                 cout << moving_avg << endl;
//             }
//         }
//         catch (const invalid_argument& e){
//             cerr << "Invalid number in file: " << line << endl;
//         }
//     }
//     file.close();
//     auto end_time = chrono::high_resolution_clock::now();
//     auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
//     cout << "Execution time: " << duration.count() << " ms" << endl;
//     return 0;
// }


#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>

int main() {
    const size_t N = 1'000'000;
    const int window_size = 50;

    std::vector<double> prices(N);
    std::vector<double> moving_average(N, 0.0);

    // -----------------------------------
    // Generate Dummy Price Data
    // -----------------------------------

    std::mt19937 rng(42);
    std::normal_distribution<double> dist(0.0, 1.0);

    double price = 100.0;

    for (size_t i = 0; i < N; ++i) {
        price += dist(rng);   // Random walk
        prices[i] = price;
    }

    // -----------------------------------
    // Moving Average Calculation
    // Optimized Sliding Window Approach
    // -----------------------------------

    auto start = std::chrono::high_resolution_clock::now();

    double window_sum = 0.0;

    for (size_t i = 0; i < N; ++i) {
        window_sum += prices[i];

        if (i >= window_size) {
            window_sum -= prices[i - window_size];
        }

        if (i >= window_size - 1) {
            moving_average[i] = window_sum / window_size;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    // -----------------------------------
    // Print Sample Output
    // -----------------------------------

    std::cout << "First 10 Moving Averages:\n";

    for (int i = window_size - 1; i < window_size + 9; ++i) {
        std::cout << "Index " << i
                  << " -> MA: "
                  << moving_average[i]
                  << "\n";
    }

    std::cout << "\nComputed Moving Average on "
              << N
              << " rows\n";

    std::cout << "Execution Time: "
              << elapsed.count()
              << " seconds\n";

    return 0;
}