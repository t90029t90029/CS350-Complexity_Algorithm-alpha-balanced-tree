##Name : Shang-Chun, Lin

* description :
The codes are made for building program that generates alpha-balanced-tree, which reads data from the external file "test.txt". It's like a BST but will rebuild when the tree is alpha-unbalanced.

* How I did it :
I have built several functions for the program.
First off, I have built a tree class and a node class for the program. The node class constructs how a node looks like and the tree class hold the whole tree for us.

Secondly, There are several public functions in the tree class so that we are able to call them in main.cpp. They are corresponding to BuildTree, Insert, Search, Delete, Print, and Done. the user is allowed to modify the test.txt file to control the program.

Thirdly, whenever the tree is unbalanced after insertion or deletion, the program will rebuild the tree.

The last one is I have included sstream and used istringstream to parse the string after I have read the whole line until \n. This is because unlike Java we can not use several delimiters in a single getline command in c++.

* the list of files should be in the archive :
main.cpp file : an interface between external file and the program.
list.h   file : to declare the classes and everything we need in list.cpp file.
list.cpp file : the implementation of the classes/functions for the program.
test.txt file : a user control interface to call the functions.
Makefile      : a tool for make/clean/zip files.
README.md file: the introduction of the program.
