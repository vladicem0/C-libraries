#pragma once
#ifndef DList_h
#define DList_h


template <class T>
class Node {
public:
	T key;
	Node* next;
	Node* prev;

	Node() { next = NULL; prev = NULL; }

	friend std::ostream& operator<< (std::ostream& out, Node<T>* ptr) {
		if (ptr == NULL) { return out << "Non-existent node"; }
		return out << ptr->key;
	}

	friend std::ostream& operator<< (std::ostream& out, const Node<T>& obj) {
		if (obj == NULL) { return; }
		return out << obj.key;
	}

	friend std::istream& operator>> (std::istream& in, Node<T>& obj) {
		if (obj == NULL) { return; }
		return in >> obj.key;
	}
};


template <class T>
class List {
private:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* current;
	int count;

	Node<T>* findPos(int num) {
		if (num >= count || num < 0) { return NULL; }
		Node<T>* elem = head;
		for (int i = 0; i < num; i++) {
			elem = elem->next;
		}
		return elem;
	}

	Node<T>* findData(T field) {
		Node<T>* elem = head;
		while (elem != NULL) {
			if (elem->key == field) { return elem; };
			elem = elem->next;
		}
		return NULL;
	}
public:
	List() { head = NULL; tail = NULL; current = NULL; count = 0; }

	List(T field) { addHead(field); }

	List(const List<T>& list) {
		Node<T>* out = list.head;
		do {
			addTail(out->key);
			out = out->next;
		} while (out != NULL);
	}
	
	List(T* arr, int size) {
		for (int i = 0; i < size; i++)
			addHead(T[i]);
	}
	~List() { clear(); }

	List<T>& operator++() { 
		if (current->next != NULL)
			current = current->next;
		return *this;
	}

	List<T> operator++(int) {
		List<T> temp{ *this };
		++(*this);
		return temp;
	}

	List<T>& operator--() {
		if (current->prev != NULL)
			current = current->prev;
		return *this;	
	}

	List<T> operator--(int) {
		List<T> temp{ *this };
		--(*this);
		return temp;
	}

	T operator[](int num) {
		Node<T>* ptr = findPos(num);
		if (ptr == NULL)
			return T();
		return ptr->key;	
	}
	/*
	T* operator[](int num) {
		Node<T>* ptr = findPos(num);
		//		if (ptr == NULL)
		//			return T();
		return &(ptr->key);
	}*/

	
	bool isEmpty() { return head == NULL; }
	bool isHead(Node<T>* list) { return head == list; }
	bool isHead() { return head == current; }
	bool isTail(Node<T>* list) { return tail == list; }
	bool isTail() { return tail == current; }

	int getCount() { return count; }

	Node<T>* getHead() { return head; }

	Node<T>* getTail() { return tail; }

	T getCurrent() {
		if (current == NULL)
			return T();
		return current->key;
	}

	T Prev() {
		if (current == head || isEmpty()) { return T(); };
		current = current->prev;
		return current->key;
	}

	T Next() {
		if (current == tail || isEmpty()) { return T(); };
		current = current->next;
		return current->key;
	}

	void addHead(T field) {
		Node<T>* elem = new Node<T>;
		elem->key = field;
		count++;
		if (isEmpty()) { tail = elem; current = elem; }
		else { head->prev = elem; };
		elem->next = head;
		elem->prev = NULL;
		head = elem;
		return;
	}

	void addTail(T field) {
		Node<T>* elem = new Node<T>;
		elem->key = field;
		count++;
		if (isEmpty()) { head = elem; current = elem; }
		else { tail->next = elem; };
		elem->prev = tail;
		elem->next = NULL;
		tail = elem;
		return;
	}

	void insert(T field, int num) {
		if (num > count) { num = count; };
		if (num == 0) { addHead(field); return; };
		if (num == count) { addTail(field); return; };
		Node<T>* elem = new Node<T>;
		Node<T>* curr;
		elem->key = field;
		count++;
		if (num < count / 2) {
			curr = head;
			for (int i = 0; i < num - 1; i++) {
				curr = curr->next;
			}
			elem->next = curr->next;
			elem->prev = curr;
			curr->next->prev = elem;
			curr->next = elem;
		}
		else {
			curr = tail;
			for (int i = count - 1; i > num + 1; i--) {
				curr = curr->prev;
			}
			elem->next = curr;
			elem->prev = curr->prev;
			curr->prev->next = elem;
			curr->prev = elem;

		}
		return;
	}

	T removeHead() {
		if (isEmpty()) { return T(); }
		Node<T>* elem = head;
		if (isTail(elem)) { tail = NULL; };
		count--;
		head = head->next;
		if (!isEmpty()) { head->prev = NULL; }
		else { current = NULL; }
		T key = elem->key;
		delete elem;
		return key;
	}

	T removeTail() {
		if (isEmpty()) { return T(); }
		Node<T>* elem = tail;
		if (isHead(elem)) {
			head = NULL;
			tail = NULL;
		}
		else {
			tail = tail->prev;
			tail->next = NULL;
		}
		count--;
		if (isEmpty()) { current = NULL; }
		T key = elem->key;
		delete elem;
		return key;
	}

	T remove(int num) {
		if (num >= count || num < 0) { return T(); } 
		if (num == 0)
			return removeHead();
		if (num == count - 1)
			return removeTail();
		Node<T>* elem;
		count--;
		if (isEmpty()) { current = NULL; }
		elem = head;
		for (int i = 1; i < num; i++)
			elem = elem->next;
		Node<T>* delElem = elem->next;
		elem->next = delElem->next;
		delElem->next->prev = elem;
		T key = delElem->key;
		delete delElem;
		return key;
	}

	void clear() {
		Node<T>* curr;
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
		count = 0;
		head = NULL;
		tail = NULL;
		current = NULL;
		return;
	}

	void showList() {
		if (isEmpty()) { return; };
		Node<T>* out = head;
		do {
			std::cout << out->key << "\n";
			out = out->next;
		} while (out != NULL);
		return;
	}

	void showListRev() {
		if (isEmpty()) { return; };
		Node<T>* out = tail;
		do {
			std::cout << out->key << "\n";
			out = out->prev;
		} while (out != NULL);
		return;
	}

	void BinRead(std::string name = "file.bin") {
		std::ifstream fin;
		T tmp;
		int size;
		fin.open(name, std::ios::binary | std::ios::in);
		fin >> size;
		for (int i = 0; i < size; i++) {
			fin >> tmp;
			addTail(tmp);
		}
		fin.close();
		return;
	}

	void BinWrite(const char* name = "file.bin") {
		std::ofstream fout;
		fout.open(name, std::ios::binary | std::ios::out);
		if (isEmpty()) { return; };
		fout << count << " ";
		Node<T>* out = head;
		do {
			fout << out->key << " ";
			out = out->next;
		} while (out != NULL);
		fout << std::endl;
		fout.close();
		return;
	}		
};


template <class T>
class Queue :public List<T> {
public:
	Queue() {}
	~Queue() {}

	void push_back(T key) {
		List<T>::addTail(key);
		return;
	}

	T pop_head() {
		return List<T>::removeHead();
	}
};


template <class T>
class Deque :protected List<T> {
public:
	Deque() {}
	~Deque() {}

	bool isEmpty() {
		return List<T>::isEmpty();
	}

	void push_front(T key) {
		List<T>::addHead(key);
		return;
	}

	void push_back(T key) {
		List<T>::addTail(key);
		return;
	}

	T pop_head() {
		return List<T>::removeHead();
	}

	T pop_tail() {
		return List<T>::removeTail();
	}

	void clear() {
		return List<T>::clear();
	}
};


template <class T>
class Stack :private List<T> {
public:
	Stack() {}
	~Stack() {}

	bool isEmpty() {
		return List<T>::isEmpty();
	}

	void push_front(T key) {
		List<T>::addHead(key);
		return;
	}

	T pop_head() {
		return List<T>::removeHead();
	}

	void clear() {
		return List<T>::clear();
	}
};


#endif
