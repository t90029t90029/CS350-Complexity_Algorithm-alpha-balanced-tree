//Shang-Chun, Lin CS350
#include "list.h"
using namespace std;

int main()
{
	tree mytree;
	int running = 1;
	char * read = new char[100];
	char * command = new char[10];
	int key = 0;
	float alpha = 0;

	ifstream file_in;
	file_in.open("test.txt");

	if(file_in){
		file_in.get(read,100,'\n');
		file_in.ignore(100,'\n');
		while(!file_in.eof() && running){

			//parse the read
			istringstream strm(read);
			strm>>command;

			if(command && strcmp(command,"BuildTree") == 0){
				strm>>alpha;
				strm>>key;
				mytree.build(alpha,key);
			}
			else if(command && strcmp(command,"Insert") == 0){
				strm>>key;
				mytree.insert(key);
			}	
			else if(command && strcmp(command,"Delete") == 0){
				strm>>key;
				mytree.remove(key);
			}	
			else if(command && strcmp(command,"Search") == 0){
				strm>>key;
				if(mytree.search(key)){
					cout<<"We have found number "<<key<<" in the tree."<<endl;
				}
			}	
			else if(command && strcmp(command,"Print") == 0){
				mytree.display();
				cout<<endl;
			}	
			else if(command && strcmp(command,"Done") == 0){
				mytree.remove_all();
				running = 0;
			}

			if(read){
				delete []read;
				read = NULL;
			}
			if(command){
				delete []command;
				command = NULL;
			}

			if(!file_in.eof() && running){
				read = new char[100];
				command = new char[10];
				file_in.get(read,100,'\n');
				file_in.ignore(10,'\n');
			}
		}
		file_in.close();
		file_in.clear();
	}
	if(read)	
		delete []read;
	read = NULL;

	if(command)	
		delete []command;
	command = NULL;
	return 0;
}
