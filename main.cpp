#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
        Node<T>* current = other.head;
        if (current) {
            do {
                push_tail(current->data);
                current = current->next;
            } while (current != other.head);
        }
    }

    LinkedList(int count, int seed) : head(nullptr), tail(nullptr), size(0) {
        srand(seed);
        for (int i = 0; i < count; ++i) {
            push_tail(rand() % 100);
        }
    }

    ~LinkedList() {
        clear();
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.head;
            if (current) {
                do {
                    push_tail(current->data);
                    current = current->next;
                } while (current != other.head);
            }
        }
        return *this;
    }

    void push_tail(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (!head) {
            head = tail = new_node;
            head->next = head;
            head->prev = head;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            new_node->next = head;
            head->prev = new_node;
            tail = new_node;
        }
        size++;
    }

    void push_tail(const LinkedList<T>& other) {
        if (other.head == nullptr) return;
        Node<T>* current = other.head;
        if (current) {
            do {
                push_tail(current->data);
                current = current->next;
            } while (current != other.head);
        }
    }

    void push_head(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (!head) {
            head = tail = new_node;
            head->next = head;
            head->prev = head;
        }
        else {
            new_node->next = head;
            new_node->prev = tail;
            tail->next = new_node;
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }

    void push_head(const LinkedList<T>& other) {
        if (other.head == nullptr) return;

        Node<T>* current = other.tail;
        do {
            push_head(current->data);
            current = current->prev;
        } while (current != other.tail);

    }
    
    void pop_head() {
        if (head == nullptr) {
            throw length_error("list is empty");
        }
        Node<T>* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
        size--;
    }

    void pop_tail() {
        if (head == nullptr) {
            throw length_error("list is empty");
        }
        Node<T>* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
        }
        delete temp;
        size--;
    }

    void delete_node(const T & value) {
        Node<T>* current = head;
        if (current == nullptr) {
            return;
        }
        do {
            Node<T>* nextNode = current->next;
            if (current->data == value) {
                if (current == head) {
                    pop_head();
                }
                else if (current == tail) {
                    pop_tail();
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    size--;
                }
            }
            current = nextNode;
        } while (current != head);
    }

    const T& operator[](size_t index) const {
        if (index >= size) 
            throw out_of_range("index out of range");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }


    T& operator[](size_t index) {
        if (index >= size) 
            throw out_of_range("index out of range");
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void clear() {
        while (head) {
            pop_head();
        }
    }

    void out() const {
        Node<T>* current = head;
        if (current) {
            do {
                cout << current->data << " ";
                current = current->next;
            } while (current != head);
            cout << endl;
        }
        else {
            cout << "list is empty" << endl;
        }
    }
    size_t get_size() const {
        return size;
    }

    Node<T>* get_head() const {
        return head;
    }

    Node<T>* get_tail() const {
        return tail;
    }

    void set_head(Node<T>* new_head) {
        head = new_head;
    }

    void set_tail(Node<T>* new_tail) {
        tail = new_tail;
    }
};

template <typename T>
void reverse(LinkedList<T>& list) {
    if (list.get_head() == nullptr || list.get_head() == list.get_tail()) {
        return;
    }
    Node<T>* current = list.get_head();
    Node<T>* temp = nullptr;

    do {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; //cause the pointer which led to the next is leading to previous now
    } while (current != list.get_head());

    temp = list.get_head();
    list.set_head(list.get_tail());
    list.set_tail(temp);
}

void menu() {
    cout << "menu:\n";
    cout << "1 create random list with seed\n";
    cout << "2 add value to tail\n";
    cout << "3 create new list and add it to tail of existing\n";
    cout << "4 add value to head\n";
    cout << "5 create new list and add it to head of existing\n";
    cout << "6 remove value from head\n";
    cout << "7 remove value from tail\n";
    cout << "8 delete all nodes with a specific value\n";
    cout << "9 access value by index r\n";
    cout << "10 access value by index w\n";
    cout << "11 display current list\n"; 
    cout << "12 reverse the list\n";
    cout << "0 exit\n";
}

int main() {
    LinkedList<int> list;
    int choice, value, index;
        do {
            menu();
            cout << "choose an option ";
            cin >> choice;
            try {
                switch (choice) {
                case 1: {
                    int count;
                    unsigned int seed;
                    cout << "enter the number of elements to add ";
                    cin >> count;
                    cout << "enter seed for random number generation ";
                    cin >> seed;
                    LinkedList<int> new_list(count, seed);
                    list.push_tail(new_list);
                    list.out();
                    break;
                }
                case 2: {
                    cout << "enter value to add to tail ";
                    cin >> value;
                    list.push_tail(value);
                    list.out();
                    break;
                }
                case 3: {
                    LinkedList<int> new_list;
                    int input_value;
                    cout << "enter values for the new list (enter 0 to finish)\n";
                    while (true) {
                        cout << "enter value: ";
                        cin >> input_value;
                        if (input_value == 0) break;
                        new_list.push_tail(input_value);
                    }
                    cout << "current new list: ";
                    new_list.out();
                    list.push_tail(new_list);
                    cout << "new list created and added to the tail of existing list\n";
                    break;
                }
                case 4: {
                    cout << "enter value to add to head ";
                    cin >> value;
                    list.push_head(value);
                    list.out();
                    break;
                }
                case 5: {
                    LinkedList<int> new_list;
                    int input_value;
                    cout << "enter values for the new list (enter 0 to finish)\n";
                    while (true) {
                        cout << "enter value ";
                        cin >> input_value;
                        if (input_value == 0) break;
                        new_list.push_head(input_value);
                    }
                    cout << "current new list ";
                    new_list.out();
                    list.push_head(new_list);
                    cout << "new list created and added to the existing list\n";
                    break;
                }
                case 6: {
                    list.pop_head();
                    cout << "removed element from head\n";
                    break;
                }
                case 7: {
                    list.pop_tail();
                    cout << "removed element from tail\n";
                    break;
                }
                case 8: {
                    cout << "enter value to delete ";
                    cin >> value;
                    list.delete_node(value);
                    list.out();
                    break;
                }
                case 9: {
                    cout << "enter index to access r ";
                    cin >> index;
                    cout << "value at index " << index << " " << list[index] << endl;
                    break;
                }
                case 10: {
                    cout << "enter index to access w ";
                    cin >> index;
                    cout << "enter new value ";
                    cin >> value;
                    list[index] = value;
                    cout << "value at index " << index << " written\n";
                    list.out();
                    break;
                }
                case 11: {
                    cout << "current list ";
                    list.out();
                    break;
                }
                case 12: {
                    reverse(list);
                    cout << "list has been reversed\n";
                    cout << "current list ";
                    list.out();
                    break;
                }
                case 0: {
                    break;
                }
                default:
                    cout << "invalid option\n";
                }
            }
            catch (const length_error& e) {
                cout << "error " << e.what() << endl;
            }
            catch (const logic_error& e) {
                cout << "error " << e.what() << endl;
            }
        } while (choice != 0);

    return 0;
}