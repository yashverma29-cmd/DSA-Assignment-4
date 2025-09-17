#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// 1. Simple Queue Implementation
class SimpleQueue {
private:
    int front, rear, capacity;
    int* queue;
public:
    SimpleQueue(int size) {
        capacity = size;
        queue = new int[capacity];
        front = rear = -1;
    }

    ~SimpleQueue() {
        delete[] queue;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % capacity == front;
    }

    void enqueue(int item) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        
        queue[rear] = item;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return INT_MIN;
        }
        
        int item = queue[front];
        
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        
        return item;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear) break;
            i = (i + 1) % capacity;
        }
        cout << endl;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return INT_MIN;
        }
        return queue[front];
    }
};

// 2. Circular Queue Implementation
class CircularQueue {
private:
    int front, rear, capacity;
    int* queue;
public:
    CircularQueue(int size) {
        capacity = size;
        queue = new int[capacity];
        front = rear = -1;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (rear + 1) % capacity == front;
    }

    void enqueue(int item) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        
        queue[rear] = item;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return INT_MIN;
        }
        
        int item = queue[front];
        
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        
        return item;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear) break;
            i = (i + 1) % capacity;
        }
        cout << endl;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return INT_MIN;
        }
        return queue[front];
    }
};

// 3. Interleave first half with second half
void interleaveQueue(queue<int>& q) {
    if (q.size() % 2 != 0) {
        cout << "Queue size must be even\n";
        return;
    }
    
    stack<int> s;
    int halfSize = q.size() / 2;
    
    // Push first half to stack
    for (int i = 0; i < halfSize; i++) {
        s.push(q.front());
        q.pop();
    }
    
    // Add stack elements to end of queue
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    
    // Dequeue first half and enqueue to end
    for (int i = 0; i < halfSize; i++) {
        q.push(q.front());
        q.pop();
    }
    
    // Push first half to stack again
    for (int i = 0; i < halfSize; i++) {
        s.push(q.front());
        q.pop();
    }
    
    // Interleave elements from stack and queue
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
        q.push(q.front());
        q.pop();
    }
}

// 4. First non-repeating character using Queue
vector<string> firstNonRepeatingChar(string str) {
    unordered_map<char, int> freq;
    queue<char> q;
    vector<string> result;
    
    for (char c : str) {
        freq[c]++;
        q.push(c);
        
        while (!q.empty() && freq[q.front()] > 1) {
            q.pop();
        }
        
        if (q.empty()) {
            result.push_back("-1");
        } else {
            result.push_back(string(1, q.front()));
        }
    }
    
    return result;
}

// 5a. Stack using Two Queues
class StackTwoQueues {
private:
    queue<int> q1, q2;
public:
    void push(int x) {
        q2.push(x);
        
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        swap(q1, q2);
    }
    
    int pop() {
        if (q1.empty()) {
            cout << "Stack is empty\n";
            return INT_MIN;
        }
        int top = q1.front();
        q1.pop();
        return top;
    }
    
    int top() {
        if (q1.empty()) {
            cout << "Stack is empty\n";
            return INT_MIN;
        }
        return q1.front();
    }
    
    bool isEmpty() {
        return q1.empty();
    }
};

// 5b. Stack using One Queue
class StackOneQueue {
private:
    queue<int> q;
public:
    void push(int x) {
        q.push(x);
        
        for (int i = 0; i < q.size() - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        if (q.empty()) {
            cout << "Stack is empty\n";
            return INT_MIN;
        }
        int top = q.front();
        q.pop();
        return top;
    }
    
    int top() {
        if (q.empty()) {
            cout << "Stack is empty\n";
            return INT_MIN;
        }
        return q.front();
    }
    
    bool isEmpty() {
        return q.empty();
    }
};

// Additional Question 1: Generate binary numbers from 1 to n
vector<string> generateBinaryNumbers(int n) {
    vector<string> result;
    queue<string> q;
    q.push("1");
    
    for (int i = 0; i < n; i++) {
        string current = q.front();
        q.pop();
        result.push_back(current);
        
        q.push(current + "0");
        q.push(current + "1");
    }
    
    return result;
}

// Additional Question 2: Sort queue without extra space
void sortQueue(queue<int>& q) {
    if (q.empty()) return;
    
    for (int i = 0; i < q.size(); i++) {
        int minIndex = -1;
        int minVal = INT_MAX;
        int n = q.size();
        
        for (int j = 0; j < n; j++) {
            int current = q.front();
            q.pop();
            
            if (current <= minVal && j < n - i) {
                if (minIndex != -1) {
                    q.push(minVal);
                }
                minVal = current;
                minIndex = j;
            } else {
                q.push(current);
            }
        }
        
        for (int j = n; j > 0; j--) {
            int current = q.front();
            q.pop();
            
            if (j - 1 != minIndex) {
                q.push(current);
            }
        }
        
        q.push(minVal);
    }
}

// Additional Question 3: Check if queue can be sorted using stack
bool canBeSorted(queue<int>& q) {
    stack<int> st;
    int expected = 1;
    
    while (!q.empty()) {
        if (q.front() == expected) {
            q.pop();
            expected++;
        } else {
            if (!st.empty() && st.top() == expected) {
                st.pop();
                expected++;
            } else {
                st.push(q.front());
                q.pop();
            }
        }
    }
    
    while (!st.empty() && st.top() == expected) {
        st.pop();
        expected++;
    }
    
    return st.empty();
}

// Additional Question 4: Number of students unable to eat lunch
int countStudents(vector<int>& students, vector<int>& sandwiches) {
    queue<int> q;
    for (int student : students) {
        q.push(student);
    }
    
    int i = 0, count = 0;
    while (!q.empty() && count < q.size()) {
        if (q.front() == sandwiches[i]) {
            q.pop();
            i++;
            count = 0;
        } else {
            q.push(q.front());
            q.pop();
            count++;
        }
    }
    
    return q.size();
}

// Menu functions
void simpleQueueMenu() {
    int size, choice, item;
    cout << "Enter size of simple queue: ";
    cin >> size;
    SimpleQueue sq(size);
    
    do {
        cout << "\nSimple Queue Operations:\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Peek\n5. Check if empty\n6. Check if full\n0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter item to enqueue: ";
                cin >> item;
                sq.enqueue(item);
                break;
            case 2:
                item = sq.dequeue();
                if (item != INT_MIN) cout << "Dequeued: " << item << endl;
                break;
            case 3:
                sq.display();
                break;
            case 4:
                item = sq.peek();
                if (item != INT_MIN) cout << "Front element: " << item << endl;
                break;
            case 5:
                cout << (sq.isEmpty() ? "Queue is empty" : "Queue is not empty") << endl;
                break;
            case 6:
                cout << (sq.isFull() ? "Queue is full" : "Queue is not full") << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);
}

void circularQueueMenu() {
    int size, choice, item;
    cout << "Enter size of circular queue: ";
    cin >> size;
    CircularQueue cq(size);
    
    do {
        cout << "\nCircular Queue Operations:\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Peek\n5. Check if empty\n6. Check if full\n0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter item to enqueue: ";
                cin >> item;
                cq.enqueue(item);
                break;
            case 2:
                item = cq.dequeue();
                if (item != INT_MIN) cout << "Dequeued: " << item << endl;
                break;
            case 3:
                cq.display();
                break;
            case 4:
                item = cq.peek();
                if (item != INT_MIN) cout << "Front element: " << item << endl;
                break;
            case 5:
                cout << (cq.isEmpty() ? "Queue is empty" : "Queue is not empty") << endl;
                break;
            case 6:
                cout << (cq.isFull() ? "Queue is full" : "Queue is not full") << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);
}

void interleaveMenu() {
    int n, value;
    cout << "Enter number of elements (must be even): ";
    cin >> n;
    
    if (n % 2 != 0) {
        cout << "Number of elements must be even\n";
        return;
    }
    
    queue<int> q;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.push(value);
    }
    
    cout << "Original queue: ";
    queue<int> temp = q;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
    
    interleaveQueue(q);
    
    cout << "Interleaved queue: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void nonRepeatingMenu() {
    string str;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, str);
    
    vector<string> result = firstNonRepeatingChar(str);
    
    cout << "First non-repeating characters: ";
    for (const string& s : result) {
        cout << s << " ";
    }
    cout << endl;
}

void stackTwoQueuesMenu() {
    StackTwoQueues st;
    int choice, item;
    
    do {
        cout << "\nStack using Two Queues Operations:\n";
        cout << "1. Push\n2. Pop\n3. Top\n4. Check if empty\n0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter item to push: ";
                cin >> item;
                st.push(item);
                break;
            case 2:
                item = st.pop();
                if (item != INT_MIN) cout << "Popped: " << item << endl;
                break;
            case 3:
                item = st.top();
                if (item != INT_MIN) cout << "Top element: " << item << endl;
                break;
            case 4:
                cout << (st.isEmpty() ? "Stack is empty" : "Stack is not empty") << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);
}

void stackOneQueueMenu() {
    StackOneQueue st;
    int choice, item;
    
    do {
        cout << "\nStack using One Queue Operations:\n";
        cout << "1. Push\n2. Pop\n3. Top\n4. Check if empty\n0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter item to push: ";
                cin >> item;
                st.push(item);
                break;
            case 2:
                item = st.pop();
                if (item != INT_MIN) cout << "Popped: " << item << endl;
                break;
            case 3:
                item = st.top();
                if (item != INT_MIN) cout << "Top element: " << item << endl;
                break;
            case 4:
                cout << (st.isEmpty() ? "Stack is empty" : "Stack is not empty") << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);
}

void binaryNumbersMenu() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    
    vector<string> result = generateBinaryNumbers(n);
    
    cout << "Binary numbers from 1 to " << n << ": ";
    for (const string& s : result) {
        cout << s << " ";
    }
    cout << endl;
}

void sortQueueMenu() {
    int n, value;
    cout << "Enter number of elements: ";
    cin >> n;
    
    queue<int> q;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.push(value);
    }
    
    cout << "Original queue: ";
    queue<int> temp = q;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
    
    sortQueue(q);
    
    cout << "Sorted queue: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void checkSortableMenu() {
    int n, value;
    cout << "Enter number of elements: ";
    cin >> n;
    
    queue<int> q;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.push(value);
    }
    
    cout << (canBeSorted(q) ? "Yes" : "No") << endl;
}

void lunchMenu() {
    int n, value;
    cout << "Enter number of students: ";
    cin >> n;
    
    vector<int> students, sandwiches;
    
    cout << "Enter student preferences (0 for circular, 1 for square): ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        students.push_back(value);
    }
    
    cout << "Enter sandwich types (0 for circular, 1 for square): ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        sandwiches.push_back(value);
    }
    
    int result = countStudents(students, sandwiches);
    cout << "Number of students unable to eat: " << result << endl;
}

int main() {
    int choice;
    
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Simple Queue Operations\n";
        cout << "2. Circular Queue Operations\n";
        cout << "3. Interleave Queue\n";
        cout << "4. First Non-Repeating Character\n";
        cout << "5. Stack using Two Queues\n";
        cout << "6. Stack using One Queue\n";
        cout << "7. Generate Binary Numbers\n";
        cout << "8. Sort Queue\n";
        cout << "9. Check if Queue can be Sorted\n";
        cout << "10. Students and Sandwiches\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                simpleQueueMenu();
                break;
            case 2:
                circularQueueMenu();
                break;
            case 3:
                interleaveMenu();
                break;
            case 4:
                nonRepeatingMenu();
                break;
            case 5:
                stackTwoQueuesMenu();
                break;
            case 6:
                stackOneQueueMenu();
                break;
            case 7:
                binaryNumbersMenu();
                break;
            case 8:
                sortQueueMenu();
                break;
            case 9:
                checkSortableMenu();
                break;
            case 10:
                lunchMenu();
                break;
            case 0:
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 0);
    
    return 0;
}