#include "own_library.h"
#include <queue>

struct nodeType
{
	char symbol;
	double value;

	nodeType * left = nullptr;
	nodeType * right = nullptr;
};

struct compareNode
{
	bool operator()(const nodeType * firstNode, const nodeType * secondNode)
	{
		if (firstNode->value > secondNode->value)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
};

typedef priority_queue<nodeType *, vector<nodeType *>, compareNode> priorityQueueType;

void huffman(priorityQueueType &);
void obtainCode(nodeType *, string, ofstream &);

int main()
{
	string data_input, data_output;
	valid_filename_two_possibilities("data_input_frequencies", "data_input_probabilities", ".txt", data_input);
	valid_filename("data_output", ".txt", data_output);

	ifstream fin;
	openFile(data_input, fin);

	ofstream fout;
	openFile(data_output, fout);

	priorityQueueType priorityQueue;

	while (fin)
	{
		if (!fin.eof())
		{
			nodeType * node = new nodeType;

			fin >> node->symbol;
			fin >> node->value;

			priorityQueue.push(node);
		}

		else
		{
			break;
		}
	}

	huffman(priorityQueue);

	nodeType * topNode = priorityQueue.top();
	obtainCode(topNode, string(), fout);
	fout << endl;

	fin.close();
	fout.close();

	return 0;
}

/**
* Creating a tree corresponding to an optimal code for each symbol using a Huffman algorithm
*
* @param	priorityQueue	priority queue storing nodes which contain symbols
* @param	value			frequency or probability of the symbol occuring in the file
* @param	left			pointer to the left child of the node
* @param	right			pointer to the right child of the node
* @param	symbol			symbol of the current node
*/
void huffman(priorityQueueType & priorityQueue)
{
	while (priorityQueue.size() > 1)
	{
		nodeType * auxiliaryNode = new nodeType;

		nodeType * firstNode = priorityQueue.top();
		priorityQueue.pop();

		nodeType * secondNode = priorityQueue.top();
		priorityQueue.pop();

		auxiliaryNode->left = firstNode;
		auxiliaryNode->right = secondNode;
		auxiliaryNode->value = firstNode->value + secondNode->value;

		priorityQueue.push(auxiliaryNode);
	}

	return;
}

/**
*  Obtaining optimal code for each symbol in a tree created using Huffman algorithm
*
* @param	node	current node
* @param	code	string object which is the final code for given symbol
* @param	left	pointer to the left child of the node
* @param	right	pointer to the right child of the node
* @param	symbol	symbol of the current node
* @param	fout	object of ofstream class which writes a data to the file
*/
void obtainCode(nodeType * node, string code, ofstream & fout)
{
	if (node->left != nullptr)
	{
		obtainCode(node->left, code + "0", fout);
	}

	else
	{
		fout << node->symbol << ": " << code << endl;
	}

	if (node->right != nullptr)
	{
		obtainCode(node->right, code + "1", fout);
	}
}