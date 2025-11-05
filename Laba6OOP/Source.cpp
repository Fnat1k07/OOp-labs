#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
void invertArray(T arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        T temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };

    Node* front; 
    Node* rear;   
    int count;  

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    void enqueue(T value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            throw runtime_error("Помилка: черга порожня, видалення неможливе!");
        }
        Node* temp = front;
        front = front->next;
        delete temp;
        count--;
        if (front == nullptr) rear = nullptr;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int size() const {
        return count;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Черга порожня!\n";
            return;
        }
        Node* current = front;
        cout << "Елементи черги: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};


int main() {
    setlocale(LC_ALL, "Ukr");

    cout << "=== Завдання 1: Iнверciя масиву ===\n";
    const int n = 5;
    int arr[n] = { 3, 5, 2, 8, 6 };

    cout << "Початковий масив: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    invertArray(arr, n);

    cout << "Пiсля iнверсiї:   ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    cout << "\n=== Завдання 2: Черга на зв’язаному списку ===\n";

    Queue<string> q;

    q.enqueue("Лаба");
    q.enqueue("Програмування");
    q.enqueue("Модуль");
    q.enqueue("Сесiя");

    q.display();
    cout << "Кiлькість елементiв: " << q.size() << endl;

    cout << "Видаляємо два елементи...\n";
    q.dequeue();
    q.dequeue();

    q.display();
    cout << "Кількість елементів: " << q.size() << endl;

    return 0;
}
