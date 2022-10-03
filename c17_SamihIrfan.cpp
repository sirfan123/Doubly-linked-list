
#include <iostream>
#include <string>
using namespace std;
// define a node for storage and linking
class node
{
public:
    string name;
    node *next;
    node *prevNode;
    // node *prev; // to be implemented by students
};
class linkedList
{
public:
    linkedList() : top(NULL) {}

    bool empty() { return top == NULL; }
    bool emptyEnd() { return end == NULL; }
    node *getTop() { return top; }
    void setTop(node *n) { top = n; }
    node *setEnd() { return end; }
    void getEnd(node *n) { end = n; }
    void add(string);
    int menu();
    string remove(string);
    ~linkedList();
    void reversePrint();                                       // to be implemented by students
    friend ostream &operator<<(ostream &, const linkedList &); // default output is in-order print.
private:
    node *top;
    node *end; // to be used for reverse print and implemented by students
};
//Samih Irfan CIT-245 Assignment 10 6/2/21

int main()
{
    string deleted;
    linkedList l;
    cout << l.empty() << endl;
    cout << l.emptyEnd() << endl;
    int option = 0;
    string s;
    bool go = true;
    while (go)
    {
        option = l.menu();
        switch (option)
        {
        case 1:
            cout << "enter a name: ";
            cin >> s;
            l.add(s);
            break;
        case 2:

            cout << "enter name to be deleted: ";
            cin >> s;
            deleted = l.remove(s);
            if (deleted != "\0")
            {
                cout << "Deleted " << deleted << endl;
            }
            else
            {
                cout << s << " was not found" << endl;
            }

            //l.remove(s);

            break;
        case 3:
            cout << l;
            break;
        case 4:
            l.reversePrint();
            break;
        case 5:
            cout << "exiting" << endl;
            go = false;
            break;
        }
    }
    // l goes out of scope and calls ~linkedList()
    system("pause");
    return 0;
}
// can not call this method "delete" - "delete" is a reserved keyword.
string linkedList::remove(string s)
{

    node *temp = getTop();

    if (temp->name == s)
    {
        if (temp->next != NULL)
        {
            temp->next->prevNode = NULL;
            top = temp->next;
        }
        if (temp->next == NULL)
        {
            top = NULL;
            end = NULL;
        }

        //(*sPtr)->prev = NULL;

        delete (temp);
        return s;
    }

    while (temp != NULL && temp->name != s)
    {
        temp = temp->next;
    }
    if (temp != NULL)
    {

        if (temp->next == NULL)
        {
            temp->prevNode->next = NULL;
            end = temp->prevNode;
            delete (temp);

            return s;
        }

        temp->prevNode->next = temp->next;
        temp->next->prevNode = temp->prevNode;

        delete (temp);
        return s;
    }

    return "\0";
}

void linkedList::add(string s)
{
    node *n = new node();
    n->name = s;
    n->next = NULL;
    n->prevNode = NULL;
    // take care of empty list case
    if (empty())
    {
        top = n;
        end = n;
        // take care of node belongs at beginning case
    }
    else if (getTop()->name > s)
    {
        n->next = getTop();
        setTop(n);
        n->next->prevNode = n;
       
        // take care of inorder and end insert
    }
    else
    {

        // insert in order case
        node *curr = getTop(), *prev = curr;
        while (curr != NULL)
        {
            if (curr->name > s)
                break;
            prev = curr;
            curr = curr->next;
        }
        if (curr != NULL)
        { // search found insert point
            n->next = curr;
            curr->prevNode = n;
            prev->next = n;
            n->prevNode = prev;
        }
        // take care of end of list insertion
        else if (curr == NULL)
        { // search did not find insert point
            prev->next = n;
            n->prevNode = prev;
            //n->next = NULL:
            end = n;
        }
    }
}
ostream &operator<<(ostream &os, const linkedList &ll)
{
    //linkedList x = ll; // put this in and the code blows up - why?
    node *n = ll.top;
    if (n == NULL)
        cout << "List is empty." << endl;
    else
        while (n != NULL)
        {
            os << n->name << endl;
            n = n->next;
        }
    return os;
}
// return memory to heap
linkedList::~linkedList()
{
    cout << "~linkedList called." << endl;
    node *curr = getTop(), *del;
    while (curr != NULL)
    {
        del = curr;
        curr = curr->next;
        delete (del);
    }
}
int linkedList::menu()
{
    int choice = 0;
    while (choice < 1 || choice > 5)
    {
        cout << "\nEnter your choice" << endl;
        cout << " 1. Add a name." << endl;
        cout << " 2. Delete a name." << endl;
        cout << " 3. Show list." << endl;
        cout << " 4. Show reverse list. " << endl; // to be implemented by students
        cout << " 5. EXIT " << endl;
        cin >> choice;
    }
    return choice;
}

void linkedList::reversePrint()
{
    node *n = end;
    cout << "Reverse Print" << endl;
    if (n == NULL)
    {
        cout << "Empty list" << endl;
    }
    else if (n != NULL)
    {
        while (n != NULL)
        {
            cout << n->name << " ";
            n = n->prevNode;
        }
        cout << endl;
    }
}