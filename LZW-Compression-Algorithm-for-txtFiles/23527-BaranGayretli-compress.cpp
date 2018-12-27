#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>


using namespace std;

// Baran Gayretli - Fall 2018 - HW2

template<class type> // this BST class is taken from the codes discussed in the class and cplusplus.com
class BST
{
private:
	struct node
	{
		node* left;
		node* right;
		type data;
		int code;
	};
	node* root;

public:
	BST();
	~BST();
	bool isEmpty() const 
	{
		return root==NULL;
	}
	void insert(type,int);
	int GetNumber(type);
	bool find(type);
	void mEmpty();
	void makeEmpty(node*);
};

template<class type>
BST<type>::BST()//initialization
{
	root=NULL;
}

template<class type>
BST<type>::~BST()//destructor
{
	mEmpty();
}

template <class type>
void BST<type>::mEmpty()
{
	makeEmpty(root);
}

template<class type>
void BST<type>::makeEmpty(node *root){
	node* temp=root;
	if (temp != NULL) {
		makeEmpty(temp->left);
		makeEmpty(temp->right);
		delete temp;

	}
	root = NULL;
}

template <class type>
void BST<type>::insert(type d,int c){

	node* t = new node;

	node* parent;
	t->data = d;
	t->code=c;
	t->left = NULL;
	t->right = NULL;
	parent = NULL;
	// check if it is a new tree
	if(isEmpty()) root = t;
	else{

		if(!find(d)){//if it exists, dont add it

			// insertion to leaf node
			node* curr;
			curr = root;
			// get the parent
			while(curr){
				parent = curr;
				if(t->data > curr->data) curr = curr->right;
				else curr = curr->left;
			}

			if(t->data < parent->data)
				parent->left = t;
			else
				parent->right = t;
		}
	}
}

template <class type>
int BST<type>::GetNumber(type d){//it will search the string of interest and return the number of the string

	node* curr;
	node* parent;
	curr = root;

	parent = (node*)NULL;
	while(curr != NULL){
		if(curr->data == d){
			return curr->code;
			break;
		}
		else{
			parent = curr;
			if(d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
}

template <class type>
bool BST<type>::find(type d){
	//Locate the element
	bool found = false;
	if(isEmpty())
		return false;

	node* curr;
	node* parent;
	curr = root;
	parent = (node*)NULL;
	while(curr != NULL){
		if(curr->data == d){
			found = true;
			break;
		}
		else{
			parent = curr;
			if(d>curr->data) curr = curr->right;
			else curr = curr->left;
		}
	}
	if(!found)
		return false;
	else
		return true;
}






int main()
{	
	ifstream compin;
	ofstream compout;
	BST<string>bst;


	compin.open("compin.txt");
	compout.open("compout.txt");

	int count = 256;

	string wholestring="";
	char ch;
	while(compin.get(ch))//creating the wholestring to iterate it  
	{
		wholestring+=ch;
	}

	for (int i = 0; i < 256; i++)
		bst.insert(string(1, i), i);

	string w;
	for (string::const_iterator iter = wholestring.begin(); iter != wholestring.end(); iter++) // iterating the whole string
	{
		char c = *iter;//c is the current character
		string wc = w + c;
		if (bst.find(wc))// if it is in the	BST
			w = wc;
		else 
		{
			compout << bst.GetNumber(w) << " ";//encode it to the compout file
			bst.insert(wc,count++);//add it to the BST, which is the dictionary
			w = string(1, c);
		}
	}
	if (!w.empty())
		compout << bst.GetNumber(w);//get the remaining code if it exists

	compout.close();

	bst.~BST();//destructor called

	return 0;
}