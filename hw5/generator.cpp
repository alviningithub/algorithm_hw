#include <iostream>
#include <fstream>  // For file operations
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Function to generate a single test case
vector<int> generateTestCase(int numElements, int lowerBound, int upperBound) {
    vector<int> testCase;
    for (int i = 0; i < numElements; i++) {
        // Generate a random integer between lowerBound and upperBound
        int randomNum = lowerBound + rand() % (upperBound - lowerBound + 1);
        testCase.push_back(randomNum);
    }
    return testCase;
}

// Function to generate multiple test cases and save them to a file
void generateTestCases(int numTestCases, int numElements, int lowerBound, int upperBound, const string& filename) {
    ofstream outFile(filename); // Open file for writing

    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }
    
    for (int i = 0; i < numTestCases; i++) {
        outFile<< 10<<" "<<10<<"\n";
        for(int j=0;j<10;j++){
            vector<int> testCase = generateTestCase(1,-1000000000, 1000000000);
            for (int num : testCase) {
                outFile << num << " ";
            }
            vector<int> testCase2 = generateTestCase(1,1,1000000000);
            for (int num : testCase2) {
                outFile << num << " ";
            }
            vector<int> testCase3 = generateTestCase(1,0,1000000000);
            for (int num : testCase3) {
                outFile << num << " ";
            }
            outFile<<endl;
        }
        
        vector<int> testCase = generateTestCase(10,-1000000000,1000000000);
        for (int num : testCase) {
            outFile << num << " ";
        }

        // Write the test case to the file
        //outFile << "Test Case " << i + 1 << ": ";
        outFile << endl;
        outFile << endl;

    }

    outFile.close(); // Close the file after writing
    cout << "Test cases saved to " << filename << endl;
}

int main() {
    // Initialize random seed
    srand(time(0));

    int numTestCases, numElements, lowerBound, upperBound;
    string filename;

    // Input the number of test cases, number of elements in each test case, bounds for random numbers, and the output filename
    cout << "Enter the number of test cases: ";
    cin >> numTestCases;

    cout << "Enter the number of elements in each test case: ";
    cin >> numElements;

    cout << "Enter the lower bound for random numbers: ";
    cin >> lowerBound;

    cout << "Enter the upper bound for random numbers: ";
    cin >> upperBound;

    cout << "Enter the output file name (with .txt extension): ";
    cin >> filename;

    // Generate the test cases and save them to a file
    generateTestCases(numTestCases, numElements, lowerBound, upperBound, filename);

    return 0;
}
