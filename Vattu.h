#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <string>
using namespace std;
//=====struct=====//
struct Vattu{
	char mavt[10];
	char tenvt[100];
	char donvitinh[10];
	int soluong;
};
struct NodeVattu{
	Vattu vattu;
	*Nodevattu left;
	*Nodevattu right;
};
//=====Danh sach ham=====//
Vattu createVattu(char mavt[], char tenvt[], char donvitinh[], int soluong);

void free(NodeVattu *root);

int leftof(Vattu &vattu, const NodeVattu* node);
int rightof(Vattu &vattu, const NodeVattu* node);

NodeVattu* insert(NodeVattu* root, Vattu &vattu);
bool search(const NodeVattu *root, Vattu &vattu);
Vattu min(const NodeVattu* root);
NodeVattu* remove(NodeVattu* root, Vattu &vattu);
//=====Ham=====//
Vattu createVattu(char mavt[], char tenvt[], char donvitinh[], int soluong){
	Vattu vattu;
	vattu.mavt = mavt;
	vattu.tenvt = tenvt;
	vattu.donvitinh = donvitinh;
	vattu.soluong = soluong
	return vattu;
};
void free(NodeVattu *root){
	if (root==null) return;
	free (root->left);
	free (root->right);
	free (root);
};
int leftof(Vattu &vattu, const NodeVattu* node){
	return strcmp(vattu.mavt, node->vattu.mavt)<=0;
};
int rightof(Vattu &vattu, const NodeVattu* node){
	return strcmp(vattu.mavt, node->vattu.mavt)>0;
};
NodeVattu* insert(NodeVattu* root, Vattu &vattu){
	if (root==null){
		NodeVattu* node = new NodeVattu;
		node->left=null;
		node->right=null;
		node->vattu=vattu;
		return node;
	}
	if (leftof(vattu, root)) root->left=insert(root->left, vattu);
	if (rightof(vattu, root)) root->right=insert(root->right, vattu);
	return root;
};
bool search(const NodeVattu* root, Vattu &vattu){
	if (root==null) return false;
	if (root->vattu==vattu) return true;
	else if (leftof(vattu, root)) return search(root->left, vattu);
	else if (rightof(vattu, root)) return search(root->right, vattu);
};
Vattu min(const NodeVattu *root){
	while (root->left != null) root=root->left;
	return root->vattu;
};
NodeVattu* remove(NodeVattu* root, Vattu &vattu){
	if(root==null) return root;
	if(leftof(vattu, root)) root->left=remove(root->left, vattu);
	else if(rightof(vattu, root)) root->right=remove(root->right, vattu);
	else{
		if(root->left==null){
			NodeVattu temp = root->right;
			free(root);
			return temp;
		}
		if(root->right==null){
			NodeVattu temp = root->left;
			free(root);
			return temp;
		}
	}
	root->vattu = min(root->right);
	root->right = remove(root->right, root->vattu);
};

