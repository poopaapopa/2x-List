#include <iostream>
using namespace std;

struct Element
{
	int data;
	Element* Next = NULL;
	Element* prev = NULL;
};
class List
{
	Element* Head;
	Element* Tail;
	Element* prev;
	int count;
public:
	List()
	{
		Head = Tail = NULL;
		count = 0;
	}
	List(const List& L)
	{
		Head = Tail = NULL;
		count = 0;
		Element* temp = L.Head;
		while (temp != 0)
		{
			AddTail(temp->data);
			temp = temp->Next;
		}
	}
	~List()
	{
		DelAll();
	}
	void AddHead(int n)
	{
		Element* temp = new Element;
		temp->prev = 0;
		temp->data = n;
		temp->Next = Head;
		if (Head != 0)
			Head->prev = temp;
		if (count == 0)
			Head = Tail = temp;
		else
			Head = temp;
		count++;
	}
	void AddTail(int n)
	{
		Element* temp = new Element;
		temp->prev = 0;
		temp->data = n;
		temp->prev = Tail;
		if (Tail != 0)
			Tail->Next = temp;
		if (count == 0)
			Head = Tail = temp;
		else
			Tail = temp;
		count++;
	}
	void Insert(int pos = 0)
	{
		if (pos == 0)
		{
			cout << "Введите позицию ";
			cin >> pos;
		}
		if (pos<1 or pos>count + 1)
		{
			cout << "Неккоректный ввод позиции!!!";
			return;
		}
		if (pos == count + 1)
		{
			int data;
			cout << "Введите значение ";
			cin >> data;
			AddTail(data);
			return;
		}
		else if (pos == 1)
		{
			int data;
			cout << "Введите значение ";
			cin >> data;
			AddHead(data);
			return;
		}
		int i = 1;
		Element* Ins = Head;
		while (i < pos)
		{
			Ins = Ins->Next;
			i++;
		}
		Element* PrevIns = Ins->prev;
		Element* temp = new Element;
		cout << "Введите данные ";
		cin >> temp->data;
		if (PrevIns != 0 and count != 1)
			PrevIns->Next = temp;
		temp->Next = Ins;
		temp->prev = PrevIns;
		Ins->prev = temp;
		count++;
	}
	int GetCount()
	{
		return count;
	}
	Element* GetElement(int pos)
	{
		Element* temp = Head;
		if (pos<1 or pos>count)
		{
			cout << "Incorrect poition!!!!!\n";
			return 0;
		}
		int i = 1;
		while (i < pos and temp != 0)
		{
			temp = temp->Next;
			i++;
		}
		if (temp == 0)
			return 0;
		else
			return temp;
	}
	void Del(int pos = 0)
	{
		if (pos == 0)
		{
			cout << "Введите позицию ";
			cin >> pos;
		}
		if (pos < 1 or pos>count)
		{
			cout << "Неккоректный ввод позиции!!!";
			return;
		}
		int i = 1;
		Element* Del = Head;
		while (i < pos)
		{
			Del = Del->Next;
			i++;
		}
		Element* PrevDel = Del->prev;
		Element* AfterDel = Del->Next;
		if (PrevDel != 0 and count != 1)
			PrevDel->Next = AfterDel;
		if (AfterDel != 0 and count != 1)
			AfterDel->prev = PrevDel;
		if (pos == 1)
			Head = AfterDel;
		if (pos == count)
			Tail = PrevDel;
		delete Del;
		count--;
	}
	void DelAll()
	{
		while (count != 0)
			Del(1);
	}
	void Print()
	{
		Element* temp = Head;
		cout << "(";
		while (temp->Next != 0)
		{
			cout << temp->data << " ";
			temp = temp->Next;
		}
		cout << temp->data << ")\n";
	}
	void Print(int pos)
	{
		if (pos<1 or pos>count)
		{
			cout << "Incorrect poition!!!!!\n";
			return;
		}
		Element* temp;
		if (pos <= count / 2)
		{
			temp = Head;
			int i = 1;
			while (i < pos)
			{
				temp = temp->Next;
				i++;
			}
		}
		else
		{
			temp = Tail;
			int i = 1;
			while (i <= count - pos)
			{
				temp = temp->prev;
				i++;
			}
		}
		cout << pos << " element" << temp->data << "\n";
	}
	List operator+(const List& L)
	{
		List Result(*this);
		Element* temp = L.Head;
		while (temp != 0)
		{
			Result.AddTail(temp->data);
			temp = temp->Next;
		}
		return Result;
	}
	List operator=(const List& L)
	{
		if (this == &L)
			return *this;
		this->~List();
		Element* temp = L.Head;
		while (temp != 0)
		{
			AddTail(temp->data);
			temp = temp->Next;
		}
		return *this;
	}
	bool operator==(const List& L)
	{
		if (count != L.count)
			return false;
		Element* t1;
		Element* t2;
		t1 = Head;
		t2 = L.Head;
		while (t1 != 0)
		{
			if (t1->data != t2->data)
				return 0;
			t1 = t1->Next;
			t2 = t2->Next;
		}
		return 1;
	}
	bool operator!=(const List& L)
	{
		return !(*this == L);
	}
	bool operator>=(const List& L)
	{
		if (count > L.count)
			return 1;
		if (*this == L)
			return 1;
		return 0;
	}
	bool operator<=(const List& L)
	{
		if (count < L.count)
			return 1;
		if (*this == L)
			return 1;
		return 0;
	}
	bool operator>(const List& L)
	{
		if (count > L.count)
			return 1;
		return 0;
	}
	bool operator<(const List& L)
	{
		if (count < L.count)
			return 1;
		return 0;
	}
	List operator-()
	{
		List Result;
		Element* temp = Head;
		while (temp != 0)
		{
			Result.AddHead(temp->data);
			temp = temp->Next;
		}
		return Result;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	List L;
	const int n = 10;
	int a[n] = { 0,1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < n; i++)
		if (i % 2 == 0)
			L.AddHead(a[i]);
		else
			L.AddTail(a[i]);
	cout << "List L: \n";
	L.Print();
	L.Insert();
	cout << "List L: \n";
	L.Print();
	L.Print(2);
	L.Print(8);
	List T;
	T = L;
	cout << "List T: \n";
	T.Print();
	cout << "List Sum: \n";
	List Sum = -L + T;
	Sum.Print();
	return 0;
}