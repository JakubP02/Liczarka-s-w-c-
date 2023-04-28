#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "CharacterCounter.h"
#include <numeric>
#include "WordCounter.h"

using namespace std;

// funkcja, która będzie wykonywana przez wątek
void threadFunction(string text, int startIndex, int endIndex, int& count) {
    CharacterCounter counter;
    counter.count(text, startIndex, endIndex, count);
}

int main() {

    int choice = 0;

    while (choice != 1)
    {
        cout << "Co chcesz zrobic?" << endl;
        cout << "1. Wyjscie" << endl;
        cout << "2. Zlicz znaki w tekscie" << endl;
        cout << "Wybierz opcje: ";

        cin >> choice;
        if (cin.fail()) {
            cout << "Blad! Wprowadzono nieprawidlowa wartosc.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {


            if (choice == 2) {
                // pobieramy tekst od użytkownika
                cout << "Podaj tekst:" << endl;
                cin.ignore();
                string text;
                getline(cin, text);

                // pobieramy liczbę wątków z procesora
                int numThreads = thread::hardware_concurrency();
                cout << "Liczba watkow: " << numThreads << endl;

                // jeśli liczba znaków jest mniejsza lub równa liczbie wątków, to wykorzystujemy tylko jeden wątek
                if (text.size() <= numThreads) {
                    int count = 0;
                    threadFunction(text, 0, text.size(), count);
                }


                // dzielimy tekst na równe części dla każdego wątku
                int partSize = text.size() / numThreads;
                vector<int> counts(numThreads);
                vector<thread> threads;

                for (int i = 0; i < numThreads; i++) {
                    int startIndex = i * partSize;
                    int endIndex = (i == numThreads - 1) ? text.size() : (i + 1) * partSize;

                    threads.push_back(thread(threadFunction, text, startIndex, endIndex, ref(counts[i])));
                }

                // czekamy na zakończenie pracy wszystkich wątków
                for (auto& th : threads) {
                    th.join();
                }


                // Wyświetl wyniki
                int totalcharacters = 0;
                for (unsigned int i = 0; i < numThreads; i++) {
                    totalcharacters += counts[i];
                    cout << "Watek " << i << ": "<<"przetworzyl " << counts[i] << " znakow " << endl;
                }
                cout << "Liczba znakow: " << totalcharacters << endl;
            }

          
        }
    }
    
    cout << "Koniec programu." << std::endl;
    return 0;


} 