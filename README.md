# GraphProjectC-

Classi implementate:
- classe Graph → la classe grafo viene implementata mediante una struct “Edge” che
contiene il nodo di partenza (u), il nodo di arrivo (v) e il peso dell’arco.
Successivamente è presente un default constructor e le funzioni necessarie per
l’implementazione:
1) void addEdge(int u, int v, int w) → aggiunge un arco al grafo;
2) void clear() → cancella il grafo corrente salvato in memoria;
3) void print() const → stampa il grafo;
4) int numVertices() const → ritorna il numero di vertici presenti;
5) const std::vector<Edge>& getEdges() const → ritorna il numero di archi;
Nella parte privata della classe si hanno anche un vettore “edges” che contiene gli
archi del grafo e un int “num_vertices” che contiene i vertici del grafo.
- classe ProblemSolution → la classe ProblemSolution è utile per implementare
della classi che ereditano da quest’ultima per stampare/esportare le varie soluzioni.
Sono presenti solo funzioni virtuali che verranno implementate nelle classi che
erediteranno e servono a stampare ed esportare la soluzione. Si ha anche un default
destructor, oltre alle funzioni output per stampare la soluzione a schermo ed
exportSolution per esportare la soluzione in un file di testo.
- classe MST → è la classe che implementa il problema “minimum spanning tree” ed
eredita da ProblemSolution. Si ha un vettore che contiene gli archi e un intero che
contiene il peso totale degli archi; dopo il costruttore si hanno le funzioni:
1) std::ostream& output(std::ostream& os) const override → stampa la soluzione
a schermo mediante l’uso di un ciclo for; la soluzione comprende nodo di partenza,
nodo di arrivo e il peso dell’arco che li unisce. Inoltre è anche riportato il peso totale
di tutti gli archi.
2) void exportSolution(const std::string& filename) const override → il principio
è lo stesso della funzione precedente, ma in questo caso la soluzione viene anche
salvata su un file di testo il cui nome viene dato in input dall’utente.
- classe ShortestPathSolution → contiene le stesse funzioni della classe precedente
in quanto eredita sempre da ProblemSolution; in questo caso le due funzioni
contengono il percorso più corto possibile dato un nodo di partenza e uno di arrivo
(scelti dall’utente), nel caso in cui esista. Si ha un if che verifica che il vettore
shortestPath non sia vuoto (i due nodi non sono connessi), nel caso in cui non lo sia
si stampa il percorso più breve. Si itera il vettore con un ciclo for in cui si stampa il
nodo corrente, così alla fine del ciclo si avrà il percorso completo con ogni nodo
collegabile. Alla fine viene anche stampata la distanza totale.
- classe SingleSourceSolution → in questo caso le funzioni restituiscono il percorso
da un nodo di partenza a tutti gli altri nodi di un grafo; viene specificato per ogni
nodo presente nel grafo, se è possibile raggiungerlo dal nodo partenza e in caso il
peso del percorso necessario. Il funzionamento è il seguente: si ha un ciclo for che
itera tutti i nodi del grafo in esame, nel caso in cui il nodo corrente sia corrispondente
al nodo di partenza scelto dall’utente lo si salta. Successivamente si ha un if per
verificare se la distanza tra i e source sia raggiungibile (si usa
std::numeric_limits<int>::max(), che rappresenta l’infinito e quindi indicherebbe
che il nodo sia irraggiungibile). A seconda della funzione usata il risultato sarà
restituito in output o su file.
- classe APSPSolution → utilizza le funzioni per restituire una matrice v*v (dove v è
il numero di vertici del grafo) nella quale si trovano le distanze più brevi tra ogni
coppia di nodi e la distanza da un nodo a sé stesso è sempre 0. Nel caso in cui la
distanza non esista si usa la sigla “INF” per indicare che non vi è alcun percorso e
anche perché la funzione std::numeric_limits<int>::max() utilizzata per
determinarlo rappresenta un numero simile all’infinito (non vi è percorso tra i due
nodi).
- classe ProblemSolver → la classe presenta un default constructor e una funzione
virtual ProblemSolution* solve(const Graph&) = 0 che implementa le soluzioni
vere e proprie.
- classe MSTSolver → eredita da ProblemSolver e presenta le seguenti funzioni:
1) int find(int u, vector<int>& parent): serve a trovare ricorsivamente la radice
dell’insieme a cui appartiene l’elemento u; nel caso di minimum spanning tre, cerca
la componente connessa a cui appartiene un nodo e unisce i nodi che si trovano in
componenti diverse. Ogni nodo ha un genitore e inizialmente ciascun nodo è il
proprio genitore; il caso base è che u != parent, quindi è la radice del suo insieme. In
questo caso vuol dire che u avrà un genitore diverso, quindi si richiama
ricorsivamente find per trovare effettivamente in genitore. Una volta trovata la
radice, quindi, si aggiorna parent[u] per farlo puntare alla radice trovata.
Se u == parent significa che è il rappresentante del suo insieme e può essere
restituito.
2) void unionSets(int u, int v, vector<int>& parent, vector<int>& rank): unisce
due insiemi disgiunti a cui appartengono i nodi u e v. Il vettore parent memorizza il
genitore di ogni nodo, che inizialmente è il proprio genitore. Il vettore rank
memorizza il grado di ogni nodo, rappresenta l’altezza approssimativa dell’albero.
Si utilizza find per trovare la radice a cui appartengono u e v, che saranno rootU e
rootV. Se sono diversi, vuol dire che u e v sono in due insiemi disgiunti e vanno uniti;
a seconda di chi ha il rango maggiore si decide come devono essere uniti così da
garantire che l’altezza dell’albero rimanga minima.
3) ProblemSolution* solve(const Graph& graph) override: usa l’algoritmo di
Kruskal, quindi cerca un insieme di archi che collega tutti i nodi mantenendo il peso
totale degli archi minimo.
Chiama getEdges() per ottenere gli archi del grafo, per poi ordinarli in modo
crescente con la funzione sort. Successivamente si inizializza ogni nodo in modo che
sia il proprio genitore e in un altro ciclo for che itera su tutti gli archi ordinati si cerca
se u e v appartengono a insiemi diversi, in quel caso si può aggiungere l’arco (unendo
gli insiemi con unionSets) nell’MST senza che formi un ciclo.
Una volta completato tutto il ciclo la funzione restituisce un oggetto che contiene gli
archi appartenenti al minimum spanning tree e il peso totale dell’albero, ricordando
che un grafo di n nodi conterrà sempre n-1 archi.
- classe SPSPSolver → implementa una soluzione per il Single Pair Shortest Path.
La funzione calcola il percorso più breve dal nodo sorgente source a ogni altro nodo
del grafo utilizzando l'algoritmo di Dijkstra. Se il nodo di destinazione è
raggiungibile, costruisce il percorso e lo restituisce; se il nodo non è raggiungibile, la
distanza rimarrà impostata a infinito. La funzione restituisce un’istanza che contiene
il vettore con il percorso più breve e la distanza totale per raggiungere il nodo finale.
- classe SingleSourceSolver → presenta ancora una volta la funzione solve, questa
volta utilizzando l’algoritmo di Dijkstra per trovare il cammino da un singolo nodo di
partenza a tutti gli altri nodi presenti all’interno del grafo. La distanza dal nodo
sorgente a sé stesso è impostata a 0 e si inserisce nella coda di priorità;
successivamente si itera con un ciclo while estraendo il nodo con la minima distanza
e rimuovendolo dalla coda. Si esaminano poi tutti gli archi in uscita dal nodo estratto
e si calcola il nodo di destinazione (più il peso dell’arco per arrivarci). Se il cammino
trovato migliora la distanza correntemente in memoria per arrivare a quel nodo, si
aggiorna la distanza e si registra il nodo come predecessore.
Al termine si restituisce un’istanza con le distanze minime e tutti i predecessori con la
sorgente utilizzata.
- classe APSPSolver → la fuunzione solve utilizza una matrice a due dimensioni in
cui ogni singola distanza/peso è inizialmente inizializzata a 0, successivamente si
utilizza un ciclo for per inserire le varie distanze del grafo in esame. Si hanno poi tre
cicli for annidati in cui per ogni coppia di nodi si cerca se esista un percorso più breve
usando un nodo intermedio.
Per quanto riguarda la lettura della tabella si incrocia il numero di riga con il numero
di colonna per vedere il peso distanza tra i nodi corrispondenti rispettivamente alla
riga e alla colonna.
Questo è un esempio della funzione in output: se si vuole cercare la distanza tra il
nodo 0 e il nodo 7 non si dovrà fare altro che incrociare la riga 0 (prima riga) con la
colonna 7 (ottava colonna, si parte sempre da 0). Una volta fatto si otterrà che la
distanza è 86, questo è un caso di grafo orientato.
- main → nel main si utilizza un ciclo do while per stampare il menù a schermo e
successivamente permettere all’utente di prendere delle scelte con un numero da 1 a
5. A seconda della scelta si ha uno switch che permette di eseguire le opzioni scritte
precedentemente nel menù:
1) case 1: si inserisce il nome di un file per importare un determinato grafo; per fare
ciò si ricorre all’utilizzo della funzione importGraphFromFile. Nel caso ci sia già
un grafo presente in memoria, la funzione lo cancella e ne importa uno nuovo, per
importarlo controlla che la riga corrente non sia l’intestazione del file, nel caso sia
una riga con dei dati utilizza uno sscanf per aggiungere i vari archi (con la funzione
addEdge di Graph).
2) case 2: permette di scegliere un problema da risolvere; si ha un altro switch
annidato che permette di risolvere i diversi problemi e di inserire eventualmente i dati
necessari (nodi di partenza/arrivo).
3) case 3: stampa la soluzione a schermo mediante l’uso della funzione output.
4) case 4: esporta la soluzione su file mediante l’uso della funzione exportSolution.
5) chiude il programma.
Si ha anche un caso di default per assicurarsi che l’utente immetta solo numeri
compresi tra 1 e 5.
NOTA: in alcuni problemi di ottimizzazione il risultato varia a seconda che il grafo
sia orientato oppure no; per questo motivo, nel momento in cui si importa il file, si da
all’utente la possibilità di scegliere se vuole che il grafo sia orientato o meno. Si
utilizza una variabile booleana che viene data in input alla funzione
importGraphFromFile. Nel caso in cui il grafo non sia orientato non si fa altro che
aggiungere due archi anziché uno: il primo arco da x a y e il secondo arco da y a x
con lo stesso peso; in questo modo le funzioni lavoreranno allo stesso modo in
entrambi i casi.
