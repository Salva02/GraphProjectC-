#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "problemSolution.h"
#include "problemSolver.h"
using namespace std;
using std::string;

bool importGraphFromFile(const string& filename, Graph& graph, bool isDirected);

int main() {

    Graph graph;
    int scelta = 0;
    int sceltaProblema = 0;
    bool running = true;
    bool validInput = false;
    bool isDirected;
    string file;
    ProblemSolution* lastSolution = nullptr;
    ProblemSolver* solver = nullptr;
    int source = 0;
    int destination = 0;
    string filename;

    cout << "Scegliere una tra le seguenti opzioni (1-5):\n";
    cout << "1. importare un grafo\n";
    cout << "2. risolvere un problema di ottimizzazione\n";
    cout << "3. stampare la soluzione\n";
    cout << "4. esportare la soluzione su file di testo\n";
    cout << "5. uscire dal programma\n";


    do {
        cout << "********************" << endl;  
        cin >> scelta;
        switch(scelta) {
        case 1:
            cout << "inserire il nome di un file (con l'estensione): \n";
            cin >> file; //inserire il nome di un file in directory
            cout << "Si vuole che il grafo sia orientato? (0 no, 1 si)" << endl;
            cin >> isDirected; // scelta per grafo orientato/non orientato
            if (importGraphFromFile(file, graph, isDirected)) {
                cout << "Grafo importato: " << endl; 
                graph.print();
            } else {
                cerr << "Errore durante la lettura del grafo!" << endl;
            }
            break;
        case 2:
            cout << "Scegliere il problema che si vuole risolvere: " << endl;
            /*per scegliere un problema da risolvere si usa un altro switch annidato, ma prima si 
            cancella la soluzione precedente in memoria così da poter salvare quella nuova*/
            if(lastSolution) {
                delete lastSolution;
                lastSolution = nullptr;
            }

            if (solver) {
                delete solver;
                solver = nullptr;
            }
            cout << "1: minimum spanning tree" << endl;
            cout << "2: single-pair shortest path problem" << endl;
            cout << "3: single-source shortest path problem" << endl;
            cout << "4: all-pairs shortest path" << endl;
            cin >> sceltaProblema;

            switch(sceltaProblema) {
                case 1:
                    solver = new MSTSolver();
                    lastSolution = solver->solve(graph);
                    cout << "Problema risolto!" << endl;
                    break;
                case 2:
                    validInput = false;
                    while (!validInput) {
                        cout << "Inserire un nodo di partenza e un nodo di arrivo: " << endl;
                        cin >> source >> destination;

                        // Controllo per verificare che i nodi siano validi
                        if (source < 0 || source >= graph.numVertices()) {
                            cout << "Errore: il nodo di partenza non esiste nel grafo. Inserire un nodo tra 0 e " 
                            << graph.numVertices() - 1 << "." << endl;
                        } else if (destination < 0 || destination >= graph.numVertices()) {
                            cout << "Errore: il nodo di arrivo non esiste nel grafo. Inserire un nodo tra 0 e " 
                            << graph.numVertices() - 1 << "." << endl;
                        } else {
                            validInput = true;  // Entrambi i nodi sono validi
                        }
                    }

                    //risoluzione solo se i nodi sono validi
                    solver = new SPSPSolver(source, destination);
                    lastSolution = solver->solve(graph);
                    cout << "Problema risolto!" << endl;
                    break;
                case 3:
                    validInput = false;
                    while (!validInput) {
                        cout << "Inserire un nodo di partenza: " << endl;
                        cin >> source;

                        // Controllo per verificare che il nodo sia valido
                        if (source < 0 || source >= graph.numVertices()) {
                            cout << "Errore: il nodo inserito non esiste nel grafo. Inserire un nodo tra 0 e " 
                            << graph.numVertices() - 1 << "." << endl;
                        } else {
                            validInput = true; // Il nodo è valido
                        }
                    }

                    // risoluzione solo se il nodo è valido
                    solver = new SingleSourceSolver(source);
                    lastSolution = solver->solve(graph);
                    cout << "Problema risolto!" << endl;
                    break;
                case 4:
                    validInput = false;
                    solver = new APSPSolver();
                    lastSolution = solver->solve(graph);
                    cout << "Problema risolto!" << endl;
                    break;
                default:
                    cout << "scelta non valida!" << endl;
                    break;
            }
            break;
        case 3:
            cout << "Soluzione del problema scelto: " << endl;
            lastSolution->output(cout); // stampa la soluzione su standard output
            break;
        case 4:
            cout << "Esportare la soluzione su file...." << endl;
            cout << "Inserire il nome che si vorrebbe dare al file: ";
            cin >> filename;
            lastSolution->exportSolution(filename); //crea un file con la soluzione attualmente salvata
            cout << "Soluzione esportata nel file " << filename << endl;
            break;
        case 5:
            cout << "Chiusura del programma" << endl;
            if (lastSolution) {
                delete lastSolution;
            }
            if (solver) {
                delete solver;
            }
            running = false;
            break;
        default: 
            cout << "Inserire un numero da 1 a 5!" << endl;
        }

        // ripeto il menù dopo ogni scelta
        if (scelta != 5) {
            cout << "********************" << endl;
            cout << "Scegliere una tra le seguenti opzioni (1-5):\n";
            cout << "1. importare un grafo\n";
            cout << "2. risolvere un problema di ottimizzazione\n";
            cout << "3. stampare la soluzione\n";
            cout << "4. esportare la soluzione su file di testo\n";
            cout << "5. uscire dal programma\n";
        }

    } while(running);
    


    return 0;
    
}

bool importGraphFromFile(const std::string& filename, Graph& graph, bool isDirected) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File not found!" << std::endl;
        return false;
    }

    graph.clear(); // cancella il grafo prima di importarne uno nuovo

    std::string line;
    bool skipHeader = true; // Variabile per tenere conto dell'intestazione

    while (getline(file, line)) {
        // Se è l'intestazione, salta
        if (skipHeader) {
            if (line.find("NAME") != std::string::npos) {
                skipHeader = false;
            }
            // Salto alla riga dopo
            continue;
        }

        // Se è una riga con dati, la analizza
        if (!line.empty()) {
            int u, v, w;
            // Cerca tre interi e li memorizza nelle variabili u, v, w
            if (sscanf(line.c_str(), "%d %d %d", &u, &v, &w) == 3) {
                // Aggiunge l'arco al grafo
                graph.addEdge(u, v, w);
                
                // Se il grafo non è orientato, aggiunge anche l'arco inverso
                if (!isDirected) {
                    graph.addEdge(v, u, w);
                }
            }
        }
    }

    file.close();
    return true;
}
