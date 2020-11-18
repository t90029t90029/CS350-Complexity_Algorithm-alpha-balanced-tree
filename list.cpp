//Shang-Chun, Lin CS350
#include "list.h"

using namespace std;
//The purpose of this file is to implement each function in the list.h file
t_node::t_node(){
	num = NULL;
	left = NULL;
	right = NULL;
	parent = NULL;
}

t_node::t_node(const int source){
	num = new int;
	*num = source;
	left = NULL;
	right = NULL;
	parent = NULL;
}

void t_node::remove_all(){
	if(num)
	{
		delete num;
		num = NULL;
	}
	if(left)
	{
		left = NULL;
	}
	if(right)
	{
		right = NULL;
	}
	if(parent)
	{
		parent = NULL;
	}
}

t_node::~t_node(){
	remove_all();
}

t_node *& t_node::go_left(){
	return left;
}
t_node * t_node::get_left()const{
	return left;
}

t_node *& t_node::go_right(){
	return right;
}
t_node * t_node::get_right()const{
	return right;
}

t_node *& t_node::go_parent(){
	return parent;
}
t_node * t_node::get_parent()const{
	return parent;
}

int t_node::isRoot(){
	if(!this->parent)
		return 1;
	return 0;
}

void t_node::connect_left(t_node * connection){
	if(!connection)
	{
		return;
	}
	left = connection;
	return;
}

void t_node::connect_right(t_node * connection){
	if(!connection)
	{
		return;
	}
	right = connection;
	return;
}

void t_node::connect_parent(t_node * connection){
	if(!connection)
	{
		return;
	}
	parent = connection;
	return;
}

void t_node::changeNum(int source){
	if(!num)
		num = new int;
	*num = source;
	return;
}

int t_node::getNum()const{
	return *num;
}

bool t_node::compare(const int source){
	if(num){
		if(*num == source){
			return true;
		}
	}
	return false;
}

bool t_node::is_leaf()const{
	if(!left && !right)
	{
		return true;
	}
	return false;
}

tree::tree(){
	root = NULL;
	alpha = 0;
	Size = 0;
	Maxsize = 0;
}

void tree::remove_all(t_node * & root){
	if(!root)
	{
		return;
	}
	remove_all(root->go_left());
	remove_all(root->go_right());

	root->remove_all();
	delete root;
	root = NULL;
	return;
}

void tree::remove_all(){
	if(!root){
		return;
	}
	return remove_all(root);
}

tree::~tree()
{
	remove_all();
}

int tree::size(t_node * root)const{
	if(!root)
		return 0;
	int count = 1;
	count += size(root->get_left());
	count += size(root->get_right());
	return count;
}

int tree::search(t_node * root,const int source){
	if(!root)
		return 0;
	int count = 0;

	if(root->compare(source))
		return 1;

	count = search(root->get_left(),source);
	count += search(root->get_right(),source);
	return count;
}

int tree::search(const int source){
	if(!root)
		return 0;
	return search(root,source);
}

int tree::get_height(t_node * root)const{
	if(!root)
		return 0;
	int left_height = 0;	
	int right_height = 0;	

	left_height += get_height(root->get_left())+1;
	right_height += get_height(root->get_right())+1;

	return max(left_height,right_height);
}

bool tree::should_rebuild(t_node * root,int depth)const{
	int nodes = size(root);
	float base = 1/alpha;
	int alpha_weight = (float)log(nodes)/(float)log(base);

	if(depth <= alpha_weight){
		return false;	//alpha-height-balanced
	}
	return true;		//should be rebuilt
}

void tree::find_scapeGoat(t_node * source,t_node *& target)const{
	while(size(source->get_left()) <= alpha*size(source) && size(source->get_right()) <= alpha*size(source)){
		source = source->get_parent();
	}
	target = source;
	return;
}

t_node * tree::buildFromArray(t_node ** array,int p,int n){
	if(!n)
		return NULL;
	int mid = n/2;	//start at the midian of the array

	//array[mid] = the root of the new subtree a[0]...a[mid-1]
	//array[0]...array[mid-1] gets stored in left subtree
	array[p+mid]->go_left() = buildFromArray(array,p,mid);
	
	//connect the parent
	if(array[p+mid]->go_left())
		array[p+mid]->go_left()->connect_parent(array[p+mid]);

	//array[mid+1]...array[n-1] gets stored in right subtree
	array[p+mid]->go_right() = buildFromArray(array,p+mid+1,n-mid-1);

	//connect the parent
	if(array[p+mid]->go_right())
		array[p+mid]->go_right()->connect_parent(array[p+mid]);

	return array[p+mid];
}

void tree::store_tree(t_node * root,t_node ** array,int & counter){
	if(!root)
		return;

	store_tree(root->get_left(),array,counter);
	array[counter] = root;
	++counter;
	store_tree(root->get_right(),array,counter);
	return;
}

//root = scapeGoat.parent = root of the subtree
void tree::rebuild(t_node * & root){
	int n = size(root);	//array[0,...,n-1]
	t_node ** array = new t_node*[n];
	int counter = 0;
	store_tree(root,array,counter);

	t_node * parent = root->go_parent();
	if(!parent){
		root = buildFromArray(array,0,n);
		root->connect_parent(NULL);
		this->root = root;
	}
	else if(parent->go_right() == root){
		parent->connect_right(buildFromArray(array,0,n));
		parent->go_right()->connect_parent(parent);
	}
	else{
		parent->connect_left(buildFromArray(array,0,n));
		parent->go_left()->connect_parent(parent);
	}

	for(int i=0;i<n;++i){
		array[i] = NULL;
	}
	delete []array;
	array = NULL;

	Maxsize = Size = size(this->root);
	return;
}

void tree::tree_walk(const t_node * root,int level)const{
	if(root){
		tree_walk(root->get_left(),++level);
		cout<<endl;
		for(int i=0;i<=level;++i){
			cout<<"   ";
		}
		cout<<root->getNum();
		tree_walk(root->get_right(),++level);
	}
	return;
}
void tree::display()const{		//for Print
	if(!root)
		return;
	return tree_walk(root,0);
}

void tree::insert(t_node * & root,const int key,int & depth,t_node * & target){
	if(!root){
		root = new t_node(key);
		root->connect_parent(target);
		target = root;
		++Size;
		return;
	}

	if(key < root->getNum()){
		++depth;
		target = root;
		insert(root->go_left(),key,depth,target);
	}
	else{
		++depth;
		target = root;
		insert(root->go_right(),key,depth,target);
	}

	return;
}
void tree::insert(const int key){	//for Insert
	if(!root){
		root = new t_node(key);
		Size = 1;
		Maxsize = max(Maxsize,Size);
		return;
	}
	int depth = 0;
	//target = inserted node
	t_node * target;
	insert(root,key,depth,target);

	//If the tree is unbalanced
	if(should_rebuild(this->root,depth)){
		//target is going to be the rebuild node
		find_scapeGoat(target,target);
		rebuild(target);
		Maxsize = max(Maxsize,Size);
	}

	return;
}

void tree::build(const float alpha_source,const int key){	//for BuildTree
	alpha = alpha_source;
	insert(key);
	return;
}

void tree::swap_ios(t_node *& root,t_node *& ios){
	t_node * hold;
	if(!ios->go_left()){
		//swap value
		root->changeNum(ios->getNum());

		//connect
		if(ios->go_right()){
			hold = ios->go_right();
			hold->connect_parent(ios->go_parent());

			ios->remove_all();
			delete ios;
			ios = hold;
			return;
		}

		//ios at leaf
		ios->remove_all();
		delete ios;
		ios = NULL;
		return;
	}
	return swap_ios(root,ios->go_left());
}

void tree::remove(t_node * & root,const int key){
	if(!root)
		return;
	t_node * target;
	t_node * hold;
	if(root->compare(key)){
		--Size;
		if(root->is_leaf()){
			root->remove_all();
			delete root;
			root = NULL;
		}
		else if(root->get_left() && !root->get_right()){
			hold = root->go_left();
			hold->connect_parent(root->go_parent());
			root->remove_all();
			delete root;
			root = hold;
		}
		else if(root->get_right() && !root->get_left()){
			hold = root->go_right();
			hold->connect_parent(root->go_parent());
			root->remove_all();
			delete root;
			root = hold;
		}
		else{
			swap_ios(root,root->go_right());
		}

		//after recursion : If the tree is unbalanced
		if(Size<= alpha*Maxsize){
			find_scapeGoat(root,target);
			rebuild(target);
			Maxsize = Size;
		}
		return;
	}

	else if(key < root->getNum()){
		return remove(root->go_left(),key);
	}
	else
		return remove(root->go_right(),key);
}
void tree::remove(const int key){	//for Delete
	if(!root)
		return;
	remove(root,key);
	return;
}
