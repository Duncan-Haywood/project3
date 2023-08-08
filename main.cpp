/******************************************************************************
* 
* Grocery Tracker Program  
*
* This program implements a simple grocery tracker that reads a list of 
* grocery items purchased from an input file. It stores the items and frequencies  
* in a map, provides options to look up items, print frequencies, and view
* a text histogram. Item lookups are case-insensitive.
*
* The GroceryTracker class handles loading data from file, saving data to file, 
* and implementing the menu options. Two maps are used - one for the main data,
* and one lowercase version for case insensitive lookups.
*
* The program loads the data on startup, saves a backup file, and then presents
* a menu for the user to look up items, print frequencies, view histogram, or exit.
*
* Input File Format:
* One grocery item per line.
* 
* Output File Format: 
* Item Name Frequency
* One item and frequency per line
*
*******************************************************************************/
#include <iostream>
#include <map>
#include <fstream> 
#include <string>

using namespace std;

// GroceryTracker class definition 
class GroceryTracker {

private:

  // Item frequencies map
  map<string, int> itemFrequencies;

  // Lowercase frequencies map for case insensitive lookup
  map<string, int> lowercaseItemFrequencies; 

  // Input data file name
  string inputFileName = "input.txt";

  // Output data file name 
  string outputFileName = "frequency.dat";

public:

  // Constructor
  GroceryTracker() {

    // Load item frequencies from input file
    calculateFrequencies();

    // Save item frequencies to output file
    saveData();

  }

  // Load item frequencies from input file
  int calculateFrequencies() {
    
    // Open input file for reading
    ifstream inputFile(inputFileName);

    // Check if file opened successfully
    if(!inputFile) {
    
      // Print error message and return error code
      cerr << "Unable to open " << inputFileName << endl;
      return -1;

    }
    
    // Read each item from input file
    string item;
    while(inputFile >> item) {

      // If new item, add to map with frequency 1
      if(itemFrequencies.count(item) == 0) {
        itemFrequencies[item] = 1;

      // If existing item, increment frequency  
      } else {
        itemFrequencies[item]++;
      }

    }

    // Populate lowercase frequency map
    copyToLowerCase();
    
    // Close input file
    inputFile.close();

    // Return success code
    return 0;

  }

  // Copy frequencies to lowercase map
  int copyToLowerCase() {
  
    // Loop through main frequency map
    for(auto& [item, frequency] : itemFrequencies) {
    
      // Convert item to lowercase 
      string lowerItem = item;
      transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), ::tolower);

      // Insert lowercase item into lowercase map
      lowercaseItemFrequencies[lowerItem] = frequency;
    
    }

    // Return success code
    return 0;

  }

  // Save frequencies to output file
  int saveData() {

    // Open output file for writing 
    ofstream outputFile(outputFileName);

    // Check if file opened successfully
    if(!outputFile) {
    
      // Print error and return error code
      cerr << "Error opening " << outputFileName << endl;
      return -1;

    }

    // Write frequencies to output file 
    for(auto it = itemFrequencies.begin(); it != itemFrequencies.end(); ++it) {
      outputFile << it->first << " " << it->second << "\n";
    }

    // Close output file
    outputFile.close();

    // Return success code
    return 0;

  }

  // Show menu to user
  void showMenu() {

    // Choice entered by user
    int choice;

    while(true) {
    
      // Print menu options
      cout << string(30, '-') << "\n";
      cout << "1. Look Up Word\n";
      cout << "2. Print All\n";
      cout << "3. Print Histogram\n";
      cout << "4. Exit\n";

      // Get user's choice
      cin >> choice;

      // Validate input
      if(choice < 1 || choice > 4) {
      
        // Invalid choice, print error and retry
        cout << "Invalid choice" << endl;
        continue;

      }

      // Handle user's choice
      if(choice == 4) {
      
        // Exit menu
        break;
      
      } else {

        switch(choice) {
        
          case 1: 
            lookUpWord();
            break;
          case 2:
            printAll();
            break;
          case 3:
            printHistogram();
            break;
        
        }

      }

    }

  }

  // Look up a word
  int lookUpWord() {

    // Get word to look up
    string word;
    cout << string(30, '-') << "\n";
    cout << "Enter word: ";
    cin >> word;

    // Convert to lowercase for comparison
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

    // Check if word exists
    if(lowercaseItemFrequencies.count(lowerWord) == 0) {
    
      // Word not found, print error
      cout << "Word not found" << endl;
      return -1;

    }

    // Print word's frequency
    cout << word << " appears " << lowercaseItemFrequencies[lowerWord] << " times" << endl;

    // Return success code
    return 0;

  }

    // Print all words and frequencies
    int printAll() {

    // Print header
    cout << left << setw(15) << "Item" << "Frequency" << endl;

    // Loop through main frequency map
    for(auto it = itemFrequencies.begin(); it != itemFrequencies.end(); ++it) {

        // Print each item and frequency
        cout << left << setw(15) << it->first << " " << it->second << "\n";

    }

    // Return success code
    return 0;

    }

    // Print histogram
    int printHistogram() {

    // Print header
    cout << left << setw(15) << "Item" << "Frequency" << endl;
    
    // Print dividing line  
    cout << setfill('-') << setw(30) << "" << setfill(' ') << endl;

    // Loop through main frequency map
    for(auto it = itemFrequencies.begin(); it != itemFrequencies.end(); ++it) {

        // Print item left aligned
        cout << left << setw(15) << it->first;

        // Print frequency right aligned 
        cout << right << setw(10) << it->second << " | ";
        
        // Print histogram bars
        for(int i = 0; i < it->second; i++) {
        cout << "*";
        }

        // Move to next line
        cout << endl;

    }

    // Return success code
    return 0;

    }
};

// Main driver code  
int main() {
  GroceryTracker tracker;
  tracker.showMenu();
  return 0;
}