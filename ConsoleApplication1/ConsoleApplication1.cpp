#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** previous, Node** current);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    
    Node* newNode = new Node;

    cout << "Enter roll number: ";
    cin >> newNode->rollNumber;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newNode->name);

    if (listEmpty()) {
        
        newNode->next = newNode;

        
        LAST = newNode;
    }
    else {
        
        Node* current, * previous;
        current = LAST->next;
        previous = NULL;

        
        while (current->rollNumber < newNode->rollNumber && current != LAST) {
            previous = current;
            current = current->next;
        }

        
        newNode->next = current;

        
        previous->next = newNode;
    }
}

bool CircularLinkedList::search(int rollno, Node** previous, Node** current) {
    *previous = LAST->next;
    *current = LAST->next;

    while (*current != LAST) {
        if (rollno == (*current)->rollNumber) {
            return true;
        }
        *previous = *current;
        *current = (*current)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    int rollno;
    cout << "Enter the roll number to delete: ";
    cin >> rollno;

    Node* previous, * current;
    if (search(rollno, &previous, &current)) {
        // Beginning of the list
        if (current == LAST->next) {

            if (current == LAST) {
                LAST = NULL;
                // b. Exit
                return true;
            }
            
            current = LAST->next->next;
            
            LAST->next = current;
        }
        else if (current == LAST) {
            previous->next = LAST->next;
            current = LAST->next;
            
            while (current->next != LAST) {
                previous = current;
                
                current = current->next;
            }
            
            previous->next = current;
            
            current = current->next;
        }
        else {
            current = LAST;
            previous = current->next;
            
            while (previous->next != LAST) {
                
                previous = previous->next;
            }
            
            previous->next = current->next;
            
            previous = current;
            
            delete current;
            
            current = previous->next;
        }

        return true;
    }
    else {
        return false;
    }
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* currentNode = LAST->next;
        while (currentNode != LAST) {
            cout << currentNode->rollNumber << " " << currentNode->name << endl;
            currentNode = currentNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-5): ";

            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                if (obj.delNode()) {
                    cout << "Record deleted successfully\n";
                }
                else {
                    cout << "Record not found\n";
                }
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}

