//Shang-Chun, Lin CS350
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <sstream>	//for parse read in main
#include <math.h>	// log

//This file has been implemented by an alpha balanced tree.

class t_node
{
	public:
		t_node();
		t_node(const int);
		~t_node();

		t_node *& go_left();
		t_node * get_left()const;
		t_node *& go_right();
		t_node * get_right()const;
		t_node *& go_parent();
		t_node * get_parent()const;
		int isRoot();
		void connect_left(t_node * connection);
		void connect_right(t_node * connection);
		void connect_parent(t_node * connection);
		void changeNum(int);
		int getNum()const;
		
		void remove_all();
		bool is_leaf()const;
		bool compare(const int);

	protected:
		int * num;
		t_node * left;
		t_node * right;
		t_node * parent;
};

class tree
{
	public:
		tree();
		~tree();
		
		void remove_all();		//for Done
		int search(const int key);	//for Search
		void display()const;		//for Print
		void insert(const int key);	//for Insert
		void build(const float alpha,const int key);	//for BuildTree
		void remove(const int key);	//for Delete

	protected:
		t_node * root;
		float alpha;
		int Size;
		int Maxsize;

		void remove_all(t_node * &);
		int size(t_node *)const;
		int search(t_node *,const int);
		int get_height(t_node *)const;	//serve for should_rebuild()
		bool should_rebuild(t_node *,int)const;
		void insert(t_node * &,const int,int &,t_node * &);
		void remove(t_node * &,const int);
		void swap_ios(t_node *&,t_node *&);
		
		//for insert()
		//order of calling : find->rebuild->store->build
		//algorithm followed on the geeksforgeeks
		void find_scapeGoat(t_node *,t_node *&)const;
		void store_tree(t_node *,t_node **,int &);
		void rebuild(t_node * &);
		t_node * buildFromArray(t_node **,int,int);

		//provided by the teacher
		void tree_walk(const t_node *,int)const;
		void display(const t_node *)const;
};
















