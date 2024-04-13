#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include<numeric>
#include <map>
#include <algorithm>
#include <sstream>

/// <summary>
/// This method returns the leading digit of an integer
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
int leadingDigit(double num) {
    while (num >= 10) {
        num /= 10;
    }
    return static_cast<int>(num);
}

/// <summary>
/// This functions returns an unordered map with the modes and their frequencies
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
std::map<double, int> calculateMode(std::vector<double>& data) {
    // Create a map to store the frequency of each element
    std::map<double, int> frequency;

    // Calculate the frequency of each element in the input data
    for (double num : data) {
        if (num > 0) {
            frequency[num]++;
        }
    }

    // Find the maximum frequency among all elements
    int maxFrequency = 0;
    for (const auto& pair : frequency) {
        if (maxFrequency < pair.second) {
            maxFrequency = pair.second;
        }
    }

    // Create a map to store the mode (elements with the maximum frequency)
    std::map<double, int> mode;

    // Populate the mode map with elements having the maximum frequency
    for (const auto& pair : frequency) {
        if (maxFrequency == pair.second && maxFrequency != 1) {
            mode.insert({ pair.first, pair.second });
        }
    }

    // Return the mode map containing the mode and their frequencies
    return mode;
}

/// <summary>
/// The purpose of this method is t find the mininmum number in a data set
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
int minNum(std::vector<double> data) {
    double smallestNum = std::numeric_limits<double>::max();
    for (double num : data) {
        if (smallestNum > num) {
            smallestNum = num;
        }
    }

    return static_cast<int>(smallestNum);
}
/// <summary>
/// The purpose of this method is t find the maximum number in a data set
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
int maxNum(std::vector<double> data) {
    double largestNum = 0;
    for (double num : data) {
        if (largestNum < num) {
            largestNum = num;
        }
    }

    return static_cast<int>(largestNum);
}

/// <summary>
/// This method calculate the benford variance for a given data set
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
double nbVariance(std::vector<double>& data) {
    double sumSquared = 0;
    double totalCount = 0;


    std::map<int, int> frequency;
    for (double num : data) {
        if (leadingDigit(num) > 0) {
            frequency[leadingDigit(num)]++;
            totalCount++;
        }
    }
    // Calculate sum of squared differences    
    for (int i = 1; i < 10; i++) {
        double observedFrequency = 0;
        if (frequency.find(i) != frequency.end()) {
            observedFrequency = (static_cast<double>(frequency[i]) / totalCount);
        }
        double expectedFrequency = log10(1 + 1.0 / (i + 1));
        sumSquared += pow(observedFrequency - expectedFrequency, 2);
    }

    return sumSquared / 9.0;
}

/// <summary>
/// This method prints the header of the benford analysis
/// </summary>
void printHeader() {
    std::cout << "Newcomb-Benford's Law Analysis\n";
    std::cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n";
    std::cout << std::setw(10) << "exp dig" << std::setw(6) << "freq"
        << std::setw(6) << "0" << std::setw(10) << "10" << std::setw(10) << "20"
        << std::setw(10) << "30" << std::setw(10) << "40" << std::setw(10) << "50" << '\n';
    std::cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ÚÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄÂ\n";
}

/// <summary>
/// This method prints the results of caculations for the benford anaylisis
/// </summary>
/// <param name="data"></param>
void benfordAnalysis(const std::vector<double>& data) {
    // Create a map to store the frequency of leading digits
    std::map<int, int> digitFrequency;

    // Create a vector to store data for variance calculation
    std::vector<double> arrayForVariance;

    // Calculate the frequency of leading digits
    for (double num : data) {
        if (num > 0) {
            int digit = leadingDigit(num);
            digitFrequency[digit]++;
        }
    }

    // Calculate the total count of leading digits
    int totalCount = 0;
    for (auto pair : digitFrequency) {
        totalCount += pair.second;
    }

    // Populate an array with data for variance calculation
    for (double num : data) {
        arrayForVariance.push_back(leadingDigit(num));
    }

    // Calculate the variance and standard deviation
    double nbVar = nbVariance(arrayForVariance) * 100;
    double stdDev = (sqrt(nbVar)) * 100;

    // Print the frequency of numbers (0-9)
    std::cout << "\nFrequency of Numbers(0-9):" << std::endl;
    for (const auto pair : digitFrequency) {
        std::cout << "[" << pair.first << "] = " << pair.second << std::endl;
    }
    std::cout << std::endl;

    // Print the header for the Benford analysis
    printHeader();

    // Print the Benford frequencies and observed frequencies
    for (const auto& pair : digitFrequency) {
        double benFordFrequency = log10(1 + 1.0 / pair.first) * 100;
        double frequency = (static_cast<double>(pair.second) / totalCount) * 100;

        // Print the Benford frequency and observed frequency
        std::cout << std::fixed << std::setprecision(2) << std::setw(6) << benFordFrequency << "%";
        std::cout << " [" << pair.first << "] = " << std::fixed << std::setprecision(2) << std::setw(6) << frequency << "% ";

        // Display the histogram
        for (int i = 0; i < static_cast<int>(frequency); ++i) {
            std::cout << "#";
        }
        std::cout << "\n";
    }
    std::cout << "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ ÀÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÁ" << std::endl;
    std::cout << "Variance = " << (nbVar *100) << "%" << std::endl;
    std::cout << "Std. Dev. = " << stdDev  << "%" << std::endl;

    // Determine the strength of the Benford relationship based on standard deviation
    if (stdDev >= (0.5)) {
        std::cout << "There is a weak Benford relationship." << std::endl;
    }
    else if (stdDev >= 0.35) {
        std::cout << "There is a moderate Benford relationship." << std::endl;
    }
    else if (stdDev >= 0.2) {
        std::cout << "There is a moderate Benford relationship." << std::endl;
    }
    else if (stdDev >= 0.1) {
        std::cout << "There is a very strong Benford relationship." << std::endl;
    }
    else {
        std::cout << "There is not a Benford relationship." << std::endl;
    }
    std::cout << "ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ" << std::endl;
}
/// <summary>
/// Prints a help message from a file
/// </summary>
/// <param name="filename"></param>
void printHelpMessage(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open help file" << std::endl;
    }
}





/// <summary>
/// Main method
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[]) {
  

    std::vector<double> data;
    int numOfElem = 0;
    //Titles program.
    std::cout << "Newcomb-Benford Stats (v2.0.0), copyright 2024 Abdulmuhaimin Ali\n";
    std::cout << "================================================================\n";
    // Check if there is a filename provided as a command line argument
    if (argc > 1) {
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
            return 1;
        }

        double num;
        while (file >> num) {
            if (num > 0) {
                data.push_back(num);
                numOfElem++;
            }
            else {
                std::cerr << "Error: Only numbers greater than zero are accepted. Ignoring input: " << num << std::endl;
            }
            // Clear the error flag and ignore the rest of the line
            if (file.fail()) {
                file.clear();
                std::string line;
                std::getline(file, line);
            }
        }
    }
    else {
        std::cout << "Enter white-space separated real numbers. Terminate input with ^Z\n";
        double num;
        while (std::cin >> num) {
            if (std::cin.fail() || num <= 0) {
                std::cerr << "Error: Invalid input. Please enter only numbers greater than zero." << std::endl;
                // Clear the error flag and ignore the rest of the line
                std::cin.clear();
                std::string line;
                std::getline(std::cin, line);
            }
            else {
                data.push_back(num);
                numOfElem++;
            }
        }
    }

    // Perform standard analysis
    double minVal = minNum(data);
    double maxVal = maxNum(data);
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();

    double median;

    std::sort(data.begin(), data.end());


    if (data.size() % 2 == 0) {
        median = ((data[(data.size() / 2) - 1] + data[(data.size() / 2)]) / 2);
    }
    else {
        median = data[data.size() / 2];
    }

    double variance = 0.0;
    for (double num : data) {
        variance += std::pow(num - mean, 2);
    }
    variance /= data.size();

    double stdDeviation = std::sqrt(variance);

    std::map<double, int> mode = calculateMode(data);

    // Print standard analysis results
    std::cout << "Standard Analysis\n";
    std::cout << "=========================================================\n";
    std::cout << "# elements = " << numOfElem << std::endl;
    std::cout << "Range = [" << minVal << " .. " << maxVal << "]\n";
    std::cout << "Arithmetic mean = " << mean << "\n";
    std::cout << "Arithmetic median = " << median << "\n";
    std::cout << "Variance = " << variance << "\n";
    std::cout << "Standard Deviation = " << stdDeviation << "\n";
    if (mode.size() == 1) {
        std::cout << "Mode = { " << mode.begin()->first << " } x" << mode.begin()->second << " (unimodal)\n";
    }
    else if (mode.size() > 1) {
        std::cout << "Mode = { ";
        for (std::map<double, int>::iterator it = mode.begin(); it != mode.end(); ++it) {
            std::cout << it->first;
            if (std::next(it) != mode.end()) {
                std::cout << ", ";
            }

        }
        std::cout << " } x" << mode.begin()->second << " (multimodal)\n";
    }

    benfordAnalysis(data); 
}
