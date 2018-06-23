# include < iostream >
# include  < fstream >
# include  < string >

using namespace std;

struct Node
{
	char data;
	Node* next;
	Node* prev;

};


class TextStructure
{
private:


	int size;

	Node* head;
	Node* tail;

	Node* createnode(const char & data)
	{
		Node* temp = new Node;

		temp->data = data;
		temp->next = NULL;
		temp->prev = NULL;
		return temp;

	}

public:

	friend ostream & operator<<(ostream &  out, TextStructure & text)
	{
		text.printlist();

		return out;

	}

	TextStructure(const TextStructure & text)
	{
		//Node * newnode;
		Node * curr;

		size = 0;

		if (text.size == 0)
		{
			head = tail = NULL;
			size = 0;

		}
		else
		{
			curr = text.head;


			while (curr != NULL)
			{
				addatend(curr->data);

				curr = curr->next;
			}


		}

	}

	const TextStructure & operator=(const TextStructure & text)
	{
		Node * curr;

		if (size != 0)
		{
			distroylist();

		}

		if (text.size == 0)
		{
			head = tail = NULL;
			size = 0;

		}
		else
		{
			curr = text.head;


			while (curr != NULL)
			{
				addatend(curr->data);

				curr = curr->next;
			}


		}

		return *this;
	}

	TextStructure()
	{
		head = tail = NULL;
		size = 0;

	}
	void addatend(const char & obj)
	{
		if (size == 0)
		{
			head = createnode(obj);
			tail = head;
			size++;

		}

		else
		{
			Node * temp;
			temp = createnode(obj);
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
			size++;


		}

	}
	void addatstart(const char & obj)
	{

		if (size == 0)
		{
			head = createnode(obj);
			tail = head;
			size++;

		}

		else
		{
			Node * temp;
			temp = createnode(obj);
			temp->next = head;
			head->prev = temp;
			head = temp;
			size++;


		}


	}
	void printlist()
	{
		Node * curr;
		curr = head;

		while (curr != tail->next)
		{
			cout << curr->data;
			curr = curr->next;

		}
		cout << endl << " size is " << size << endl;
	}

	void printlisto()
	{
		Node * curr;
		curr = tail;

		while (curr != head->prev)
		{
			cout << curr->data;
			curr = curr->prev;

		}
		cout << endl << "size is " << size << endl;
	}

	void distroylist()
	{

		Node * curr;

		while (head != NULL)
		{
			curr = head;
			head = head->next;
			delete curr;

		}
		tail = NULL;
		size = 0;

	}

	~TextStructure()
	{
		Node * curr;

		while (head != NULL)
		{
			curr = head;
			head = head->next;
			delete curr;

		}
		tail = NULL;
		size = 0;


	}



	//---------------------------- iterator

	class iterate
	{
		Node* curr;
	public:
		iterate(Node * ptr = NULL)
		{
			curr = ptr;

		}

		iterate & operator++()
		{
			curr = curr->next;
			return *this;

		}

		iterate & operator--()
		{
			curr = curr->prev;
			return *this;

		}

		char & operator*()
		{
			return curr->data;

		}

		iterate begin()
		{

			//	return iterate(gethead());


		}
		iterate end()
		{

			return iterate(NULL);


		}

		bool operator!=(const iterate & obj)
		{
			return (curr != obj.curr);

		}

	};

	//---------------------------

	void Readtextfromfile(const string & filename)
	{
		ifstream fin;	// object to read data from file.
		char ch;


		fin.open(filename, ios::in);	// opening file input.txt.

		if (!fin)	//Check if file has been opened or not.
		{
			cout << "Could not open the input file.\n";
			return;
		}

		cout << "Reading data character by character:\n";

		while (!fin.eof())		//Read until end of file.

		{
			ch = fin.get();		//Read a character from file.


			addatend(ch);
		}


		fin.close();		//Close file after reading data.


							// Writing data in File

							//ofstream fout;	//Object to write data in file.

							//fout.open("Output.txt", ios::out);		//open file output.txt. (Previous data in the file will be truncated.)

							//if( fout )		//Check if file has been opened or not.
							//{
							//	Writing in the file.
							//	fout<<"Total Number of characters:\t"<<character_count<<endl;

							//	fout.close();		//Close the file after writing all the data.
							//}
							//else
							//{
							//	If file could not be opened, print error message.
							//	cout<<"File could not be opened.\n";
							//}
							//

	}

	void addcharAfter(char c, Node * ptr)
	{
		if (ptr == NULL || size == 0 || size == 1)
		{
			addatend(c);

		}
		else
		{
			Node * temp;
			temp = createnode(c);
			temp->next = ptr->next;
			temp->prev = ptr;
			ptr->next->prev = temp;
			ptr->next = temp;
			size++;


		}


	}


	void cutKcharsfrom(Node * ptr, int k, string & sub)
	{
		Node * first, *second;

		if (ptr != NULL && size > 2)
		{
			first = ptr->prev;
			second = ptr->next;
			sub.clear();

			for (int i = 0; i < k; i++)
			{
				sub = sub + ptr->data;
				first->next = second;
				second->prev = first;
				delete ptr;
				ptr = second;
				second = second->next;
				size--;

			}
		}
	}

	bool findtext(const string & str, bool direction, Node * & start, Node * & end, Node * & previous)
	{
		int exact = str.size();
		int i = 0;
		int count = 0;


		if (direction == true)
		{
			Node * curr = head;
			while (curr != NULL)
			{
				if (curr->data == str[i])
				{
					count++;
					i++;

				}
				else
				{
					count = 0;
					i = 0;


				}

				if (count == exact)
				{
					end = curr;

					for (int j = 0; j < count - 1; j++)
					{
						curr = curr->prev;

					}
					start = curr;

					previous = curr->prev;
					return true;

				}
				curr = curr->next;


			}

			start = end = NULL;
			return false;

		}

		else if (direction == false)
		{
			Node * curr = tail;
			while (curr != NULL)
			{
				if (curr->data == str[i])
				{
					count++;
					i++;

				}
				else
				{
					count = 0;
					i = 0;


				}

				if (count == exact)
				{
					end = curr;

					for (int j = 0; j < count - 1; j++)
					{
						curr = curr->next;

					}
					start = curr;
					previous = curr->next;

					return true;

				}
				curr = curr->prev;


			}

			start = end = NULL;
			return false;

		}

	}

	void Findandreplace(const string & str1, const string & str2, bool directon)
	{
		if (directon == true)
		{
			string se;
			bool k = true;
			Node*s, *e, *p;
			while (k == true)
			{
				if (findtext(str1, directon, s, e, p) == true)
				{
					cutKcharsfrom(s, str1.size(), se);

					for (int i = 0; i < str2.size(); i++)
					{
						addcharAfter(str2[i], p);
						p = p->next;

					}

				}

				else
				{
					k = false;
				}
			}

		}

		else if (directon == false)
		{
			string se;
			bool k = true;
			Node*s, *e, *p;
			while (k == true)
			{
				if (findtext(str1, directon, s, e, p) == true)
				{
					cutKcharsfrom(e, str1.size(), se);

					for (int i = 0; i < str2.size(); i++)
					{
						addcharAfter(str2[i], p);
						p = p->next;

					}

				}
				else
				{
					k = false;
				}
			}

		}

	}

};






void main()
{
	TextStructure l1, l2, l3;


	l1.addatend(60);
	l1.addatend(100);
	l1.addatstart(75);
	l1.addatend(120);
	l1.addatend(72);

	l2.addatend(65);
	l2.addatend(66);
	l2.addatend(67);



	l3.Readtextfromfile("file1.txt");
	l3.addatend('T');
	
	Node*s, *e, *p;
	bool k;
	string se;

	l3.Findandreplace("yrev", "is", false);

	cout << l3;


	

}