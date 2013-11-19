#include <iostream>

using namespace std;

struct Node
{
	int col;
	int v;
	Node* right;
};

struct Head
{
	int row;
	Node* node;
	Head* down;
};

void insert(Head* head, int row, int col, int v)
{

	if (head == NULL)
	{
		head = new Head;
		head->row = row;
		head->down = NULL;
		head->node = NULL;
	}
	else
	{
		while (head)
		{
			if (head->row == row) break;
			else if (head->row > row
					|| head->down == NULL)
			{
				Head* p = new Head;
				p->row = row;
				p->down = head->down;
				head->down = p;
				head = p;
				break;
			}
			
			head = head->down;
		}
	}
	
	if (head->node == NULL)
	{
		head->node = new Node;
		head->node->col = col;
		head->node->v = v;
		head->node->right = NULL;
	}
	else
	{
		while (head->node)
		{
			if (head->node->col == col)
			{
				head->node->v = v;
				break;
			}
			else if (head->node->col > col 
					|| head->node->right == NULL)
			{
				Node* node = new Node;
				node->col = col;
				node->v = v;
				node->right = head->node->right;
				head->node->right = node;
				break;
			}
			
			head->node = head->node->right;
		}
	}
}

void print(Head* head)
{
	while (head)
	{
		while (head->node)
		{
			cout << '[' << head->row << ", " << head->node->col << ", "
				<< head->node->v << "] ";
			head->node = head->node->right;
		}
		cout << endl;
		head=head->down;
	}
}

void init(Head* head)
{
	insert(head, 1, 3, 13);
	insert(head, 2, 3, 23);
	insert(head, 1, 4, 14);
	insert(head, 3, 3, 33);
}

int main()
{
	Head head;
	head.node = NULL;
	head.down = NULL;
	init(&head);
	print(&head);
	return 0;
}



