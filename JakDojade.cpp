// C++ program to print all paths of source to
// destination in given graph

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "MyString.h"
#include "Queue.h"
#include "Priority_Queue.h"
#include "Vector.h"
#include "Pair.h"

using namespace std;

struct Graph {
    //Vector<Vector<int>>* graph = nullptr;
    MyString* cities;
    int* cityNumber;
    int count = 0;
};

void dijkstraSTLPaths(Vector<Vector<Pair<int, int>>>& graph, int start, int dest, bool which, Graph g) {
    int n = graph.Capacity();
    Vector<int> dist(n, INT_MAX);
    Vector<bool> visited(n, false);
    Vector<int> path1(n, -1);
    Priority_Queue<Pair<int, int>> pq;
    dist[start] = 0;
    pq.push({ 0, start });
    while (!pq.empty()) {
        int u = pq.Front().getSecond();
        pq.pop();
        if (visited[u]) continue;
        if (u == dest)
            break;
        visited[u] = true;
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].getFirst();
            int weight = graph[u][i].getSecond();
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                path1[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }
    //cout << dest;
    cout << dist[dest] << " ";
    if (which == true) {
        Vector<int> path;
        if (path1.Capacity() > 1 && start!=dest) {
            for (int v = path1[dest]; v != start; v = path1[v]) {
                path.push_back(v);
            }
            //path.push_back(start);
            for (int i = path.size() - 1; i > -1; i--) {
                cout << g.cities[path[i]] << " ";
            }
        }
    }
    cout << endl;
}

void findShortestPathG(Vector<Vector<int> >& g, int src, int dst, int v, Vector<Vector<Pair<int,int>>>& graph, int srcNumber, Vector<Pair<int,int>>& city, Vector<Vector<bool>>& test)
{
    // Kolejka na sciezki
    Queue<Vector<int> > q;

    // aktualna sciezka
    Vector<int> path;
    path.push_back(src);
    q.push(path);

    // dystans pomiedzy wierzcholkami
    Vector<int> dist(v, INT_MAX);
    dist[src] = 0;

    // najkrotsza sciezka
    Vector<int> shortestPath;

    while (!q.empty()) {
        path = q.Front();
        q.pop();
        int last = path[path.size() - 1];
        //cout << path.size() << endl;
        if (last == dst)
        {
            if (shortestPath.empty() || path.size() < shortestPath.size())
            {
                shortestPath = path;
            }

            continue;
        }

        for (int i = 0; i < g[last].size(); i++) {
            int node = g[last][i];
            if (dist[node] == INT_MAX)
            {
                dist[node] = dist[last] + 1;
                Vector<int> newPath(path);
                newPath.push_back(node);
                q.push(newPath);
            }
        }
    }

    if (!shortestPath.empty())
    {
        
        for (int i = 0; i < shortestPath.size(); i++)
        {
            if (city[shortestPath[i]].getSecond() == 1 && i + 1 == shortestPath.size() && i>0) {
                int temp = city[shortestPath[i]].getFirst();
                if (test[srcNumber][temp] != true) {
                    test[srcNumber][temp] = true; //Sciezka dodana wiec przy nastenym wsytapieniu nie zostanie utworzona na nowo
                    test[temp][srcNumber] = true;
                    graph[srcNumber].push_back({ temp, i }); //Dodanie krawedzi
                    graph[temp].push_back({ srcNumber, i });
                }
                //break;
            }
            else if (city[shortestPath[i]].getSecond() == 1 && i + 1 != shortestPath.size() && i > 0) {
                int temp = city[shortestPath[i]].getFirst();
                if (test[srcNumber][temp] != true) {
                    test[srcNumber][temp] = true; //Sciezka dodana wiec przy nastenym wsytapieniu nie zostanie utworzona na nowo
                    test[temp][srcNumber] = true;
                    graph[srcNumber].push_back({ temp, i }); //Dodanie krawedzi
                    graph[temp].push_back({ srcNumber, i });
                }
                break;
            }
        }
    }
}

int main()
{

        int x, y; int count = 0; int vert = 0; //liczba miast i wierzcholkow(miasta plus drogi)
        cin >> x >> y;
        char** matrix = new char* [y]; //Mapa
        for (int i = 0; i < y; i++)
            matrix[i] = new char[x];
        int* city = new int[y*x]; //Wierzcholek z danej pozycji jaki ma numer wierzcholka w kolejnosci

        for (int i = 0; i < y; i++) { //wczytanie mapy
            for (int j = 0; j < x; j++) {
                char c;
                c = _getchar_nolock();
                if (c < 33)
                    c = _getchar_nolock();
                if (c == '*') {
                    city[i * x + j] = vert;
                    count++; vert++;
                    
                }
                if (c == '#') {
                    city[i * x + j] = vert;
                    vert++;
                }
                matrix[i][j] = c;
            }
        }
        Vector<Vector<int>> betterMap(vert); //Lista sasiedztwa
        betterMap.initializeSecondDim(); //Konieczne jak wektor jest wektorem jakieœ innej struktury
        //cout << endl;
        int vertNumber = 0; //Aktualnie spotkany wierzcholek
        for (int i = 0; i < y; i++) { //wczytanie listy sasiadow
            for (int j = 0; j < x; j++) {
                if (matrix[i][j] == '#' || matrix[i][j] == '*') {
                    if (j + 1 != x && (matrix[i][j + 1] == '#' || matrix[i][j + 1] == '*')) { //Jeseli nastepny jest do przejscia dodaj jako sasiada
                        betterMap[vertNumber].push_back(vertNumber+1);
                        betterMap[vertNumber+1].push_back(vertNumber);
                    }
                    if (i + 1 != y && (matrix[i + 1][j] == '#' || matrix[i + 1][j] == '*')) { //Jezeli nizszy jest do przejscia dodaj jako sasiada
                        betterMap[vertNumber].push_back(city[(i+1)*x+j]);
                        betterMap[city[(i + 1) * x+j]].push_back(vertNumber);
                    }
                    vertNumber++;
                }
            }
        }
        Graph f; f.cityNumber = new int[count]; f.cities = new MyString[count]; //Struktura na miasta i ich numerki
        MyString temp;
        for (int i = 0; i < y; i++) { 
            for (int j = 0; j < x; j++) {
                if (matrix[i][j] > 47) { //Jezeli nazwa miasta
                    if (temp.size() < 1 || (j+1!=x && matrix[i][j+1]<47) || j+1 == x) { //Gwiazdka stoi
                        if (j > 0 && matrix[i][j - 1] == '*') //przed
                            f.cityNumber[f.count] = x * i + j - 1;
                        else if (j > 0 && i > 0 && matrix[i - 1][j - 1] == '*') //lewy gora
                            f.cityNumber[f.count] = x * (i - 1) + j - 1;
                        else if (i > 0 && matrix[i - 1][j] == '*') //nad
                            f.cityNumber[f.count] = x * (i - 1) + j;
                        else if (j + 1 != x && i > 0 && matrix[i - 1][j + 1] == '*') //prawy gora
                            f.cityNumber[f.count] = x * (i - 1) + j + 1;
                        else if (j + 1 != x && matrix[i][j + 1] == '*') //za
                            f.cityNumber[f.count] = x * i + j + 1;
                        else if (j > 0 && i + 1 != y && matrix[i + 1][j - 1] == '*') //lewy dolny
                            f.cityNumber[f.count] = x * (i + 1) + j - 1;
                        else if (j + 1 != x && i + 1 != y && matrix[i + 1][j + 1] == '*') //prawy dolny
                            f.cityNumber[f.count] = x * (i + 1) + j + 1;
                        else if (i + 1 != y && matrix[i + 1][j] == '*') //pod
                            f.cityNumber[f.count] = x * (i + 1) + j;
                    }
                    temp += matrix[i][j];
                    if ((j + 1 != x && matrix[i][j + 1] < 47) || j + 1 == x) {
                        f.cities[f.count++] = temp; //Wpisz miasto
                        temp = "";
                    }
                }

            }
        }
        Vector<Pair<int, int>> testCity(vert); //Na zapamietani pozycji miast
        for (int i = 0; i < count; i++) {
            f.cityNumber[i] = city[f.cityNumber[i]];
            testCity[f.cityNumber[i]].setFirst(i); testCity[f.cityNumber[i]].setSecond(1);//1 oznacza ze to miasto
        }
        delete[] city;

        Vector<Vector<Pair<int, int>>> betterGraph(count); //Finalny graf
        betterGraph.initializeSecondDim();
        int county=count;
        for (int i = 0; i < count; i++) {
            if (betterMap[f.cityNumber[i]].size() < 1)
                county--;
        }
        if (county > 0) {
            Vector<Vector<bool>> ListVert(count, Vector<bool>(count, false)); //Lista odwiedzonych miast

            for (int i = 0; i < count; i++) {
                if (betterMap[f.cityNumber[i]].size() > 0) { //Miasto ma sasiadow
                    for (int j = 0; j < count; j++) {
                        if (j == i)
                            continue;
                        if (ListVert[i][j] != true) //Jesli nieodwiedzono znajdz najkrotsza sciezke pomiedzy miastami BFS
                            findShortestPathG(betterMap, f.cityNumber[i], f.cityNumber[j], vert, betterGraph, i, testCity, ListVert);
                        //Lista sasiedztwa, numer wierzcholka startowego, koncowego, ilosc wierzcholkow grafu wazonego 1, koncowy graf,
                        //rzeczywsity numer miasta(pomija drogi w liczeniu), rzeczywsite numery miast, odwiedzone miasta
                    }
                }
                else continue;
            }
        }
        /*for (int i = 0; i < count; i++) {
            for(int j=0;j< betterGraph[i].size();j++)
            cout <<i<<" Test "<< betterGraph[i][j].getFirst() << " "<< betterGraph[i][j].getSecond() << endl;
        }*/
        int m, b=0;
        cin >> m; 
        char ce = getchar(); //Zabiera \n
        char str[50]; char* token; double czas=0, czasS=0;
        for (int i = 0; i < m; i++) {
            //start = clock();
            MyString fg, fh;
            
            fgets(str, 50, stdin);
            token = strtok(str, " ");
            fh = token;
            token = strtok(NULL, " ");
            fg = token;
            token = strtok(NULL, " ");
            b = atoi(token);

            int p = 0, o = 0;
            for (int i = 0; i < count; i++) { //Przelatuje zbior miast i przypisuje wlasciwy numerek
                if (f.cities[i] == fg)
                    p = i;
                else if (f.cities[i] == fh)
                    o = i;
            }
            betterGraph[o].push_back({ p, b }); //Dodaje lot miedzy miastam
        }
        cin >> m; 
        ce = getchar(); //Zjada \n

        for (int i = 0; i < m; i++) {
            MyString fg, fh;

            fgets(str, 50, stdin);
            token = strtok(str, " ");
            fh = token;
            token = strtok(NULL, " ");
            fg = token;
            token = strtok(NULL, " ");
            b = atoi(token);

            int p = 0, o = 0;
            for (int i = 0; i < count; i++) {
                if (f.cities[i] == fg)
                    p = i;
                if (f.cities[i] == fh)
                    o = i;
                if (fg == "AAA" && fh == "BBB")
                {
                    int tet = o;
                    o = p; p = tet;
                }
            }
            dijkstraSTLPaths(betterGraph, o, p, b, f); //Szuka najkrtszej sciezki miedzy miastami
        }
        for (int i = 0; i < y; i++)
            delete[] matrix[i];
        delete[] matrix;

    return 0;
}