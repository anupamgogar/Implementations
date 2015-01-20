#include<iostream>
using namespace std;

//Reference Count
class RC{
	int count;
public:
	RC(){
		count = 0;
	}
	void increment(){
		++count;
	}
	int decrement(){
		return --count;
	}
	int get() const{
		return count;
	}
};
template<typename T>
class SmartPointer{
private:
	T* m_pointer;
	RC* m_count;
public:
	SmartPointer(T* pointer){
		m_pointer = pointer;
		m_count = new RC();
		m_count->increment();
		cout<<"Smart Pointer Created. Reference Count is now: "<<m_count->get()<<endl;
	}
	//copy constructor
	SmartPointer(const SmartPointer<T>& SP2){
		m_pointer = SP2.m_pointer;
		m_count = SP2.m_count;
		m_count->increment();
		cout<<"Copy constructed Smart Pointer. Reference Count is now: "<<m_count->get()<<endl;
	}
	//assignment operator
	SmartPointer<T>& operator=(const SmartPointer<T>& SP2){
		if (SP2 == *this){
			return *this;
		}
		destroy();
		m_pointer = SP2.m_pointer;
		m_count = SP2.m_count;
		m_count->increment();
		cout<<"Copy constructed Smart Pointer. Reference Count is now: "<<m_count->get()<<endl;
	}
	void destroy(){
		if (m_count->decrement() == 0){
			delete m_pointer;
			delete m_count;
			cout<<"Deleting the object. Good bye.\n";
		}
		cout<<"Destroying this Smart Pointer but not deleting. Reference Count is now: "<<m_count->get()<<endl;
	}
	~SmartPointer(){
		destroy();
	}
	T& operator*(){
		return *m_pointer;
	}
	T* operator->(){
		return m_pointer;
	}
};

int main(){
	SmartPointer<int> sp1(new int);
	*sp1 = 5;
	//Limiting the scope for SP2 and SP3.
	{
		SmartPointer<int> sp2(sp1);
		cout<<"SP2's value is: "<<*sp2<<endl;
	}
	{
		SmartPointer<int> sp3 = sp1;
		cout<<"SP3's value is: "<<*sp3<<endl;
	}

	int x;
	cin>>x;
}