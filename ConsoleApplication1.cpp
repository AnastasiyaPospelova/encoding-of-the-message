#include <iostream>
#include <fstream>
#include <string>
#include<limits>
using namespace std;

int check_numbers() {
	int number;
	while (true) {
		cin >> number;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "The number is incorrect. Try again." << endl;
		}
		else break;
	}
	return number;
}

struct node {
	int data;
	char symbol;
	struct node* left;
	struct node* right;
	char t;
};

struct list {
	struct list* next;
	struct list* prev;

	node *tree;
};

struct list* delete_two_elements(list* lst) {
	if (lst->next != NULL) {
		lst = lst->next;
		lst->prev = NULL;
		if (lst->next != NULL) {
			lst = lst->next;
			lst->prev = NULL;
		}
	}
	return lst;
}

struct list* make_new_node(list* lst) {
	list* new_node;
	new_node = (struct list*)malloc(sizeof(struct list));

	node* i;
	i = (struct node*)malloc(sizeof(struct node));
	i->data = lst->tree->data;
	i->symbol = lst->tree->symbol;
	i->left = lst->tree->left;
	i->right = lst->tree->right;
	i->t = '0';
	new_node->tree->left = i;

	lst = lst->next;
	node* j;
	j = (struct node*)malloc(sizeof(struct node));
	j->data = lst->tree->data;
	j->symbol = lst->tree->symbol;
	j->left = lst->tree->left;
	j->right = lst->tree->right;
	j->t = '1';
	new_node->tree->right = j;

	new_node->tree->data = i->data + j->data;
	new_node->tree->symbol = '~';

	return new_node;
}

struct list* paste_node(list* lst, list* new_node) {
	bool r = true;
	while (r) {
		if (new_node->tree->data <= lst->tree->data) {
			if (lst->prev == NULL) {
				lst->prev = new_node;
				new_node->next = lst;
				new_node->prev = NULL;
				r = false;
			}
			else {
				list* p;
				p = lst->prev;
				new_node->next = lst;
				lst->prev = new_node;
				p->next = new_node;
				new_node->prev = p;
				r = false;
			}
		}
		else if (lst->next != NULL) {
			lst = lst->next;
		}
		else {
			lst->next = new_node;
			new_node->prev = lst;
			new_node->next = NULL;
			r = false;
		}
	}
	return new_node;
}

struct list* start(list* lst) {
	while (lst->prev != NULL) {
		lst = lst->prev;
	}
	return lst;
}

struct list* init(int data, char symbol) {
	struct list* lst;
	lst = (struct list*)malloc(sizeof(struct list));
	lst->next = NULL;
	lst->prev = NULL;

	lst->tree->data = data;
	lst->tree->symbol = symbol;
	lst->tree->left = NULL;
	lst->tree->right = NULL;
	return(lst);
};

struct list* addelem(list* lst, int data, char symbol) {
	struct list* tem, * p;
	tem = (struct list*)malloc(sizeof(struct list));
	p = lst->next;
	lst->next = tem;
	tem->next = p;
	tem->prev = lst;
	if (p != NULL) p->prev = tem;

	tem->tree->data = data;
	tem->tree->symbol = symbol;
	tem->tree->left = NULL;
	tem->tree->right = NULL;
	return(tem);
};

struct dictionary {
	char letter;
	string code;
	struct dictionary* next;
	struct dictionary* prev;
};

struct dictionary* init_d(char letter, string code) {
	struct dictionary* dict;
	dict = (struct dictionary*)malloc(sizeof(struct dictionary));
	dict->next = NULL;
	dict->prev = NULL;
	dict->letter = letter;

	// Нам в переменную code тупо передаётся 0

	dict->code = code;

	cout << "in struct" << endl;

	return(dict);
};

struct dictionary* addelem_d(dictionary* dict, char letter, string code) {
	struct dictionary* tem;
	tem = (struct dictionary*)malloc(sizeof(struct dictionary));
	dict->next = tem;
	tem->prev = dict;
	tem->next = NULL;

	tem->code = code;
	tem->letter = letter;
	return(tem);
};

struct dictionary* start_d(dictionary* dict) {
	while (dict->prev != NULL) dict = dict->prev;
	return dict;
};

void listprint(list* lst) {
	do {
		cout << lst->tree->data << "  " << lst->tree->symbol << endl;
		lst = lst->next;
	} while (lst != NULL);
}

string get_data(string filename) {
	string text;
	fstream input;
	input.open(filename, ios::in);
	while (!input.eof()) {
		string temp;
		std::getline(input, temp);
		if (!input.eof()) {
			temp += '\n';
		}
		text += temp;
	}
	input.close();
	return text;
}

string alphabet(string text) {
	string abc;
	bool exit_flag = 0;
	abc.push_back(text[0]);
	for (int i = 1; i < text.size(); i++) {
		exit_flag = 0;
		for (int j = 0; j < abc.size(); j++) {
			if (abc[j] == text[i]) {
				exit_flag = 1;
				break;
			}
		}
		if (exit_flag == 1) {
			continue;
		}
		else {
			abc.push_back(text[i]);
			continue;
		}
	}
	return abc;
}

void get_frequency(string text, int* frequencies, string abc) {
	int len = abc.size();
	for (int i = 0; i < len; i++) {
		frequencies[i] = 0;
	}
	for (int j = 0; j < len; j++) {
		for (int i = 0; i < text.size(); i++) {
			if (abc[j] == text[i]) {
				frequencies[j]++;
			}
		}
	}
}

void print_abc(string text, string abc, int* frequencies) {
	cout << endl;
	cout << text << endl;
	cout << endl;
	cout << "Alphabet: " << abc << endl;
	cout << endl;
	cout << "Size of alphabet: " << abc.size() << endl;
	cout << endl;
	cout << "Frequencies: " << endl;
	for (int i = 0; i < abc.size(); i++) {
		cout << abc[i] << " - " << frequencies[i] << endl;
	}
	cout << endl;
}

void make_nodes(int* frequencies, const string abc, list* lst, char g) {
	int k = 0, counter = 1;
	char already_in_list[sizeof(abc)];
	bool is_in;
	already_in_list[0] = lst->tree->symbol;
	while (already_in_list[abc.size() - 1] != g) {
		for (int i = 0; i < abc.size(); i++) {
			is_in = true;
			for (int j = 0; j < abc.size(); j++) {
				if (abc[i] == already_in_list[j]) continue;
				else is_in = false;
			}
			if ((frequencies[i] == counter) && (is_in == false)) {
				addelem(lst, frequencies[i], abc[i]);
				lst = lst->next;
				already_in_list[k] = abc[i];
				k++;
			}
		}
		counter++;
	}
}

dictionary* coding(node* tree, string s, dictionary* dict) {
	if (tree != NULL) {
		s += tree->t;
		dict = coding(tree->left, s, dict);
		dict = coding(tree->right, s, dict);
		if (tree->symbol != '~') {
			string new_s;
			for (int i = 1; i < s.length(); i++) {
				new_s += s[i];
			}
			dict = addelem_d(dict, tree->symbol, new_s);
			s = "";
			//			cout << dict->letter << " " << dict->code << endl;
			return dict;
		}
	}
	return dict;
}

int find_size(dictionary* dict) {
	int counter = 1;
	while (dict->next != NULL) {
		counter++;
		dict = dict->next;
	}
	return counter;
}

string make_code(dictionary* dict, string text) {
	string code;
	int i = 0;
	int size_dict = find_size(dict);
	while (text[i] != '\0') {
		for (int j = 0; j < size_dict; j++) {
			if (text[i] == dict->letter) {
				code += dict->code;
				break;
			}
			dict = dict->next;
		}
		dict = start_d(dict);
		i++;
	}
	return code;
}

void dict_print(dictionary* dict) {
	do {
		cout << dict->letter << "  " << dict->code << endl;
		dict = dict->next;
	} while (dict != NULL);
}

void encode_text(string code) {
	string filename_code;
	cout << "Enter file name to print the encode text: " << endl;
	cin >> filename_code;
	std::ofstream out;  // поток для записи
	out.open(filename_code, ios::out); // окрываем файл для записи
	if (out.is_open()) {
		out << code << std::endl;
	}
	cout << "The encoded text is written to a file." << endl;
}

void encode_table(dictionary* dict) {
	string filename_code;
	cout << "Enter file name to print the table: " << endl;
	cin >> filename_code;
	std::ofstream out;  // поток для записи
	out.open(filename_code, ios::out); // окрываем файл для записи
	if (out.is_open()) {
		while (dict != NULL) {
			out << dict->letter << "|" << dict->code << "\\n" << std::endl;
			dict = dict->next;
		}
	}
	cout << "The encoding table is written to a file." << endl;
}

int main() {
	cout << "Enter file name containing the text: ";
	string filename, text;
	cin >> filename;
	text = get_data(filename); // Считываение текста из файла
	const string abc = alphabet(text);
	int* frequencies = new int[abc.size()];
	get_frequency(text, frequencies, abc); // Число вхождений букв в текст
	cout << endl;
	cout << "-------------" << endl;
	cout << "TEXT ANALYSIS" << endl;
	cout << "-------------" << endl;
	print_abc(text, abc, frequencies);

	int mini = 9999;
	int maxi = 0;
	int j;
	char g;
	for (size_t h = 0; h < abc.size(); h++) { // Поиск самой редкой и самой частой бувкы
		
		if (mini > frequencies[h]) {
			mini = frequencies[h];
			j = h;
		}
		if (maxi < frequencies[h]) {
			maxi = frequencies[h];
			g = abc[h];
		}
	}
	list* head, * cur;
	head = init(mini, abc[j]);
	cur = head;
	make_nodes(frequencies, abc, cur, g); // Создание списка корней
	head = head->next;
	head->prev = NULL;
	cur = head;
	list* new_node;
	while (true) { // Создание дерева
		cur = head;
		if (cur->next->next == NULL) {
			new_node = make_new_node(cur);
			break;
		}
		new_node = make_new_node(cur);
		head = delete_two_elements(head);
		cur = head;
		new_node = paste_node(cur, new_node);
		head = start(head);
	}

	cur = head;
	head = new_node;
	head->prev = NULL;
	string s;
	node* tree_d = head->tree;
	while (tree_d->left != NULL) { // Поиск самого левого эл-та дерева для инициализации
		tree_d = tree_d->left;
		s += '0';
	}
	
	dictionary* head_d = init_d(tree_d->symbol, s);

	cout << "here!" << endl;

	s = "";

	cout << "here!" << endl;

	dictionary* dict = head_d;

	cout << "here!" << endl;

	dict = coding(head->tree, s, dict); // Функция заполнения словаря, содержащего буквы и соответствующие им кодовые слова
	
	//D:\ci\ConsoleApplication1\cba.txt
	
	cout << "here!" << endl;

	dict = start_d(dict);
	dict = dict->next;
	dict->prev = NULL;

	cout << "here!" << endl;

	cout << endl;
	cout << "Code table:" << endl;
	cout << endl;
	dict_print(dict);

	cout << "here!" << endl;

	s = make_code(dict, text); // Кодировка текста
	cout << endl;
	encode_text(s); // Запись закодированного текста в файл
	cout << endl;
	encode_table(dict); // Запись таблицы кодировки в файл


	return 0;
}
