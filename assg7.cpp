#include <iostream>
using namespace std;

class Graph {
    int AM[100][100], num;
    string data[100];

public:
    Graph(int n) {
        num = n;

        cout << "Enter names of all cities:\n";
        for (int i = 0; i < num; i++) {
            cout << "City " << i + 1 << ": ";
            cin >> data[i];
        }

        cout << "\nEnter the cost to connect cities (0 if no direct connection):\n";
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                if (i == j) {
                    AM[i][j] = 0; // No self-loops
                } else {
                    cout << "Cost to connect " << data[i] << " to " << data[j] << ": ";
                    cin >> AM[i][j];

                    if (AM[i][j] == 0) AM[i][j] = 999999; // No connection
                    AM[j][i] = AM[i][j]; // Symmetric for undirected graph
                }
            }
        }
    }

    void prims() {
        cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
        int visited[100] = {0}, distance[100], from[100] = {0}, cost = 0;

        visited[0] = 1;
        for (int i = 0; i < num; i++)
            distance[i] = AM[0][i];

        for (int count = num - 1; count > 0; count--) {
            int min = 999999, v = -1;

            for (int j = 1; j < num; j++) {
                if (!visited[j] && distance[j] < min) {
                    min = distance[j];
                    v = j;
                }
            }

            if (v == -1) break;

            int u = from[v];
            cout << data[u] << " ==> " << data[v] << "  (cost: " << AM[u][v] << ")\n";
            cost += AM[u][v];
            visited[v] = 1;

            for (int j = 0; j < num; j++) {
                if (!visited[j] && AM[v][j] < distance[j]) {
                    distance[j] = AM[v][j];
                    from[j] = v;
                }
            }
        }

        cout << "Total Cost of MST: " << cost << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    Graph gr(n);

    int choice;
    do {
        cout << "\nMENU:\n";
        cout << "1. Find Minimum Spanning Tree (Prim's Algorithm)\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                gr.prims();
                break;
            case 2:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 2);

    return 0;
}