#include <iostream>
#include <vector>

using namespace std;

struct Edge { //ребро графа
    int source; // Исходная вершина
    int destination; // Конечная вершина
    int weight; //вес ребра

    Edge(){} // конструкторы
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

        this->matrix = new int*[verticesNum]; //создаем матрицу смежности
        for (int i = 0; i < verticesNum; i++) {
            this->matrix[i] = new int[verticesNum];
        }
        for (int i = 0; i < verticesNum; i++) {
            for (int j = 0; j < verticesNum; j++) {
                this->matrix[i][j] = 0;
        }
        }
        for (int i = 0; i < edges.size(); i++) {
            Edge edge = edges[i];
            matrix[edge.source][edge.destination] = edge.weight;
            matrix[edge.destination][edge.source] = edge.weight;
        }
    }


    Edge* primAlg(int start) { //алгоритм прима
            vector not_used
        }
};




int main()
{
    std::cout << "Hello World!\n";
}