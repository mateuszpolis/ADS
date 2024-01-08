#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Node
{
	public:
		Node *left;
		Node *right;
		int val;
		int right_children;
};


class Tree
{
	public:
		Node *root;
		int inversion_count;

		void insert(int value) {
			Node *newNode = new Node();
			newNode->val = value;
			newNode->right_children = 0;
			newNode->left = NULL;
			newNode->right = NULL;
			if (root == NULL)
			{
				root = newNode;
				return;
			}
			else
			{
				Node *prev = NULL;
				Node *current = root;
				while( current != NULL)
				{
					if (value <= current->val)
					{
						inversion_count += current->right_children + 1;
						prev = current;
						current = current->left;
						if (current == NULL)
						{
							prev->left = newNode;
							break;
						}
						
					}
					else
					{
						current->right_children++;
						prev = current;
						current = current->right;
						if (current == NULL)
						{
							prev->right = newNode;
							break;
						}
					}
				}
				return;
			}
		}
};


int compute(vector<int>& perm, int n)
{
	Tree tree = Tree();

	for(int i = 0; i < n; i++)
		tree.insert(perm[i]);

	return tree.inversion_count;
}


int main()
{
	vector<int> perm; 
	
	int z,n,m;
	cin >> z;
	while(z)
	{
		perm.clear();		
		cin >> n;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			perm.push_back(x);
		}
		int sol = compute(perm, n);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}
