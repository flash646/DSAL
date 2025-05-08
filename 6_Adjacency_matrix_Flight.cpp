#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

#define MAX_CITIES 100

class Graph {
private:
    int adjMatrix[MAX_CITIES][MAX_CITIES];
    char cities[MAX_CITIES][50];
    int numCities;

public:
    Graph(int n) {
        numCities = n;
        for (int i = 0; i < MAX_CITIES; i++) {
            for (int j = 0; j < MAX_CITIES; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addCity(int index, const char* city) {
        strcpy(cities[index], city);
    }

    int getCityIndex(const char* city) {
        for (int i = 0; i < numCities; i++) {
            if (strcmp(cities[i], city) == 0) {
                return i;
            }
        }
        return -1;
    }

    void addFlight(const char* cityA, const char* cityB, int weight) {
        int indexA = getCityIndex(cityA);
        int indexB = getCityIndex(cityB);

        if (indexA == -1 || indexB == -1) {
            cout << "One or both cities not found!\n";
            return;
        }

        adjMatrix[indexA][indexB] = weight;
        adjMatrix[indexB][indexA] = weight; // bidirectional
    }

    void displayAdjMatrix() {
        cout << "\nAdjacency Matrix:\n";
        cout << setw(10) << "";

        for (int i = 0; i < numCities; i++) {
            cout << setw(10) << cities[i];
        }
        cout << "\n";

        for (int i = 0; i < numCities; i++) {
            cout << setw(10) << cities[i] << " |";
            for (int j = 0; j < numCities; j++) {
                cout << setw(9) << adjMatrix[i][j] << " |";
            }
            cout << "\n";
        }
    }

    void displayAdjList() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < numCities; i++) {
            cout << cities[i] << " -> ";
            bool first = true;
            for (int j = 0; j < numCities; j++) {
                if (adjMatrix[i][j] > 0) {
                    if (!first) cout << " -> ";
                    cout << cities[j] << "(" << adjMatrix[i][j] << ")";
                    first = false;
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    int numCities;
    cout << "Enter number of cities: ";
    cin >> numCities;

    Graph g(numCities);
    char city[50];

    for (int i = 0; i < numCities; i++) {
        cout << "Enter city name: ";
        cin >> city;
        g.addCity(i, city);
    }

    int numFlights;
    cout << "\nEnter number of flights: ";
    cin >> numFlights;

    char cityA[50], cityB[50];
    int weight;

    for (int i = 0; i < numFlights; i++) {
        cout << "\nEnter city A: ";
        cin >> cityA;
        cout << "Enter city B: ";
        cin >> cityB;
        cout << "Enter flight cost/time: ";
        cin >> weight;
        g.addFlight(cityA, cityB, weight);
    }

    g.displayAdjMatrix();
    g.displayAdjList();

    return 0;
}
