#include <iostream>
using namespace std;

template<class Tkey, class Tvalue>
class BinaryTree
{
public:
	BinaryTree() 
	{
		this->Size_main = 0;
		this->head = nullptr;
	};
	~BinaryTree() {clear();}

	//--Добовление элементов.
	void add(Tkey const key_F, Tvalue const value_F);
	//--Замена.
	void value_replacement(Tkey const key_F, Tvalue const value_F);
	//--Удаление.
	void clear();
	Tvalue pop(Tkey const key_F);
	//--Информация.
	Tvalue get(Tkey const key_F);
	void items();
	void keys();
	Tkey max();
	Tkey min();
	//--Оптимизация дерева.
	void sort_opt();

	
private:
	template<class Tkey, class Tvalue>
	struct Node
	{
		//Ключ
		Tkey key_node;
		//Указатель на значение.
		Tvalue* pValue_pt;
		//Указатель Левый 'Node'.
		Node* pLeft_pt;
		//Указатель Правый 'Node'.
		Node* pRight_pt;
		Node(Tkey key_node, Tvalue value_node, Node* pLeft = nullptr, Node* pRight = nullptr)
		{
			this->key_node = key_node;
			this->pValue_pt = new Tvalue(value_node);
			this->pLeft_pt = pLeft;
			this->pRight_pt = pRight;
		}
	};
	int Size_main;
	Node<Tkey, Tvalue>* head;

	//--Оптимизация для функций класса.
	Node<Tkey, Tvalue>* add_node(Tkey const key_F, Tvalue const value_F, Node<Tkey, Tvalue>* node_F);
	void value_replacement_node(Tkey const key_F, Tvalue const value_F, Node<Tkey, Tvalue>* node_F);
	void replace_value_node(Node<Tkey, Tvalue>* node_F, Tvalue const value_F);
	void items_node(Node<Tkey, Tvalue>* node_F);
	void keys_node(Node<Tkey, Tvalue>* node_F);
	void del_node(Node<Tkey, Tvalue>* node_F);
	void get_sort_opt(bool rounding, Tkey const key_F, Node<Tkey, Tvalue>** args_last, int& len);
	void sort_opt_get(Node<Tkey, Tvalue>* node_F, Node<Tkey, Tvalue>** args_last,int& len);
};

//------------------- Удаление -------------------
//Удаляет ключ и возвращает его значение. 
template<class Tkey, class Tvalue>
Tvalue BinaryTree<Tkey, Tvalue>::pop(Tkey const key_F)
{
	Node<Tkey, Tvalue>* TMP = this->head;
	Node<Tkey, Tvalue>* DEL = TMP;
	Tvalue save_vaul = Tvalue();

	//Если это ЦЕНТЕР
	if (key_F == this->head->key_node)
	{
		//Если  с ЛЕВО не пусто
		if (DEL->pLeft_pt != nullptr)
		{
			//Если с ПРАВО не пусто
			if (DEL->pRight_pt != nullptr)
			{

				this->head = DEL->pRight_pt;
				TMP = this->head->pLeft_pt;
				//Спуск до самого меньшего значения слево
				while (TMP->pLeft_pt != nullptr)
				{
					TMP = TMP->pLeft_pt;
				}
				TMP->pLeft_pt = DEL->pLeft_pt;

			}
			//Если с ПРАВО пусто
			else if (DEL->pRight_pt == nullptr)
			{
				this->head = this->head->pLeft_pt;
			}
		}
		//Если с ЛЕВО пусто
		else if (DEL->pLeft_pt == nullptr)
		{
			this->head = this->head->pRight_pt;
		}
		save_vaul = *DEL->pValue_pt;
		delete DEL->pValue_pt;
		delete DEL;
		this->Size_main--;
		return save_vaul;
	}
	
	while (true)
	{
		//Удаление и переставление элементов дерева
		//Если с ЛЕВА
		if (TMP->pLeft_pt != nullptr && key_F == TMP->pLeft_pt->key_node)
		{
			/*
			* Проверка на nullptr чтобы можно было считать ключ 
			* значение листьев дерева
			*/
			DEL = TMP->pLeft_pt;
			//Если  с ЛЕВО не пусто
			if (DEL->pLeft_pt != nullptr)
			{
				//Если с ПРАВО не пусто
				if (DEL->pRight_pt != nullptr)
				{

					TMP->pLeft_pt = DEL->pRight_pt;
					TMP = TMP->pLeft_pt;
					//Спуск до самого меньшего значения слево
					while (TMP->pLeft_pt != nullptr)
					{
						TMP = TMP->pLeft_pt;
					}
					TMP->pLeft_pt = DEL->pLeft_pt;
				}
				//Если с ПРАВО пусто
				else if (DEL->pRight_pt == nullptr)
				{
					TMP->pLeft_pt = DEL->pLeft_pt;
				}
			}
			//Если с ЛЕВО пусто
			else if (DEL->pLeft_pt == nullptr)
			{
				TMP->pLeft_pt = DEL->pRight_pt;
			}
			save_vaul = *DEL->pValue_pt;
			delete DEL->pValue_pt;
			delete DEL;
			this->Size_main--;
			return save_vaul;
		}
		//Если с ПРАВА
		else if (TMP->pRight_pt != nullptr && key_F == TMP->pRight_pt->key_node)
		{
			DEL = TMP->pRight_pt;
			//Если  с ЛЕВО не пусто
			if (DEL->pLeft_pt != nullptr)
			{
				//Если с ПРАВО не пусто
				if (DEL->pRight_pt != nullptr)
				{

					TMP->pRight_pt = DEL->pRight_pt;
					TMP = TMP->pRight_pt;
					//Спуск до самого меньшего значения слево
					while (TMP->pLeft_pt != nullptr)
					{
						TMP = TMP->pLeft_pt;
					}
					TMP->pLeft_pt = DEL->pLeft_pt;
				}
				//Если с ПРАВО пусто
				else if (DEL->pRight_pt == nullptr)
				{
					TMP->pRight_pt = DEL->pLeft_pt;
				}
			}
			//Если с ЛЕВО пусто
			else if (DEL->pLeft_pt == nullptr)
			{
				TMP->pRight_pt = DEL->pRight_pt;
			}
			save_vaul = *DEL->pValue_pt;
			delete DEL->pValue_pt;
			delete DEL;
			this->Size_main--;
			return save_vaul;
		}


		//Передвижение по дереву
		//Если с ЛЕВА
		if (key_F < TMP->key_node)
		{
			//Если есть элементы слева то идем дальше
			if (TMP->pLeft_pt != nullptr)
			{
				TMP = TMP->pLeft_pt;
			}
			//Если это последний то не найденно
			else if (TMP->pLeft_pt == nullptr)
			{
				throw exception("Not key");
				return save_vaul;
			}
		}
		//Если с ПРАВА
		else if (key_F > TMP->key_node)
		{
			//Если есть элементы справо то идем дальше
			if (TMP->pRight_pt != nullptr)
			{
				TMP = TMP->pRight_pt;
			}
			//Если это последний то не найденно
			else if (TMP->pRight_pt == nullptr)
			{
				throw exception("Not key");
				return save_vaul;
			}
		}
	}
	
}
//Отчистка массива.
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::clear()
{
	del_node(this->head);
	this->head = nullptr;
}
//Удаление всего Рекурсиваня функция для clear().
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::del_node(Node<Tkey, Tvalue>* node_F)
{
	if (node_F != nullptr)
	{
		del_node(node_F->pLeft_pt);
		del_node(node_F->pRight_pt);
		delete node_F->pValue_pt;
		node_F->pValue_pt = nullptr;
		delete node_F;
		this->Size_main--;
	}
}
//------------------------------------------------


//------------ Добовление элементов --------------
//Добовление элемента.
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::add(Tkey const key_F, Tvalue const value_F)
{
	if (this->head == nullptr)
	{
		this->head = new Node<Tkey, Tvalue>(key_F, value_F);
		this->Size_main++;
	}
	else
	{
		add_node(key_F, value_F, this->head);
	}
}
//Добовление элемента Рекурсиваня функция для add().
template<class Tkey, class Tvalue>
BinaryTree<Tkey, Tvalue>::Node<Tkey, Tvalue>* BinaryTree<Tkey, Tvalue>::add_node(Tkey const key_F, Tvalue const value_F, Node<Tkey, Tvalue>* node_F)
{
	//Оптимизация для функции 'add'
	if (node_F == nullptr)
	{
		node_F = new Node<Tkey, Tvalue>(key_F, value_F);
		this->Size_main++;
	}
	//Меньше
	else if (key_F < node_F->key_node)
	{
		node_F->pLeft_pt = add_node(key_F, value_F, node_F->pLeft_pt);
	}
	//Больше
	else if (key_F > node_F->key_node)
	{
		node_F->pRight_pt = add_node(key_F, value_F, node_F->pRight_pt);
	}
	//Если уже есть
	else if (key_F == node_F->key_node)
	{
		if (value_F != *node_F->pValue_pt)
		{
			//Замена значения
			replace_value_node(node_F, value_F);
		}
	}
	/*
	Возвращаем созданный элемент чтобы привязать его
	к конкретной стороне дерева
	*/
	return(node_F);
}
//------------------------------------------------


//------------------ Замена -----------------------
//Замена значения по ключу.
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::value_replacement(Tkey const key_F, Tvalue const value_F)
{
	//Стартуем с головы
	value_replacement_node(key_F, value_F,this->head);
}
//Замена значения Рекурсиваня функция value_replacement().
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::value_replacement_node(Tkey const key_F, Tvalue const value_F, Node<Tkey, Tvalue>* node_F)
{
	//Оптимизация для функции 'value_replacement'
	//Меньше
	if (key_F < node_F->key_node)
	{
		value_replacement_node(key_F, value_F, node_F->pLeft_pt);
	}
	//Больше
	else if (key_F > node_F->key_node)
	{
		value_replacement_node(key_F, value_F, node_F->pRight_pt);
	}
	//Если уже есть заменяем
	else if (key_F == node_F->key_node)
	{
		//Замена значения
		replace_value_node(node_F, value_F);
	}
}
//Замена значение у ключа по -> 'Node'.
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::replace_value_node(Node<Tkey, Tvalue>* node_F, Tvalue const value_F)
{
	//Оптимизация для функции 'add_node','value_replacement_node'
	delete node_F->pValue_pt;
	node_F->pValue_pt = nullptr;
	node_F->pValue_pt = new Tvalue(value_F);
}
//------------------------------------------------


//---------------- Оптимизация -------------------
//Отображение Рекурсиваня функция для items().
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::items_node(Node<Tkey, Tvalue>* node_F)
{
	if (node_F != nullptr)
	{
		items_node(node_F->pLeft_pt);
		cout << node_F->key_node << ":" << *node_F->pValue_pt << ", ";
		items_node(node_F->pRight_pt);
	}
}
//Отображение Рекурсиваня функция для keys().
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::keys_node(Node<Tkey, Tvalue>* node_F)
{
	//5,4,7,3,9,6,8,1
	if (node_F != nullptr)
	{
		/*
		Сортированный вид по возростанию
		keys_node(node_F->pLeft_pt);
		cout << node_F->key_node << ", ";
		keys_node(node_F->pRight_pt);
		*/
		
		/*Удобный вывод структуры дерва*/
		cout << node_F->key_node << ", ";
		keys_node(node_F->pLeft_pt);
		keys_node(node_F->pRight_pt);

		/*
		keys_node(node_F->pLeft_pt);
		keys_node(node_F->pRight_pt);
		cout << node_F->key_node << ", ";
		*/
	}
}
//------------------------------------------------


//---------------  Сортировка ----------------------------
//Отимальное размещение элементов
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::sort_opt()
{
	//Двумерный массив с оптимальными значениями дерева
	Node<Tkey, Tvalue>** New_dict = new Node<Tkey, Tvalue>*[this->Size_main];
	//Длинна у нового списка с оптимальными значениями дерева
	int len = 0;


	//Максимальное значение у дерева
	Tkey max_f = max();
	Tkey min_f = min();

	//Ставим первое опорное значение
	float last_max = (float)max_f / 2;
	int mid = ceil(last_max);//К большему
	get_sort_opt(false,mid, New_dict, len);
	last_max = mid;

	//Далее сторим в лево и в право
	int right = mid;
	int left;

	//Строит опорные узлы
	while (true)
	{
		//Опрделяем середину
		last_max = last_max / 2;//5.0
		//Левый узел К меньшему
		left = floor(last_max);
		//Правый узел К большему
		right = right + ceil(last_max);

		//Если дошел или вышел за границы то выходим из цикла
		if (left <= min_f || right >= max_f)
		{
			break;
		}
		/*
		true - Округление к меньшему
		false - Округление к большему
		*/
		//ЛЕВО Записываем самое близкое число в массив
		get_sort_opt(true,left, New_dict, len);//5
		//ПРАВО Записываем самое близкое число в массив
		get_sort_opt(false,right, New_dict, len);//15
		//Переход на новую середину
		last_max = left;
	}

	//Дописывает все остольные элементы в массив
	sort_opt_get(this->head, New_dict, len);
	//Отчищаем нашь класс от всех значений чтобы записать новые
	clear();
	//Записывает в класс новые элементы в правильной последовательности
	for (int i = 0; i < len; i++)
	{
		add(New_dict[i]->key_node, *New_dict[i]->pValue_pt);

		delete [] New_dict[i];
		New_dict[i] = nullptr;
	}
	//Удаляем двумерный динамический массив
	delete [] New_dict;
	New_dict = nullptr;
}
//Ищет указзаный ключ и записывает его в 'New_dict'
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::get_sort_opt(bool rounding, Tkey const key_F, Node<Tkey, Tvalue>** args_last, int& len)
{
	//Работает только с ключами типа int
	/*
	true - к меньшему
	false - к большему
	*/
	Node<Tkey, Tvalue>* TMP_root_F = this->head;
	//Переменная которая будет хранить прошлый элемент.
	Node<Tkey, Tvalue>* Last = TMP_root_F;

	//Чтобы этого элемента уже небыло в спике
	bool res = false;

	//Если элемент найден то цикл прекращается.
	while (key_F != TMP_root_F->key_node)
	{
		//Если меньше в ЛЕВА.
		if (key_F < TMP_root_F->key_node)
		{
			//Если есть элементы слева то идем дальше
			if (TMP_root_F->pLeft_pt != nullptr)
			{
				Last = TMP_root_F;
				TMP_root_F = TMP_root_F->pLeft_pt;
			}
			//Если это последний то ищем ближайший элемент
			else if (TMP_root_F->pLeft_pt == nullptr)
			{
				//Окгругление к меньшему
				if (rounding == true)
				{
					TMP_root_F = Last;
				}
				//Окгругление к большему
				else if (rounding == false)
				{
					TMP_root_F = TMP_root_F;
				}
				//Чтобы этого элемента уже небыло в спике
				for (int i = 0; i < len; i++)
				{
					if (TMP_root_F->key_node == args_last[i]->key_node)
					{
						res = true;
						break;
					}
				}
				break;
			}
		}

		//Если больше в ПРАВА.
		else if (key_F > TMP_root_F->key_node)
		{
			//Если есть элементы справо то идем дальше
			if (TMP_root_F->pRight_pt != nullptr)
			{
				Last = TMP_root_F;
				TMP_root_F = TMP_root_F->pRight_pt;
			}
			//Если это последний то ищем ближайший элемент
			else if (TMP_root_F->pRight_pt == nullptr)
			{
				//Окгругление к меньшему
				if (rounding == true)
				{
					TMP_root_F = Last;
				}
				//Окгругление к большему
				else if (rounding == false)
				{
					TMP_root_F = TMP_root_F;
				}
				//Чтобы этого элемента уже небыло в спике
				for (int i = 0; i < len; i++)
				{
					if (TMP_root_F->key_node == args_last[i]->key_node)
					{
						res = true;
						break;
					}
				}
				break;
			}
		}
	}
	//Если этого элемента небыло то
	if (res == false)
	{
		//Создаем новый 'Node' с данными найденными в цикле.
		args_last[len++] = new Node<Tkey, Tvalue>(TMP_root_F->key_node, *TMP_root_F->pValue_pt);
	}
}
//Дописывает все остольные элементы в 'New_dict'
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::sort_opt_get(Node<Tkey, Tvalue>* node_F, Node<Tkey, Tvalue>** args_last, int& len)
{
	if (node_F != nullptr)
	{
		sort_opt_get(node_F->pLeft_pt, args_last, len);
		//Чтобы этого элемента уже небыло в спике
		bool res = false;
		for (int i = 0; i < len; i++)
		{
			if (node_F->key_node == args_last[i]->key_node)
			{
				res = true;
				break;
			}
		}
		//Если нету.
		if (res == false)
		{
			args_last[len++] = new Node<Tkey, Tvalue>(node_F->key_node, *node_F->pValue_pt);
		}
		sort_opt_get(node_F->pRight_pt, args_last, len);
	}
}
//------------------------------------------------


//----------------- Информация -------------------------------
//Возвращает значение ключа.
template<class Tkey, class Tvalue>
Tvalue BinaryTree<Tkey, Tvalue>::get(Tkey const key_F)
{
	Node<Tkey, Tvalue>* node_F = this->head;
	while (key_F != node_F->key_node)
	{
		//Меньше
		if (key_F < node_F->key_node)
		{
			node_F = node_F->pLeft_pt;
		}
		//Больше
		else if (key_F > node_F->key_node)
		{
			 node_F = node_F->pRight_pt;
		}
		//Если ключа нет
		if (node_F == nullptr)
		{
			throw exception("Not key");
		}
	}
	return *node_F->pValue_pt;
}
//Возвращает пары (ключ, значение).
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::items()
{
	//Node<Tkey, Tvalue>* tmp = this->head;
	cout << "items = {";
	items_node(this->head);
	cout << "}" << endl;
}
//Возвращает ключи в словаре.
template<class Tkey, class Tvalue>
void BinaryTree<Tkey, Tvalue>::keys()
{
	//Node<Tkey, Tvalue>* tmp = this->head;
	cout << "keys = {";
	keys_node(this->head);
	cout << "}"<<endl;
}
//max значение в дереве.
template<class Tkey, class Tvalue>
Tkey BinaryTree<Tkey, Tvalue>::max()
{
	Node<Tkey, Tvalue>* tmp = this->head;
	while (tmp->pRight_pt != nullptr)
	{
		tmp = tmp->pRight_pt;
	}
	return tmp->key_node;
}
//min значение в дереве.
template<class Tkey, class Tvalue>
Tkey BinaryTree<Tkey, Tvalue>::min()
{
	Node<Tkey, Tvalue>* tmp = this->head;
	while (tmp->pLeft_pt != nullptr)
	{
		tmp = tmp->pLeft_pt;
	}
	return tmp->key_node;
}
//------------------------------------------------

template<class Tkey, class Tvalue>
void Test(BinaryTree<Tkey, Tvalue>& dict)
{
	setlocale(LC_ALL, ".1251");
	int size = 5;
	int* args = new int[size];
	for (int i = 0; i < size; i++)
	{
		cout << "Введите число " << i << " : ";
		cin >> args[i];
	}

	for (int i = 0; i < size; i++)
	{
		dict.add(args[i], 0);
	}
	dict.items();
	dict.sort_opt();
	dict.keys();
}



int main()
{
	setlocale(LC_ALL, ".1251");
	BinaryTree<int, int> dict;



	Test(dict);
	


	return 0;
}

