#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TagNode
{
	TagNode(string name) : msg(name)
	{
		endTag = "</" + msg.substr(1, msg.size() - 1);
	};
	void addChild(TagNode* node) { children.push_back(node); }
	bool isTag()
	{
		return msg[0] == '<' && msg[msg.size() - 1] == '>';
	}
	bool isEndTag(const string& str)
	{
		return str == endTag;
	}
	void printTree(int level = 0)
	{
		for (int i = 0; i < level; ++i)
		{
			cout << "----";
		}
		cout << msg << endl;
		for (auto child : children)
		{
			child->printTree(level + 1);
		}
		if (isTag())
		{
			for (int i = 0; i < level; ++i)
			{
				cout << "----";
			}
			cout << endTag << endl;
		}
	}
	string msg, endTag;
	vector<TagNode*> children;
};

class LexParser
{
private:
	string data;
	vector<int> lexIndexList;
public:
	void doLex(const string& data)
	{
		this->data = data;
		startLex(0, 0);
	}
	TagNode* buildTagTree()
	{
		auto iter = lexIndexList.begin();
		TagNode* root = doBuildTagTree(iter);
		return root;
	}
	void printLex()
	{
		cout << "Lex Result: " << endl;
		for (auto iter = lexIndexList.begin(); iter != lexIndexList.end(); ++iter)
		{
			cout << data.substr(*iter, *(iter + 1) - *iter + 1) << " ";
			++iter;
		}
		cout << endl;
	}
private:
	TagNode* doBuildTagTree(vector<int>::iterator& iter)
	{
		string msg = getNextLex(iter);
		if (msg == "") return nullptr;
		TagNode* node = new TagNode(msg);

		// 不是tag
		if (!node->isTag()) return node;
		while (true)
		{
			auto pre = iter;
			string next = getNextLex(iter);
			if (next == "") return node;
			if (node->isEndTag(next)) return node;
			// 子节点
			iter = pre;
			TagNode* child = doBuildTagTree(iter);
			node->addChild(child);
		}
	}
	string getNextLex(vector<int>::iterator& iter)
	{
		if (iter == lexIndexList.end()) return "";
		int start = *iter;
		++iter;
		int endInclude = *iter;
		++iter;
		auto lex = data.substr(start, endInclude - start + 1);
		return lex;
	}
private:
	void startLex(int start, int index)
	{
		if (!isIndexValid(index)) return;
		char c = data[index];
		if (c == '<') stateTag(start, index + 1);
		else stateNotTag(start, index + 1);
	}
	void stateTag(int start, int index)
	{
		if (!isIndexValid(index)) return;
		char c = data[index];
		if (c == '>')
		{
			stateEnd(start, index);
		}
		else
		{
			stateTag(start, index + 1);
		}
	}
	void stateEnd(int start, int index)
	{
		if (index < start) return;
		lexIndexList.push_back(start);
		lexIndexList.push_back(index);
		startLex(index + 1, index + 1);
	}

	void stateNotTag(int start, int index)
	{
		if (!isIndexValid(index))
		{
			stateEnd(start, index - 1);
			return;
		}
		char c = data[index];
		if (c == '<') stateEnd(start, index - 1);
		else stateNotTag(start, index + 1);
	}
	int isIndexValid(int index)
	{
		return index < data.size();
	}

};

void testHtmlTagParser()
{
	string tests[] = {
		"sdgsdg",
		"<b>sdgsdg<a>343</a></b>",
		"<body> <h3>HTML标签演示</h3> <iframe src=1.1-ShowHtml.htm ></iframe> </body>",
		"<a></a>"
	};
	for (auto str : tests)
	{
		cout << "Start Test: " << str << endl;
		LexParser parser;
		parser.doLex(str);
		parser.printLex();
		TagNode* tree = parser.buildTagTree();
		cout << "TagTree:" << endl;
		tree->printTree();
		delete tree;
		cout << "===============================" << endl << endl;
	}
}