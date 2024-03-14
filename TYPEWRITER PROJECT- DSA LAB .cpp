//PROJECT NAME: TYPE WRITER - DSA LAB V8
//MADE BY: M. HAROON VIRK (F2022266182) & M. BURHAN AWAIS (F2022266159)
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;
class Node
{
public:
	char data;
	Node* right, * left, * up, * down;
	Node()
	{
		data = '\0';
		right = nullptr;
		left = nullptr;
		up = nullptr;
		down = nullptr;
	}
	~Node()
	{
	}
};
class TwoDDLLADT
{
private:
	Node* cursor, * first;
	void twoWayBackspace()
	{
		if (first == nullptr)
		{
			return;
		}
		if (cursor->right == nullptr && cursor->left == nullptr)
		{
			cursor->data = '\0';
			return;
		}
		if (cursor->left == nullptr)
		{
			cout << "Try removing the first character with 'DELETE' key!" << endl;
			Sleep(3000);
			return;
		}
		if (cursor->left != nullptr)
		{
			cursor->left->right = cursor->right;
			if (cursor->right != nullptr)
			{
				cursor->right->left = cursor->left;
			}
			cursor = cursor->left;
		}
	}
      int wordCount()
    {
        int count = 0;
        Node* temp = first;
        while (temp != nullptr)
        {
            if (temp->data == ' ' || temp->data == '\n')
            {
                count++;
            }
            temp = temp->right;
        }
        return count;
    }
     void findAndReplace(char findChar, char replaceChar)
    {
        Node* temp = first;
        while (temp != nullptr)
        {
            if (temp->data == findChar)
            {
                temp->data = replaceChar;
            }
            temp = temp->right;
        }
    }
    void lineNumbering()
    {
        int lineCount = 1;
        Node* temp = first;
        while (temp != nullptr)
        {
            if (temp->data == '\n')
            {
                cout << "\n" << lineCount << ": ";
                lineCount++;
            }
            else
            {
                cout << temp->data;
            }
            temp = temp->right;
        }
    }
    void wordWrap()
    {
        int lineLength = 0;
        Node* temp = first;
        while (temp != nullptr)
        {
            if (temp->data == ' ' || temp->data == '\n')
            {
                lineLength = 0;
            }
            else
            {
                lineLength++;
                if (lineLength > 20) // Adjust the line length as needed
                {
                    cout << "\n";
                    lineLength = 0;
                }
            }
            cout << temp->data;
            temp = temp->right;
        }
    }
	void threeWayBackspaceUP()
	{
		if (cursor->left == nullptr)
		{
			cout << "Try removing the first character with 'DELETE' key!" << endl;
			Sleep(3000);
			return;
		}
		cursor->left->right = cursor->right;
		if (cursor->right != nullptr)
		{
			cursor->right->left = cursor->left;
		}
		cursor = cursor->left;
		reLink(cursor, cursor->down);
	}
	void threeWayBackspaceDOWN()
	{
		if (cursor->left == nullptr)
		{
			cout << "Try removing the first character with 'DELETE' key!" << endl;
			Sleep(3000);
			return;
		}
		cursor->left->right = cursor->right;
		if (cursor->right != nullptr)
		{
			cursor->right->left = cursor->left;
		}
		cursor = cursor->left;
		reLink(cursor->up, cursor);
	}
	void fourWayBackspace()
	{
		if (cursor->left == nullptr)
		{
			cout << "Try removing the first character with 'DELETE' key!" << endl;
			Sleep(3000);
			return;
		}
		cursor->left->right = cursor->right;
		if (cursor->right != nullptr)
		{
			cursor->right->left = cursor->left;
		}
		cursor = cursor->left;
		reLink(cursor->up, cursor);
		reLink(cursor, cursor->down);
	}
	void twoWayDelete()
	{
		if (first == nullptr)
		{
			return;
		}
		if (cursor->right == nullptr && cursor->left == nullptr)
		{
			cursor->data = '\0';
			return;
		}
		if (cursor->right == nullptr)
		{
			cout << "Try removing the last character with 'BACKSPACE' key!" << endl;
			Sleep(3000);
			return;
		}
		if (cursor->left == nullptr)
		{
			cursor->right->left = nullptr;
			first = first->right;
			cursor = first;
			return;
		}
		if (cursor->left != nullptr)
		{
			cursor->left->right = cursor->right;
			if (cursor->right != nullptr)
			{
				cursor->right->left = cursor->left;
			}
			cursor = cursor->right;
		}
	}
	void threeWayDeleteUP()
	{
		if (cursor->right == nullptr)
		{
			cout << "Try removing the last character with 'BACKSPACE' key!" << endl;
			Sleep(3000);
			return;
		}
		if (cursor->left != nullptr)
		{
			cursor->left->right = cursor->right;
		}
		else
		{
			if (cursor->data != '\n')
			{
				cursor->right->left = nullptr;
				first = first->right;
				cursor = first;
			}
			else if (cursor->data == '\n')
			{
				first = first->down;
				first->left = nullptr;
				cursor = first;

				Node* temporary = first;
				while (temporary->data != '\n')
				{
					temporary->up = nullptr;
					temporary = temporary->right;
					if (temporary == nullptr)
					{
						break;
					}
					if (temporary->data == '\n')
					{
						temporary->up = nullptr;
						break;
					}
				}
				return;
			}
			reLink(cursor, cursor->down->left);
			return;
		}
		if (cursor->right != nullptr)
		{
			cursor->right->left = cursor->left;
		}
		cursor = cursor->right;
		if (cursor->left == nullptr)
		{
			reLink(cursor, cursor->down);
		}
		else
		{
			reLink(cursor->left, cursor->left->down);
		}
	}
	void threeWayDeleteDOWN()
	{
		if (cursor->right == nullptr)
		{
			cout << "Try removing the last character with 'BACKSPACE' key!" << endl;
			Sleep(3000);
			return;
		}
		cursor->left->right = cursor->right;
		if (cursor->right != nullptr)
		{
			cursor->right->left = cursor->left;
		}
		cursor = cursor->right;
		reLink(cursor->left->up, cursor->left);
	}
	void fourWayDelete()
	{
		if (cursor->right == nullptr)
		{
			cout << "Try removing the last character with 'BACKSPACE' key!" << endl;
			Sleep(3000);
			return;
		}
		cursor->left->right = cursor->right;
		if (cursor->right != nullptr)
		{
			cursor->right->left = cursor->left;
		}
		cursor = cursor->right;
		reLink(cursor->left->up, cursor->left);
		reLink(cursor->left, cursor->left->down);
	}
	void reLink(Node* North, Node* South)
	{
		if (South == nullptr)  // Critical (Debugger)
		{
			return;
		}
		if (North == nullptr)
		{
			while (South->data != '\n')
			{
				South->up = nullptr;
				South = South->right;
				if (South == nullptr)
				{
					break;
				}
				if (South->data == '\n')
				{
					South->up = nullptr;
					break;
				}
			}
			return;
		}
		if (North->data == '\n')
		{
			South->up = North;
			North->down = South;
			while (South != nullptr)
			{
				South->up = North;
				South = South->right;
				if (South == nullptr)
				{
					break;
				}
				if (South->data == '\n')
				{
					South->up = North;
					break;
				}
			}
			return;
		}
		else if (South->right == nullptr)
		{
			North->down = South;
			South->up = North;
			while (North->data != '\n')
			{
				North->down = South;
				North = North->right;
				if (North == nullptr)
				{
					break;
				}
				if (North->data == '\n')
				{
					North->down = South;
					break;
				}
			}
			return;
		}
		else if (South->data == '\n')
		{
			North->down = South;
			South->up = North;
			while (North->data != '\n')
			{
				North->down = South;
				North = North->right;
				if (North->data == '\n')
				{
					North->down = South;
					break;
				}
			}
			return;
		}
		North->down = South;
		South->up = North;
		reLink(North->right, South->right);
	}
	void reLinkNotepad()
	{
		Node* temp = first;
		while (temp != nullptr)
		{
			temp->up = nullptr;
			temp->down = nullptr;
			temp = temp->right;
		}
		Node* count = first;
		Node* a = first;
		Node* b = first;
		while (count != nullptr)
		{
			if (b->data == '\n')
			{
				b = b->right;
				reLink(a, b);
				a = b;
			}
			if (b == nullptr)  // Critical (Debugger)
			{
				break;
			}
			b = b->right;
			if (b == nullptr)
			{
				break;
			}
			count = count->right;
		}
	}
	void backspaceEnterKey()
	{
		if (cursor->left != nullptr)
		{
			cursor->left->right = cursor->right;
			if (cursor->right != nullptr)
			{
				cursor->right->left = cursor->left;
			}
			cursor = cursor->left;
		}
		if (first->down->down == nullptr) // Case of there are two lines and user presses BACKSPACE || DELETE
		{
			Node* temp = first;
			while (temp != nullptr)
			{
				temp->up = nullptr;
				temp->down = nullptr;
				temp = temp->right;
			}
			return;
		}
		reLinkNotepad();
	}
	void deleteEnterKey()
	{
		if (cursor->left != nullptr)
		{
			cursor->left->right = cursor->right;
			if (cursor->right != nullptr)
			{
				cursor->right->left = cursor->left;
			}
			cursor = cursor->right;
		}
		if (first->down->down == nullptr) // Case of there are two lines and user presses BACKSPACE || DELETE
		{
			Node* temp = first;
			while (temp != nullptr)
			{
				temp->up = nullptr;
				temp->down = nullptr;
				temp = temp->right;
			}
			return;
		}
		reLinkNotepad();
	}
	void destroy(Node* D) // Stack Overflow error
	{
		if (D == nullptr)
		{
			return;
		}
		destroy(D->right);
		destroy(D->left);
		destroy(D->up);
		destroy(D->down);
		delete D;
		D = nullptr;
	}

	void up()
	{
		if (cursor->up != nullptr)
		{
			cursor = cursor->up;
		}
	}
	void down()
	{
		if (cursor->down != nullptr)
		{
			cursor = cursor->down;
		}
	}
	void right()
	{
		if (cursor->right != nullptr)
		{
			cursor = cursor->right;
		}
	}
	void left()
	{
		if (cursor->left != nullptr)
		{
			cursor = cursor->left;
		}
	}
public:
	TwoDDLLADT()
	{
		SetConsoleTextAttribute(hStdOut, (11 + 0 * 16));
		cursor = nullptr;
		first = nullptr;
		cout << "TwoDDLLADT Constructed!" << endl;
		Sleep(2000);
	}
	void load()
	{
		ifstream inputFile;
		inputFile.open("notepad.txt");
		if (inputFile.is_open())
		{
			while (inputFile)
			{
				char next = '\0';

				Node* emptyNode = new Node;
				inputFile >> emptyNode->data;
				if (inputFile.peek() == '\n')
				{
					next = '\n';
				}
				if (emptyNode->data == '\0')
				{
					break;
				}
				push(emptyNode->data);
				if (next == '\n')
				{
					push('\n');
				}
			}
			inputFile.close();
		}
	}
	void save()
	{
		ofstream outputFile;
		outputFile.open("notepad.txt");
		Node* curr = first;
		while (curr != nullptr)
		{
			outputFile << curr->data;
			curr = curr->right;
		}
		outputFile.close();
	}
	void display()
	{
		Node* curr = first;
		while (curr != nullptr)
		{
			if (curr == cursor)
			{
				SetConsoleTextAttribute(hStdOut, (0 + 11 * 16));
				cout << curr->data;
				curr = curr->right;

			}
			else
			{
				SetConsoleTextAttribute(hStdOut, (11 + 0 * 16));
				cout << curr->data;
				curr = curr->right;
			}
		}
		cout << endl;
		SetConsoleTextAttribute(hStdOut, (11 + 0 * 16));
	}
	void displayNode()
	{
		cout << "-----------------------" << endl;
		if (cursor == nullptr)
			return;
		if (cursor->up == nullptr)
		{
			cout << "      (NULL)" << endl;
		}
		else
			cout << "      (" << cursor->up->data << ")" << endl;
		if (cursor->left == nullptr)
		{
			cout << "(NULL)   ";
		}
		else
			cout << "(" << cursor->left->data << ")   ";
		if (cursor == nullptr)
		{
			cout << "(NULL)   ";
		}
		else
			cout << "(" << cursor->data << ")   ";
		if (cursor->right == nullptr)
		{
			cout << "(NULL)" << endl;
		}
		else
			cout << "(" << cursor->right->data << ")" << endl;
		if (cursor->down == nullptr)
		{
			cout << "(NULL)   " << endl;
		}
		else
			cout << "      (" << cursor->down->data << ")" << endl;
		cout << "-----------------------" << endl;
	}
	void displayHeader()
	{
		SetConsoleTextAttribute(hStdOut, (11 + 0 * 16));
		for (int i = 0;i < 59;i++)
		{
			cout << char(219);
		}cout << endl;
		cout << char(219) << "               Welcome to TYPE WRITER!                   " << char(219) << endl;
		cout << char(219) << "           Made by: Haroon Virk & Burhan Awais           " << char(219) << endl;
		cout << char(219) << " Use Arrow Keys to move cursor UP, DOWN, RIGHT and LEFT. " << char(219) << endl;
		cout << char(219) << " Press 'L' to load data from notepad.txt!                " << char(219) << endl;
		cout << char(219) << " Press '}' to save data to notepad.txt!                  " << char(219) << endl;
		cout << char(219) << " Press 'ENTER Key to continue writing on next line.      " << char(219) << endl;
		cout << char(219) << " Press 'BACKSPACE Key' to remove character.              " << char(219) << endl;
		cout << char(219) << " Press 'DELETE Key' to delete character.                 " << char(219) << endl;
        cout << char(219) << " Press 'W' for Word Count.                               " << char(219) << endl;
        cout << char(219) << " Press 'F' for Find and Replace.                         " << char(219) << endl;
        cout << char(219) << " Press 'N' for Line Numbering.                           " << char(219) << endl;
        cout << char(219) << " Press 'R' for Word Wrap.                                " << char(219) << endl;
		cout << char(219) << " Press 'Q' to quit the notepad.                          " << char(219) << endl;
		cout << char(219) << "                      Start Typing...                    " << char(219) << endl;
		for (int i = 0;i < 59;i++)
		{
			cout << char(219);
		}cout << endl;
		displayNode();
	}
	void push(int val)
	{
		Node* tempVal = new Node;
		tempVal->data = val;

		if (first == nullptr)
		{
			first = tempVal;
			cursor = first;
		}
		else if (first != nullptr)
		{
			if (cursor->right == nullptr)
			{
				Node* curr = first;
				while (curr->right != nullptr)
				{
					curr = curr->right;
				}
				curr->right = tempVal;
				tempVal->left = curr;
				//-----------------------------------------
				if (cursor->data == '\n')
				{
					Node* tempFirst = first;
					while (tempFirst->down != nullptr)
					{
						tempFirst = tempFirst->down;
					}
					tempFirst->down = tempVal;
					tempVal->up = tempFirst;
					cursor = cursor->right;
					return;
				}
				//-----------------------------------------
				cursor = tempVal;

				if (first->down != nullptr)
				{
					reLinkNotepad();
				}
			}
			else if (cursor->right != nullptr)
			{
				tempVal->left = cursor;
				tempVal->right = cursor->right;

				cursor->right->left = tempVal;
				cursor->right = tempVal;
				cursor = tempVal;

				if (first->down != nullptr)
				{
					reLinkNotepad();
				}
				else if (cursor->data == '\n' && first->down == nullptr)
				{
					reLink(first, cursor->right);
				}
			}
		}
	}
	void backspace()
	{
		if (cursor->data == '\n')
		{
			backspaceEnterKey();
			return;
		}
		if (cursor->up == nullptr && cursor->down == nullptr)
		{
			twoWayBackspace();
			return;
		}
		if (cursor->up != nullptr && cursor->down == nullptr)
		{
			threeWayBackspaceDOWN();
			return;
		}
		if (cursor->up == nullptr && cursor->down != nullptr)
		{
			threeWayBackspaceUP();
			return;
		}
		if (cursor->up != nullptr && cursor->down != nullptr)
		{
			fourWayBackspace();
			return;
		}
	}
	void deleteKey()
	{
		if (cursor->data == '\n')
		{
			deleteEnterKey();
			return;
		}
		if (cursor->up == nullptr && cursor->down == nullptr)
		{
			twoWayDelete();
			return;
		}
		if (cursor->up != nullptr && cursor->down == nullptr)
		{
			threeWayDeleteDOWN();
			return;
		}
		if (cursor->up == nullptr && cursor->down != nullptr)
		{
			threeWayDeleteUP();
			return;
		}
		if (cursor->up != nullptr && cursor->down != nullptr)
		{
			fourWayDelete();
			return;
		}
	}
	void build()
	{
		int key = 0;
		while (key != 'Q')
		{
			system("cls");
 			displayHeader();
			display();
			key = _getch();
             if (key == 'W')
            {
                int count = wordCount();
                cout << "\nWord Count: " << count << endl;
                _getch(); // Wait for a key press
            }
            else if (key == 'F')
            {
                char findChar, replaceChar;
                cout << "\nEnter character to find: ";
                findChar = _getch();
                cout << findChar;
                cout << "\nEnter character to replace with: ";
                replaceChar = _getch();
                cout << replaceChar;
                findAndReplace(findChar, replaceChar);
            }
            else if (key == 'N')
            {
                lineNumbering();
                _getch(); // Wait for a key press
            }
            else if (key == 'R')
            {
                wordWrap();
                _getch(); // Wait for a key press
            }
			if (key == 224)
			{
				//key = 0;
				//build();
			}

			else if (key == 72) //UP
			{
				up();
			}
			else if (key == 80) //DOWN
			{
				down();
			}
			else if (key == 75) //LEFT
			{
				left();
			}
			else if (key == 77)  //RIGHT
			{
				right();
			}

			else if (key == 8) //BACKSPACE
			{
				backspace();
			}
			else if (key == -32 || key == 83) //Delete Key
			{
				deleteKey();
			}
			else if (key == 13) // Enter Key
			{
				push('\n');
			}

			else if (key == 'L')
			{
				load();
			}
			else if (key == '}') //'S' replaced by '}' (issue.ASCII=83)
			{
				save();
			}

			else if (key != 224 && key != 'Q')
			{
				push(key);
			}
			else if (key == 'Q')
			{
				save();
				cout << "Saving Progress..." << endl;
				Sleep(3000);
				cout << "Notepad Exited!" << endl;
				return;
			}
		}
	}
};
int main()
{
	TwoDDLLADT obj1;
	obj1.build();
	system("pause");
	return 0;
}