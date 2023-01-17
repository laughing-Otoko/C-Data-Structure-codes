#ifndef GRAPHTYPE_H
#define GRAPHTYPE_H
#include <iostream>
#include <cassert>
#include <fstream>
#include "linkedlist.h"
#include "queue.h"

using namespace std;

class graphType
{
public:
	bool isEmpty() const;
	void createGraph();
	void clearGraph();
	void printGraph() const;
	//void depthFirstTraversal();
	//void dftAtVertex(int vertex);
	void breadthFirstTravesal();
	graphType(int size = 0);
	~graphType();

protected:
	int maxSize;
	int gSize;
	unorderedLinkedList<int>* graph;

private:
	//void dft(int v, bool visited[]);
};

class weightedGraphType : public graphType
{
public:
	void createWeightedGraph();
	void shortestPath(int vertex);
	void printShortestDistance(int vertex);
	weightedGraphType(int size = 0);
	~weightedGraphType();

protected:
	double** weights;
	double* smallestWeight;
};
#endif // !GRAPHTYPE_H

bool graphType::isEmpty() const
{
	return (gSize == 0);
}

void graphType::createGraph()
{
	ifstream infile;
	char fileName[50];

	int vertex;
	int adjacentVertex;

	if (gSize != 0)
		clearGraph();

	cout << "Enter input file name: ";
	cin >> fileName;
	cout << endl;

	infile.open(fileName);

	if (!infile)
	{
		cout << "Cannot open input file." << endl;
		return;
	}

	infile >> gSize;

	for (int index = 0; index < gSize; index++) {
		infile >> vertex;
		infile >> adjacentVertex;

		while (adjacentVertex != 999)
		{
			graph[vertex].insertLast(adjacentVertex);
			infile >> adjacentVertex;
		}
	}

	infile.close();
}

void graphType::clearGraph()
{
	for (int index = 0; index < gSize; index++)
		graph[index].destroyList();

	gSize = 0;
}

void graphType::printGraph() const
{
	for (int index = 0; index < gSize; index++)
	{
		cout << index << " ";
		graph[index].print();
		cout << endl;
	}
	cout << endl;
}

graphType::graphType(int size)
{
	maxSize = size;
	gSize = 0;
	graph = new unorderedLinkedList<int>[size];
}

graphType::~graphType()
{
	clearGraph();
}

void graphType::breadthFirstTravesal()
{
	linkedQueueType<int> queue;

	bool* visited;
	visited = new bool[gSize];

	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false;

	linkedListIterator<int> graphIt;

	for (int index = 0; index < gSize; index++)
		if (!visited[index])
		{
			queue.addQueue(index);
			visited[index] = true;
			cout << " " << index << " ";

			while (!queue.isEmptyQueue())
			{
				int u = queue.front();
				queue.deleteQueue();

				for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
				{
					int w = *graphIt;
					if (!visited[w])
					{
						queue.addQueue(w);
						visited[w] = true;
						cout << " " << w << " ";
					}
				}
				delete[] visited;
			}
		}
}

void weightedGraphType::shortestPath(int vertex)
{
	for (int j = 0; j < gSize; j++)
		smallestWeight[j] = weights[vertex][j];

	bool* weightFound;
	weightFound = new bool[gSize];

	for (int j = 0; j < gSize; j++)
		weightFound[j] = false;

	weightFound[vertex] = true;
	smallestWeight[vertex] = 0;

	for (int i = 0; i < gSize - 1; i++)
	{
		double minWeight = DBL_MAX;
		int v;

		for (int j = 0; j < gSize; j++)
			if (!weightFound[j])
				if (smallestWeight[j] < minWeight)
				{
					v = j;
					minWeight = smallestWeight[v];
				}

		weightFound[v] = true;

		for (int j = 0; j < gSize; j++)
			if (!weightFound[j])
				if (minWeight + weights[v][j] < smallestWeight[j])
					smallestWeight[j] = minWeight + weights[v][j];
	}
}//O(n^2)

void weightedGraphType::printShortestDistance(int vertex)
{
	cout << "Source Vertex: " << vertex << endl;
	cout << "Shortest distance from source to each vertex." << endl;
	cout << "Vertex Shortest_Distance" << endl;

	for (int j = 0; j < gSize; j++)
		cout << setw(4) << j << setw(12) << smallestWeight[j] << endl;
	cout << endl;
}

weightedGraphType::weightedGraphType(int size) : graphType(size)
{
	weights = new double* [size];

	for (int i = 0; i < size; i++)
		weights[i] = new double[size];

	smallestWeight = new double[size];
}

weightedGraphType::~weightedGraphType()
{
	for (int i = 0; i < gSize; i++)
		delete[] weights[i];

	delete[] weights;
	delete smallestWeight;
}