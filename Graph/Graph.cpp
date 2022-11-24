#include <iostream>
#include <vector>

using namespace std;

struct Edge { //ребро графа
    int source; // Исходная вершина
    int destination; // Конечная вершина
    int weight; //вес ребра

    Edge() {} // конструкторы
    Edge(int source, int destination, int weight) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
    void print() {
        cout << source << "<------>" << destination << "\t(" << weight << ")" << endl;
    }
};

class Graph {
private:
    int verticesNum;  // количество вершин в графе
    int edgesNum;  // количество ребер в графе
    vector<Edge> edges; // массив ребер 
    int** matrix; // матрица смежности
    vector<Edge*> graph; //минимальный остовный граф
public:
    Graph(int vnum, int edgnum) { //конструктор, аргументы - числа вершин и ребер
        this->verticesNum = vnum;
        this->edgesNum = edgnum;
        // осуществляем "заполнение" графа
        for (int i = 0; i < edgnum; i++)
        {
            // x, y - номера соединенных вершин, w - вес ребра, соед. x и y
            int x, y, w;
            // считываем информацию о каждом ребре
            cout << "Введите 2 вершины и вес ребра: ";
            cin >> x >> y >> w;
            Edge e(x, y, w); // создаем объекта классы ребра
            edges.push_back(e); // добавляем его в наш массив
        }

        this->matrix = new int* [verticesNum+1]; //создаем матрицу смежности
        for (int i = 0; i <= verticesNum; i++) {
            this->matrix[i] = new int[verticesNum+1];
        }
        for (int i = 0; i <= verticesNum; i++) {
            for (int j = 0; j <= verticesNum; j++) {
                this->matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < edges.size(); i++) {
            Edge edge = edges[i];
            matrix[edge.source][edge.destination] = edge.weight;
            matrix[edge.destination][edge.source] = edge.weight;
        }
    }

    void printGraph() {
        for (int i = 0; i < graph.size(); i++) {
            graph[i]->print();
        }
    }

    bool isValidEdge(int x, int y, bool* flag)
    {
        if (x == y) // одна и та же вершина
            return false;
        if (!flag[x] && !flag[y]) // ни одна вершина не участвует в остовном графе
            return false;
        else if (flag[x] && flag[y]) // две вершины уже есть в остовном графе
            return false;
        else {
            return true;
        }
    }

    void primMST() {
        bool* flag = new bool[verticesNum+1]; // массив обработанных вершин. Изначально все не обработаны:
        memset(flag, false, verticesNum + 1);
        flag[0] = true; // посещаем начальную вершину
        int count = 0;
        while (count < verticesNum - 1) {
            int min = INT_MAX, a = -1, b = -1;
            for (int i = 0; i < verticesNum; i++) {
                for (int j = 0; j < verticesNum + 1; j++) {
                    if (matrix[i][j] < min) {
                        if ((isValidEdge(i, j, flag)) && matrix[i][j]) {
                            min = matrix[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
            if (a != -1 && b != -1) {
                graph.push_back(new Edge(a, b, matrix[a][b]));
                cout << a << " - " << b << " : " << matrix[a][b] << endl;
                flag[b] = flag[a] = true;
            }
            count++;
        }
    }
};




int main()
{
    cout << "Введите число вершин и ребер";
    int a, b;
    cin >> a >> b;
    Graph g(a,b);
    g.primMST();
    cout << "Остовный граф:";
    g.printGraph();
}