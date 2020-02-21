#pragma once
#include <iostream>

enum ResultCode: unsigned int
{
	RCWrongInput,
	RCDuplicated,
	RCSuccess,
	RCNotFound,
};

template<class T>
class Graph
{
public:
	Graph(int size) : n(size) {}
	/*
	* �����
	*/
	virtual ResultCode insert(int u, int v, T& w) = 0;
	/*
	* ɾ����
	*/
	virtual ResultCode remove(int u, int v) = 0;
	/*
	* �Ƿ���ڱ�
	*/
	virtual bool exist(int u, int v) = 0;
	// ���ض�����
	virtual int vertices() { return n; }
protected:
	int n{ 0 };
	int e{ 0 };

};

template<class T>
struct ENode
{
	ENode(int adjVex, const T& w, ENode* nextNode = nullptr) : 
		adjVex(adjVex), w(w), nextNode(nextNode) {}
	~ENode()
	{
		if (nextNode)
		{
			delete nextNode;
			nextNode = nullptr;
		}
	}
	// Ȩֵ
	T w;
	// �ٽ�Ķ���
	int adjVex;
	// ��һ������
	ENode* nextNode{ nullptr };
};

/*
�ڽӱ�ʵ�ֵ�ͼ
*/
template<class T>
class LGraph : public Graph<T>
{
public:
	LGraph(int size) : Graph<T>(size)
	{
		mVertices = new ENode * [size];
		for (int i = 0; i < size; i++)
		{
			mVertices[i] = nullptr;
		}
	}
	~LGraph()
	{
		delete[] mVertices;
	}
public:
	/*
	* �����
	*/
	virtual ResultCode insert(int u, int v, T& w)
	{
		if (!checkInput(u, v)) return ResultCode::RCWrongInput;
		if (exist(u, v)) return ResultCode::RCDuplicated;
		auto node = new ENode<T>(v, w, mVertices[u]);
		mVertices[u] = node;
		Graph<T>::e++;
		return ResultCode::RCSuccess;
	}
	/*
	* ɾ����
	*/
	virtual ResultCode remove(int u, int v)
	{
		if (!checkInput(u, v)) return ResultCode::RCWrongInput;
		auto vertex = mVertices[u];
		auto pre = nullptr;
		
		while (vertex)
		{
			if (vertex->adjVex == v)
			{
				if (pre)
				{
					pre->nextNode = vertex->nextNode;
				}
				else
				{
					mVertices[u] = vertex->nextNode;
				}
				delete vertex;
				return ResultCode::RCSuccess;
			}
			pre = vertex;
			vertex = vertex->nextNode;
		}
		return RCNotFound;
	}
	/*
	* �Ƿ���ڱ�
	*/
	virtual bool exist(int u, int v)
	{
		if (!checkInput(u, v)) return false;
		auto vertex = mVertices[u];
		
		while (vertex->nextNode)
		{
			vertex = vertex->nextNode;
			if (vertex->adjVex == v)
			{
				return true;
			}
		}
		return false;
;
	}
protected:
	inline bool checkInput(int u, int v)
	{
		if (u < 0 || u > n - 1 || v < 0 || v > n - 1 || u == v)
		{
			return false;
		}
		return true;
	}
protected:
	ENode<T>** mVertices;
};


template<class T>
class ExtLGrash : public LGrash<T>
{
public:
	void DFS()
	{
		bool* visited = new bool[n];
		for (int i = 0; i < n; ++i)
		{
			visited[i] = false;
		}
		for (int i = 0; i < n; ++i)
		{
			DFS(i, visited, visitFunc);
		}
		delete[] visited;

	}
	void BFS()
	{
		bool* visited = new bool[n];
		for (int i = 0; i < n; ++i)
		{
			visited[i] = false;
		}
		for (int i = 0; i < n; ++i)
		{
			BFS(i, visited, visitFunc);
		}
		delete[] visited;

	}
	void topoSort(int* order)
	{
		// �������
		int* inWeights = new int[n];
		for (int i = 0; i < n; ++i)
		{
			inWeights[i] = 0;
		}
		for (int i = 0; i < n; ++i)
		{
			for (auto vertex = mVertices[i]; vertex != nullptr; vertex = vertex->nextNode)
			{
				inWeights[vertex->adjVex] += 1;
			}
		}
		// 1. Ѱ�����Ϊ0�Ľڵ㣬���ŵ�order��
		// 2. �������
		int i, j, k, top = -1;
		for (int i = 0; i < n; ++i)
		{
			if (inWeights[i] == 0)
			{
				// push to stack
				inWeights[i] = top;	
				top = i;
			}
		}

		for (int i = 0; i < n; ++i)
		{
			// ��ջ��������Ȩ�أ��������Ϊ0�Ľڵ㣬��push��ջ����
			if (top == -1) return;
			order[i] = top;
			std::cout << top << " ";
			int cur = top;
			top = inWeights[top];
			// ��curָ��Ľڵ㣬��ȼ�һ
			for (auto node = mVertices[cur]; node != nullptr; node = node->nextNode)
			{
				int j = node->adjVex;
				inWeights[j]--;
				if (inWeights[j] == 0)
				{
					// push to stack
					inWeights[j] = top;
					top = j;
				}
			}
		}

	}
private:
	void DFS(int u, bool* visited)
	{
		if (visited[u]) return;
		visit(u, visited);
		auto vertex = mVertices[u];
		while (vertex)
		{
			DFS(vertex->adjVex, visited);
			vertex = vertex->nextNode;
		}
	}
	void BFS(int u, bool* visited)
	{
		if (visited[u]) return;
		visit(u, visited);
		auto vertex = mVertices[u];
		while (vertex)
		{
			visit(vertex->adjVex, visited);
			vertex = vertex->nextNode;
		}
		vertx = mVertices[u];
		while (vertex)
		{
			BFS(vertex->adjVex, visited);
			vertex = vertex->nextNode;
		}
	}
	inline void visit(int u, bool* visited)
	{
		visited[u] = true;
		std::cout << u << " ";
	}
};