#include<iostream>
using namespace std;
class node
{
     public:
     	int data;
     	node *left;
     	node *right;
};
class bst
{

public:
		node *root;
	bst()
	{
		root=NULL;
	}
	void create();
	void insert();
	void postorder(node*);
	void inorder(node *);
        void preorder(node *);
        void search(int key);
        void mirror(node *& root);

       // int search(node*, int key);
	void minimum();
	int height(node*);
	void display(node*,int space=0);
};


void bst::minimum()
{
    if (root == NULL) {
        cout << "Tree is empty." << endl;
        return;
    }

    node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }

    cout << "Minimum number is: " << temp->data << endl;
}

int bst::height(node *root)
{
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		if(height(root->right)>height(root->left))		//right tree is longer
		{
			return (1+height(root->right));
		}
		else
		{
			return (1+height(root->left));
		}
	}
}

void bst::create()
{
	node *curr,*temp;
	int ans=1;
	cout<<"enter data:";
	do
	{
		curr=new node;
		cin>>curr->data;
		curr->left=curr->right=NULL;
		if(root==NULL)
		{
			root=curr;
		}
		else
		{
			temp=root;
			while(1)
			{
				if(curr->data<=temp->data)
				{
					if(temp->left==NULL)
					{
						temp->left=curr;
						break;
					}
					else
					{
						temp=temp->left;
					}
				}
				else
				{
					if(temp->right==NULL)
					{
						temp->right=curr;
						break;
					}
					else
					{
						temp=temp->right;
					}
				}
			}
		}
		cout<<"want to continue ?(1 for yes,0 for no):";
		cin>>ans;
	}while(ans==1);
}
void bst::inorder(node *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout<<" "<<root->data;
		inorder(root->right);
	}
}
void bst::preorder(node *root)
{
	if(root!=NULL)
	{
		cout<<"  "<<root->data;
		preorder(root->left);
		preorder(root->right);
	}
}
void bst::postorder(node *root)
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<" "<<root->data;
	}
}
void bst::insert()
{
	node *curr,*temp;
	int ans=1;
	cout<<"enter data:";


		curr=new node;
		cin>>curr->data;
		curr->left=curr->right=NULL;
		if(root==NULL)
		{
			root=curr;
		}
		else
		{
			temp=root;
			while(1)
			{
				if(curr->data<=temp->data)
				{
					if(temp->left==NULL)
					{
						temp->left=curr;
						break;
					}
					else
					{
						temp=temp->left;
					}
				}
				else
				{
					if(temp->right==NULL)
					{
						temp->right=curr;
						break;
					}
					else
					{
						temp=temp->right;
					}
				}
			}//end of while
		}
}


void bst::search(int key)
{
	node *curr;
	curr=root;
	while(curr!=NULL)
	{
		if(curr->data==key)
		{
			cout<<"found";
			break;
		}
		else
		{
			if(key<curr->data)
			{
				curr=curr->left;
			}
			else
			{
				curr=curr->right;
			}
		}
	}
	if(curr==NULL)			//not found even at the end of the tree.
	{
		cout<<"not found";
	}
}

void bst::mirror(node*& root) 
{
    if (root == nullptr) {
        return;
    }
    
    // Swap the left and right child nodes
    node* temp = root->left;
    root->left = root->right;
    root->right = temp;

}

void bst::display(node*root,int space)
{
	if(root==NULL)
	return ;


	//increase distance between levels
	space+=10;

	//first display right subtree
	display(root->right,space);

	//print the current node after space count
	cout<<endl;
	for(int i=10;i<space;i++)
	cout<<" ";
	cout<<root->data<<"\n";
	display(root->left,space);
}



int main()
{
	bst b;
	int key,ch;
	do
	{
		cout<<"\n1.create\n2.insert\n3.inorder\n4.preorder\n5.postorder\n6.search\n7.minimum\n8.height\n9.mirror\n10.display\npress 0 to exit\n";
		cout<<"enter your choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:b.create();
				break;
			case 2:b.insert();
				break;
			case 3:cout<<"inorder traversal is\n";
					b.inorder(b.root);
					break;
			case 4:cout<<"preorder traversal is\n";
					b.preorder(b.root);
					break;
			case 5:cout<<"postorder traversal is\n";
					b.postorder(b.root);
					break;
			case 6:cout<<"\nenter key:";
				cin>>key;
				b.search(key);
				break;
			case 7:b.minimum();
				break;
			case 8:cout<<"height of tree: "<<b.height(b.root);
				break;
			case 9:cout<<"Tree mirrored.\n";
            b.mirror(b.root);

				break;
			case 10:cout<<"Tree Display:\n";
			b.display(b.root);
			break;
		}
	}while(ch!=0);
	return 0;
}