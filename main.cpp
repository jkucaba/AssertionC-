//struktura przechowuj¹ca pojedynczy obiekt listy (mo¿na przerobiæ na klasê)
#define NDEBUG
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class el {
private:
	int v;
	el* next;
	el* previous;
public:
	el() {
		this -> previous = nullptr;
		this -> next = nullptr;
	};
	el(int v) {
		this -> v = v;
		this -> previous = nullptr;
		this -> next = nullptr;
	};
	el(int v, el* prev, el* n){
        this -> v = v;
		this -> previous = prev;
		this -> next = n;
	}
	int getValue() {
		return v;
	}
	el* getNext() {
		return next;
	}
	el* getPrevoius() {
		return previous;
	}
	void setNext(el* next) {
		this->next = next;
	}
	void setPrevoius(el* prev) {
		this->previous = prev;
	}
	virtual ~el() {};
};
class List {
private:
	el* head;	//przechowuje adres pierwszego elementu listy
	el* tail;	//przechowuje adres ostatniego elementu listy
	el* addHead(int a) {
		el* newHead = new el(a, nullptr, this->getHead());

		assert(newHead != nullptr); // Sprawdzamy czy nowy head nie wskazuje na pustą lukę w pamięci

		this->head->setPrevoius(newHead);
		this->head = newHead;
	};
	el* addTail(int a) {
		el* newTail = new el(a, this->getTail(), nullptr);

		assert(newTail != nullptr); // Sprawdzamy czy nowy tail nie wskazuje na pustą lukę w pamięci

		this->tail->setNext(newTail);
		this->tail = newTail;
	};
    el* removeHead() {
		el* back = head;
		this->head = this->head->getNext();
		delete back;
	};
	el* removeTail() {
		el* back = tail;
		this->tail = this->tail->getPrevoius();
		delete back;
	};
public:
	List() {
		this->head = nullptr;
		this->tail = nullptr;
	};
	virtual ~List(){
        while (head) {
            el* temp = head;
            head = head->getNext();
            delete temp;
        }
	};
	el* add(int a) {
		el* nowy = new el(a);
        //Sprawdzenie czy el nie wskazuje na nullptr
        assert(nowy != nullptr);
		if (!head) {
			head = tail = nowy;
		}
		else if (a <= head->getValue()) {
			nowy->setNext(head);
			head->setPrevoius(nowy);
			head = nowy;
		}
		else if (a >= tail->getValue()) {
			nowy->setPrevoius(tail);
			tail->setNext(nowy);
			tail = nowy;
		}
		else {
			el* current = head->getNext();
			while (current && current->getValue() < a) {
				current = current->getNext();
			}
			nowy->setPrevoius(current->getPrevoius());
			nowy->setNext(current);
			current->getPrevoius()->setNext(nowy);
			current->setPrevoius(nowy);
		}
	};
	void removeValue(int a){
        el* current = head;
        while (current != nullptr) {
            if (current->getValue() == a) {
                if (current == head) {
                    head = current->getNext();
                    if (head != nullptr)
                        head->setPrevoius(nullptr);
                } else if (current == tail) {
                    tail = current->getPrevoius();
                    tail->setNext(nullptr);
                } else {
                    current->getPrevoius()->setNext(current->getNext());
                    current->getNext()->setPrevoius(current->getPrevoius());
                }
                delete current;
                return;
            }
            current = current->getNext();
        }
	};
	void removeList(){
        while (head) {
            el* temp = head;
            head = head->getNext();
            delete temp;
        }
	};
	void showRightToLeft(){
        el* current = tail;
        while (current) {
            cout << current->getValue() << " ";
            current = current->getPrevoius();
        }
        cout << endl;
	};
	void showLeftToRight() {
		el* current = head;
		while (current) {
			std::cout << current->getValue() << " ";
			current = current->getNext();
		}
		cout << endl;
	};
	void swap(el*& tmp, el*& k){
	    // Sprawdzanie czy k nie wskazuje pustej przestrzeni pamięci
	    assert(k != nullptr);

	    // Sprawdzanie czy tmp nie wskazuje pustej przestrzeni pamięci
	    assert(tmp != nullptr);

        // Sprawdzanie czy k i tmp nie wskazują na to samo miejsce
        assert(k != tmp);

        el *kPrev = k->getPrevoius();
        el *kNext = k->getNext();
        el *tmpPrev = tmp->getPrevoius();
        el *tmpNext = tmp->getNext();

        tmpPrev->setNext(k);
        kPrev->setNext(tmp);
        tmp->setPrevoius(kPrev);
        k->setPrevoius(tmpPrev);

        kNext->setPrevoius(tmp);
        tmp->setNext(kNext);
        tmpNext->setPrevoius(k);
        k->setNext(tmpNext);

        if (k == tmp->getNext()){
            tmp->setNext(kNext);
            tmp->setPrevoius(k);
            k->setNext(tmp);
            k->setPrevoius(tmpPrev);
        } else if(tmp == k->getNext()){
            k->setNext(tmpNext);
            k->setPrevoius(tmp);
            tmp->setNext(k);
            tmp->setPrevoius(kPrev);
        }
        if (tmp == this->head){
            this->head=k;
        }
        if (k == this->head){
            this->head=tmp;
        }
        if (tmp == this->tail){
            this->tail=k;
        }
        if (k == this->tail){
            this->tail=tmp;
        }
	};	//zamienia ze sob¹ dwa elementy listy
	el* getHead(){
	return this->head;
	}
	el* getTail(){
	return this->tail;
	}
};
// Funkcja wczytuj¹ca dane z pliku i dodaj¹ca do listy
void readDataFromFile(const string& filename, float minRange, float maxRange) {
    ifstream file(filename);
    assert(file.is_open());

    List *lista = new List();
    //sprawdzanie czy lista nie jest nullptr
    assert(lista != nullptr);

    float value;
    while (file >> value) {
        assert(value >= minRange && value <= maxRange && "Value out of range");
        lista -> add(value);
    }
    file.close();
    lista->showLeftToRight();
    lista->removeList();
}

int main(int argc, char* argv[]) {

    List *list = new List();
    list->add(5);
    list->add(7);
    list->add(6);
    list->showLeftToRight();

    el* drugi = list->getHead();
    el* pierwszy = list->getHead();

    list->swap(pierwszy, drugi);

    return 0;
}
