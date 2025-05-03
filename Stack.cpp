class Stack {
    private:
        int capacity;    // Maximum number of elements the stack can hold
        int nextIndex;   // Points to the next available position (also represents current size)
        int *array;      // Dynamic array to store stack elements

    public:
        // Default constructor - creates stack with default capacity of 4
        Stack(){
            capacity = 4;
            nextIndex = 0;
            array = new int[capacity]; // Allocate memory for the stack
        }

        // Parameterized constructor - creates stack with user-specified capacity
        Stack(int capacity){
            nextIndex = 0;
            array = new int[capacity]; // Allocate memory with given capacity
            this->capacity = capacity; // Set the stack's maximum capacity
        }

        // Check if stack is empty
        bool isEmpty(){
            return nextIndex == 0; // True if nextIndex is at starting position
        }

        // Check if stack is full
        bool isFull(){
            return nextIndex == capacity; // True if nextIndex reaches capacity
        }

        // Add an element to the top of the stack
        void push(int data){
            if(!isFull()){
                array[nextIndex] = data; // Store data at current top position
                nextIndex++;             // Move top pointer up
            } else {
                cout << "Stack is full" << endl; // Error if stack is full
            }
        }

        // Remove the top element from the stack
        void pop(){
            if(!isEmpty()){
                nextIndex--; // Simply move top pointer down (LIFO principle)
            } else {
                cout << "Stack is empty" << endl; // Error if stack is empty
            }
        }

        // Display all elements in the stack
        void print(){
            // Iterate from bottom to top of stack
            for (int i = 0; i < nextIndex; i++){
                cout << array[i] << " "; // Print each element
            }
            cout << endl;
        }
        
        // Note: This implementation is missing a destructor to free memory!
        // Should add: ~Stack() { delete[] array; }
};
#include <iostream>

using namespace std;

class Stack {
    private:
        int capacity;
        int nextIndex;
        int *array;

    public:
        Stack(){
            capacity = 4;
            nextIndex = 0;
            array = new int[capacity];
        }

        Stack(int capacity){
            nextIndex = 0;
            array = new int[capacity];
            this->capacity = capacity;
        }

        bool isEmpty(){
            return nextIndex == 0;
        }

        bool isFull(){
            return nextIndex == capacity;
        }

        void push(int data){
            if(!isFull()){
                array[nextIndex] = data;
                nextIndex++;
            } else {
                cout << "Stack is full" << endl;
            }
        }

        void pop(){
            if(!isEmpty()){
                nextIndex--;
            } else {
                cout << "Stack is empty" << endl;
            }
        }

        void print(){
            for (int i = 0; i < nextIndex; i++){
                cout << array[i] << " ";
            }
            cout << endl;
        }
};

struct Node {
    int data;
    Node *next;
};

class LinkedList {
    private:
        Node *head;
        Node *tail;

    public:
        LinkedList(){
            head = nullptr;
            tail = nullptr;
        }

        void insert(int data){
            // we make the new node 
            Node *newNode = new Node();
            newNode->data = data;
            newNode->next = nullptr;

            if(head == nullptr){
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }   
        
        void print(){
            Node *current = head;
            while(current != nullptr){
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }

        void deleteTail(){
            if(head == nullptr || head->next == nullptr)
                head = nullptr;
            else {
                Node* current = head;
                while(current->next->next){
                    current = current->next;
                }
                delete current->next;
                current->next = nullptr;
            }
        }

        void sort(){
            // Check if the list is empty or has only one element
            if (head == nullptr || head->next == nullptr)
                return;

            bool swapped = true;
            while(swapped){
                swapped = false;
                Node *current = head;
                while (current->next != nullptr){
                    if (current->data > current->next->data){
                        // Swap the data.
                        swap(current->data, current->next->data);
                        swapped = true;
                    }
                    current = current->next;
                }
            }     

        }
};

class Queue {
    private:
        Node *rear;
        Node *front;
    
    public:
        Queue() : front(nullptr), rear(nullptr){};

        void enqueue(int data){
            Node *newNode = new Node();
            newNode->data = data;
            newNode->next = nullptr;

            if(rear == nullptr){
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        void dequeue(){
            if(front == nullptr){
                cout << "Queue is empty" << endl;
                return;
            }

            Node *temp = front;
            front = front->next;

            if(front == nullptr){
                rear = nullptr;
            }
            delete temp;
        }

        void print(){
            Node* current = front;
            while(current != nullptr){
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};

void linkedlist_operation(){
    LinkedList linkedList = LinkedList();
    for (int i = 0; i < 4; i++){
        int input;
        cout << "Enter the value for the node " << i + 1 << ": ";
        cin >> input; // Read an integer input from each node.
        linkedList.insert(input);
        cin.ignore(); // Discard the leftover newline (and any extra characters.)
        // cin.ignore is important due to it gives us ability to ignore the newline character that's appended on each input we read and prevent from being chained to subsequent requests.
    }

    cout << "The current linked list is: ";
    linkedList.print();
}

void stack_operation(){
    Stack stack = Stack();
    for (int i = 0; i < 4; i++){
        int input;
        cout << "Enter the value for the stack " << i + 1 << ": ";
        cin >> input; // Read an integer input from each node.
        stack.push(input);
        cin.ignore(); // Discard the leftover newline (and any extra characters.)
        cout << endl;
    }
    stack.pop();
    cout << "Stack elements after 5 pushing and 1 pop operation : ";
    stack.print();
}

void queue_operation(){
    Queue queue = Queue();
    for (int i = 0; i < 5; i++){
        int input;
        cout << "Enter the value for the queue " << i + 1 << ": ";
        cin >> input; // Read an integer input from each node.
        queue.enqueue(input);
        cin.ignore(); // Discard the leftover newline (and any extra characters.)
        cout << endl;
    }
    queue.dequeue();
    cout << "Queue elements after 5 enqueue and 1 dequeue operation: ";
    queue.print();
}

int main(int argc, char *argv[]){
    int choice;
    cout << "Enter your choice: " << endl;
    cout << "1. Operate on the linked list. " << endl;
    cout << "2. Operate on the stack." << endl;
    cout << "3. Operate on the queue." << endl;
    cout << "4. Exit." << endl;
    
    cin >> choice;
    switch(choice){
        case 1: {
            linkedlist_operation();
            break;
        }
        case 2: {
            stack_operation();
            break;
        }
        case 3: {
            queue_operation();
            break;
        }
        default: {
            cout << "Exiting " << endl;
            return 0;
        }
    }

    return 0;
}
