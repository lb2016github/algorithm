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
	* 插入边
	*/
	virtual ResultCode insert(int u, int v, T& w) = 0;
	/*
	* 删除边
	*/
	virtual ResultCode remove(int u, int v) = 0;
	/*
	* 是否存在边
	*/
	virtual bool exist(int u, int v) = 0;
	// 返回定点数
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
	// 权值
	T w;
	// 临界的顶点
	int adjVex;
	// 下一个顶点
	ENode* nextNode{ nullptr };
};

/*
邻接表实现的图
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
	* 插入边
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
	* 删除边
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
	* 是否存在边
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
		// 计算入度
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
		// 1. 寻找入度为0的节点，并放到order中
		// 2. 更新入度
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
			// 出栈，并更新权重，发现入度为0的节点，则push到栈里面
			if (top == -1) return;
			order[i] = top;
			std::cout << top << " ";
			int cur = top;
			top = inWeights[top];
			// 把cur指向的节点，入度减一
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