#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<vector>
#include<string>

struct Node {
	Node *left, *right, *parent = nullptr;
	int key;
	char color;
	Node(int key, char color, Node *left, Node *right) {
		this->key = key;
		this->color = color;
		this->left = left;
		this->right = right;
	}
};

Node *root = nullptr;

Node *getpar(Node *cur) {
	return cur->parent;
}

Node *getgrpar(Node *cur) {
	if (cur->parent != nullptr) {
		if (cur->parent->parent != nullptr) {
			return cur->parent->parent;
		}
		return nullptr;
	}
	return nullptr;
}

Node *getunc(Node *cur) {
	if (getgrpar(cur) != nullptr) {
		Node *par = getpar(cur);
		if (par == getpar(par)->left) {
			return getgrpar(cur)->right;
		}
		return getgrpar(cur)->left;
	}
	return nullptr;
}

void leftrotare(Node *cur) {
	Node *rightson = cur->right;
	rightson->parent = cur->parent;
	if (getpar(cur) != nullptr) {
		if (getpar(cur)->left == cur) {
			cur->parent->left = rightson;
		}
		else {
			cur->parent->right = rightson;
		}
	}
	cur->right = rightson->left;
	if (rightson->left != nullptr) {
		rightson->left->parent = cur;
	}
	cur->parent = rightson;
	rightson->left = cur;
}

void rightrotare(Node *cur) {
	Node *leftson = cur->left;
	leftson->parent = cur->parent;
	if (getpar(cur) != nullptr) {
		if (getpar(cur)->left == cur) {
			cur->parent->left = leftson;
		}
		else {
			cur->parent->right = leftson;
		}
	}
	cur->left = leftson->right;
	if (leftson->right != nullptr) {
		leftson->right->parent = cur;
	}
	cur->parent = leftson;
	leftson->right = cur;
}

void dfs(Node cur) {
	std::cout << cur.key << " ";
	if (cur.left != nullptr) {
		std::cout << cur.left->key << " ";
	}
	else {
		std::cout << "null ";
	}
	if (cur.right != nullptr) {
		std::cout << cur.right->key << " ";
	}
	else {
		std::cout << "null ";
	}
	std::cout << cur.color << "\n";
	if (cur.left != nullptr) {
		Node tmp = *cur.left;
		dfs(tmp);
	}
	if (cur.right != nullptr) {
		Node tmp = *cur.right;
		dfs(tmp);
	}
}

void fix(Node *tmp) {
	if (getpar(tmp) == nullptr) {
		tmp->color = 'B';
	}
	else if (getpar(tmp)->color == 'B') {
	}
	else if (getunc(tmp) != nullptr && getunc(tmp)->color == 'R') {
		getpar(tmp)->color = 'B';
		getunc(tmp)->color = 'B';
		getgrpar(tmp)->color = 'R';
		fix(getgrpar(tmp));
	}
	else {
		Node *par = getpar(tmp);
		Node *grpar = getgrpar(tmp);
		if (tmp == par->right && par == grpar->left) {
			leftrotare(par);
			tmp = tmp->left;
		}
		else if (tmp == par->left && par == grpar->right) {
			rightrotare(par);
			tmp = tmp->right;
		}
		par = getpar(tmp);
		grpar = getgrpar(tmp);

		if (tmp == par->left) {
			rightrotare(grpar);
		}
		else {
			leftrotare(grpar);
		}
		par->color = 'B';
		grpar->color = 'R';
	}
}

void downslide(Node *root, Node *tmp) {
	/*
	if (root != nullptr) {
	if (tmp->key < root->key) {
	if (root->left != nullptr) {
	downslide(root->left, tmp);
	return;
	}
	else {
	root->left = tmp;
	}
	}
	else {
	if (root->right != nullptr) {
	downslide(root->right, tmp);
	return;
	}
	else {
	root->right = tmp;
	}
	}
	}
	*/
	//Node *temp_val = new Node(tmp->key, 'R', nullptr, nullptr);
	if (root == nullptr) {
		root = tmp;
		tmp->parent = nullptr;
	}
	else {
		Node *pa = root;
		Node *cur = nullptr;
		while (pa != nullptr) {
			cur = pa;
			if (pa->key < tmp->key) {
				pa = pa->right;
			}
			else {
				pa = pa->left;
			}
		}
		tmp->parent = cur;
		if (cur->key < tmp->key) {
			cur->right = tmp;
		}
		else {
			cur->left = tmp;
		}
	}



	//tmp->parent = root;
	//tmp = temp_val;
}

void insert(Node *tmp) {
	downslide(root, tmp);
	fix(tmp);
	root = tmp;
	while (getpar(root) != nullptr) {
		root = getpar(root);
	}
}
int find(int key) {
	Node *tmp = root;
	while (tmp != nullptr) {
		if (key == tmp->key) {
			return 1;
		}
		else if (key < tmp->key) {
			tmp = tmp->left;
		}
		else {
			tmp = tmp->right;
		}
	}
	return 0;
}

int num;
int counter = 0;

signed main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cin >> num;
	if (num == 0) {
		std::cout << "0";
	}
	else {
		for (int ii = 0; ii < num; ii++) {
			int first, second;
			std::cin >> first >> second;
			if (first == 0) {
				if (find(second) == 0) {
					counter++;
					Node *tmp = new Node(second, 'R', nullptr, nullptr);
					insert( tmp);
				}
			}
			if (first == 1) {
				if (find(second) == 1) {
					std::cout << "Yes" << "\n";
				}
				else {
					std::cout << "No" << "\n";
				}
			}
		}
		std::cout << counter << "\n";
		if (counter != 0) {
			dfs(*root);
		}
	}
	//system("pause");
	return 0;
}
