#include <iostream>

/////////////////////////////////////////////////////////////
template<class T>
class Dodle_list
{
public:
	Dodle_list();
	~Dodle_list();
	//Добавление в список
	void append(T* value_F, int size);//Добавление массива
	void append(T value_F);//Добавление одиного элемента
	void add_index(T value_F, int index);//Добовление по индексу
	//Удаление из списка по индексу
	void pop(int index);
	//Замена элемента в списке по индексу
	void replac(T value_F, int index);
	//Информация о списке
	void print();
	int get_size() { return this->Size_D; }
	//Сортировка списка
	void sort_list();
	//Итератор для списка
	template<class T>
	struct List;
	template<class T>
	class iterator
	{
	public:
		//Dodle_list<int>::iterator<int> iter(dt);
		iterator(Dodle_list<T>& itt)
		{
			this->it = &itt;
			this->TMP = it->head;
			this->position_index = 0;
		}
		T& operator[](T  index) 
		{
			//Оптимизация для индексации в цикле
			if (index == this->position_index + 1)
			{
				this->TMP = this->TMP->pNext;
				this->position_index++;
			}
			else
			{
				this->TMP = it->head;
				this->position_index = 0;
				for (int i = 0; i < index; i++)
				{
					this->TMP = this->TMP->pNext;
					this->position_index++;
				}
			}
			return this->TMP->value;
		}
	private:
		int position_index;
		Dodle_list<T>* it;
		List<T>* TMP;
	};


private:
	template<class T>
	struct List
	{
		T value;
		List<T>* pNext;
		List<T>* pLatst;
		List(T& V, List<T>* N = nullptr, List<T>* L = nullptr)
		{
			this->value = V;
			this->pNext = N;
			this->pLatst = L;
		}
	};
	List<T>* head;
	List<T>* tail;
	int Size_D;
	void _append_end(T& value_F);
	void _append_front(T& value_F);
	void _pop_end();
	void _pop_front();
	//Сортировка списка с помощью бинарного дерева
	template<class T>
	class sort
	{
	public:
		//sort<char>::sort(args, size);
		sort(Dodle_list::List<T>* node, int size_F)
		{
			//Запомнить начальный элемент
			this->list = node;
			//Заполнение бинарного дерева
			this->head = new BunTer<T>(node->value);
			node = node->pNext;
			for (int i = 1; i < size_F; i++)
			{
				add(this->head, node->value);
				node = node->pNext;
			}
			//Изменить значения у входного списка
			setlist(this->head);
		}

	private:
		template<class T>
		struct BunTer
		{
			int quantity;
			T key;
			BunTer<T>* pLeft;
			BunTer<T>* pRight;
			BunTer(T K, int Q = 0, BunTer<T> * L = nullptr, BunTer<T> * R = nullptr)
			{
				this->key = K;
				this->quantity = Q;
				this->pLeft = L;
				this->pRight = R;
			}
		};
		BunTer<T>* head;
		Dodle_list::List<T>* list;
		//Добовление элемента
		void add(BunTer<T>* tmp, T args)
		{

			{
				while (true)
				{
					if (tmp->key == args)
					{
						tmp->quantity++;
						break;
					}

					else if (tmp->key < args)
					{
						if (tmp->pRight != nullptr)
						{
							tmp = tmp->pRight;
						}
						else
						{
							tmp->pRight = new BunTer<T>(args);
							break;
						}
					}

					else if (tmp->key > args)
					{
						if (tmp->pLeft != nullptr)
						{
							tmp = tmp->pLeft;
						}
						else
						{
							tmp->pLeft = new BunTer<T>(args);
							break;
						}
					}
				}
			}
		}
		//Изменения списка
		void setlist(BunTer<T>* node)
		{
			if (node != nullptr)
			{
				setlist(node->pLeft);
				if (node->quantity == 0)
				{
					this->list->value = node->key;
					this->list = this->list->pNext;
				}
				//Если повторяються
				else
				{
					for (int i = 0; i < node->quantity + 1; i++)
					{
						this->list->value = node->key;
						this->list = this->list->pNext;
					}
				}
				setlist(node->pRight);
				delete node;
			}
		}
	};
};
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//Удаление по выбранном индексу
template<class T>
void Dodle_list<T>::pop(int index)
{
	//В конце списка
	if (index == this->Size_D)
	{
		_pop_end();
	}

	//В начале списка
	else if (index == 0)
	{
		_pop_front();
	}

	//По указанному индексу
	else if (index < this->Size_D)
	{
		//Временная переменная которая будеи изменена
		List<T>* tmp_f = this->head;

		//Если ближе к концу
		if (index >= ceil((float)this->Size_D / 2))
		{

			tmp_f = this->tail;
			for (int i = this->Size_D; i > index; i--)
			{
				tmp_f = tmp_f->pLatst;
			}
			//Компинсация нулевого элемента
			tmp_f = tmp_f->pNext;
		}
		//Если ближе к началу
		else if (index <= ceil((float)this->Size_D / 2))
		{
			tmp_f = this->head;
			for (int i = 0; i < index; i++)
			{
				tmp_f = tmp_f->pNext;
			}
		}

		//Удаление и переопределение указателей
		List<T>* del_tmp = tmp_f;

		tmp_f = del_tmp->pLatst;
		tmp_f->pNext = del_tmp->pNext;

		tmp_f = tmp_f->pNext;
		tmp_f->pLatst = del_tmp->pLatst;

		delete del_tmp;
		this->Size_D--;

	}


	//За пределами списка 
	else if (index > this->Size_D)
	{
		throw false;
	}
}
//Диструктор класса
template<class T>
Dodle_list<T>::~Dodle_list()
{
	while (this->Size_D)
	{
		_pop_end();
	}
}
//Удаление в конце
template<class T>
void Dodle_list<T>::_pop_end()
{
	if (this->tail == this->head)
	{ 
		delete this->head;
		this->tail = this->head = nullptr;
	}
	else if (this->tail != this->head)
	{

		this->tail = this->tail->pLatst;
		delete this->tail->pNext;
		this->tail->pNext = nullptr;
	} 
	this->Size_D--;
}
//Удаление в начале
template<class T>
void Dodle_list<T>::_pop_front()
{
	if (this->head == this->tail)
	{
		delete this->head;
		this->tail = this->head = nullptr;
	}
	else if (this->head != this->tail)
	{
		this->head = this->head->pNext;
		delete this->head->pLatst;
		this->head->pLatst = nullptr;
	}
	this->Size_D--;
}
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//Сортировка списка с помощью бинарного дерева
template<class T>
void Dodle_list<T>::sort_list()
{
	sort<T>::sort(this->head, this->Size_D);
}
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//Замена переменной
template<class T>
void Dodle_list<T>::replac(T value_F, int index)
{
	pop(index);
	add_index(value_F, index-1);
}
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//Конструктор класса
template<class T>
Dodle_list<T>::Dodle_list()
{
	this->Size_D = 0;
	this->head = nullptr;
	this->tail = nullptr;
}
//Добовление элемента в конец массива
template<class T>
void Dodle_list<T>::append(T value_F)
{
	if (this->head == nullptr)
	{
		this->tail = this->head = new List<T>(value_F);

	}
	else
	{
		this->tail->pNext = new List<T>(value_F, nullptr, this->tail);
		this->tail = this->tail->pNext;
	}
	this->Size_D++;
}
//Добовление массива
template<class T>
void Dodle_list<T>::append(T* value_F, int size)
{
	for (int i = 0; i < size; i++)
	{
		_append_end(value_F[i]);
	}
}
//Доболвение элемента по индексу
template<class T>
void Dodle_list<T>::add_index(T value_F, int index)
{

	//В конце списка
	if (index == this->Size_D)
	{
		_append_end(value_F);
	}

	//В начале списка
	else if (index == 0)
	{
		_append_front(value_F);
	}

	//По указанному индексу
	else if (index < this->Size_D)
	{
		//Временная переменная которая будеи изменена
		List<T>* tmp_f = this->head;

		//Если ближе к концу
		if (index >= ceil((float)this->Size_D / 2))
		{
			tmp_f = this->tail;
			for (int i = this->Size_D; i > index; i--)
			{
				tmp_f = tmp_f->pLatst;
			}
			//Компинсация нулевого элемента
			tmp_f = tmp_f->pNext;
		}
		//Если ближе к началу
		else if (index <= ceil((float)this->Size_D / 2))
		{
			tmp_f = this->head;
			for (int i = 0; i < index; i++)
			{
				tmp_f = tmp_f->pNext;
			}
		}

		List<T>* next_tmp = new List<T>(value_F, tmp_f->pNext, tmp_f);
		tmp_f->pNext = next_tmp;
		tmp_f = next_tmp->pNext;
		tmp_f->pLatst = next_tmp;
		this->Size_D++;
	}

	//За пределами списка 
	else if (index > this->Size_D)
	{
		throw false;
	}
}
//Добовление в конец
template<class T>
void Dodle_list<T>::_append_end(T& value_F)
{
	if (this->head == nullptr)
	{
		this->head = this->tail = new List<T>(value_F);

	}
	else
	{
		this->tail->pNext = new List<T>(value_F, nullptr, this->tail);
		this->tail = this->tail->pNext;
	}
	this->Size_D++;
}
//Добовление в начало
template<class T>
void Dodle_list<T>::_append_front(T& value_F)
{

	if (this->head == nullptr)
	{
		this->head = this->tail = new List<T>(value_F);

	}
	else
	{
		this->head->pLatst = new List<T>(value_F, this->head, nullptr);
		this->head = this->head->pLatst;
	}
	this->Size_D++;

}
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
//Отображение списка
template<class T>
void Dodle_list<T>::print()
{
	List<T>* tmp_F = this->head;
	for (int i = 0; i < this->Size_D; i++)
	{
		std::cout << tmp_F->value << ", ";
		tmp_F = tmp_F->pNext;
	}
	std::cout << std::endl;
}
/////////////////////////////////////////////////////////////



int main()
{
	int b[] = { 10,31,42,35,4,65,6 };
	int size = sizeof(b) / sizeof(b[0]);
	Dodle_list<int> dt;
	dt.append(b,size);
	dt.print();
	dt.sort_list();
	dt.print();
}



