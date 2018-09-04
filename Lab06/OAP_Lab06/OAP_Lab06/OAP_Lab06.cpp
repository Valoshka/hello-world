// OAP_Lab06.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int STREET_SIZE = 40;
const unsigned int CITY_SIZE = 20;
struct Address
{
	char name[NAME_SIZE];
	char street[STREET_SIZE];
	char city[CITY_SIZE];
	Address *next;
	Address *prev;

};
//-----------------------------------------------------------
int menu(void)
{
	char s[80];
	int c;
	cout << endl;
	cout << "1. ���� �����" << endl;
	cout << "2. �������� �����" << endl;
	cout << "3. ����� �� �����" << endl;
	cout << "4. �����" << endl;
	cout << "5. ��������� � ����" << endl;
	cout << "6. ��������� �� �����" << endl;
	cout << "7. ����� �� �����" << endl; 
	cout << "8. �����" << endl; cout << endl;
	do
	{
		cout << "��� �����: ";
		cin.sync();
		gets_s(s);
		cout << endl;
		c = atoi(s);
	} while (c < 0 || c > 8);
	return c;

}
//-----------------------------------------------------------
void create(Address *i, Address **phead, Address **plast)
{
	Address *old = NULL, *p = *phead;
	if (*plast == NULL)
	{
		i->next = NULL;
		i->prev = NULL;
		*plast = i;
		*phead = i;
		return;
	}
	while (p)
	{
		if (strcmp(p->name, i->name) < 0)
		{
			old = p;
			p = p->next;
		}
		else
		{
			if (p->prev)
			{
				p->prev->next = i;
				i->next = p;
				i->prev = p->prev;
				p->prev = i;
				return;
			}
			i->next = p;
			i->prev = NULL;
			p->prev = i;
			*phead = i;
			return;
		}
	}
	old->next = i;
	i->next = NULL;
	i->prev = old;
	*plast = i;
}

//-----------------------------------------------------------
Address* setElement()      // ���� ���������
{
	Address* temp = new  Address();
	if (!temp)
	{
		cerr << "������ ��������� ������ ������";
		return NULL;
	}
	cout << "������� ���: ";
	cin.getline(temp->name, NAME_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	cout << "������� �����: ";
	cin.getline(temp->street, STREET_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	cout << "������� �����: ";
	cin.getline(temp->city, CITY_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}
//-----------------------------------------------------------
void outputList(Address **phead, Address **plast)      //����� ������ �� �����
{
	Address *t = *phead;
	while (t)
	{
		cout << t->name << ' ' << t->street
			<< ' ' << t->city << endl;
		t = t->next;
	}
	cout << "" << endl;
}
//-----------------------------------------------------------
void find(char name[NAME_SIZE], Address **phead)    // ����� ����� � ������
{
	Address *t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name))
			break;
		t = t->next;
	}
	if (!t)
		cerr << "��� �� �������" << endl;
	else
		cout << t->name << ' ' << t->street << ' ' << t->city << endl;
}
//-----------------------------------------------------------
void delet(char name[NAME_SIZE], Address **phead, Address **plast)  // �������� ���-�� �� ������
{
	struct Address *t = *phead;

	while (t)
	{
		if (!strcmp(name, t->name))
			break;
		t = t->next;
	}
	if (t)
	{
		if (*phead == t)
		{
			*phead = t->next;
			if (*phead)
				(*phead)->prev = NULL;
			else
				*plast = NULL;
		}
		else
		{
			t->prev->next = t->next;
			if (t != *plast)
				t->next->prev = t->prev;
			else
				*plast = t->prev;
		} delete t;
	}
}
//-----------------------------------------------------------
void writeToFile(Address **phead)       //������ � ����
{
	struct Address *t = *phead;
	FILE *fp;
	errno_t err = fopen_s(&fp, "mlist", "wb");
	if (err)
	{
		cerr << "���� �� �����������" << endl;
		exit(1);
	}
	cout << "���������� � ����" << endl;

	while (t)
	{
		fwrite(t, sizeof(struct Address), 1, fp);
		t = t->next;
	}
	fclose(fp);
}
//-----------------------------------------------------------
void readFromFile(Address **phead, Address **plast)          //���������� �� �����
{
	struct Address *t;
	FILE *fp;
	errno_t err = fopen_s(&fp, "mlist", "rb");
	if (err)
	{
		cerr << "���� �� �����������" << endl;
		exit(1);
	}
	while (*phead)
	{
		*plast = (*phead)->next;
		delete *phead;
		*phead = *plast;
	}
	*phead = *plast = NULL;
	cout << "�������� �� �����" << endl;
	while (!feof(fp))
	{
		t = new Address();
		if (!t)
		{
			cerr << "������ ��������� ������ ������" << endl;
			return;
		}
		if (1 != fread(t, sizeof(struct Address), 1, fp))
			break;
		create(t, phead, plast);
	}
	fclose(fp);
}
//-----------------------------------------------------------

void search(char name[NAME_SIZE], Address **phead, int k)
{
	switch (k)
	{
	case 1:
	{
		Address *t = *phead;
		while (t)
		{
			if (!strcmp(name, t->name))
				break;
			t = t->next;
		}
		if (!t)
			cerr << "��� �� �������" << endl;
		else
			cout << t->name << ' ' << t->street << ' ' << t->city << endl;
		break;
	};
	case 2:
	{
		Address *t = *phead;
		while (t)
		{
			if (!strcmp(name, t->street))
				break;
			t = t->next;
		}
		if (!t)
			cerr << "��� �� �������" << endl;
		else
			cout << t->name << ' ' << t->street << ' ' << t->city << endl;
			break;
	}
	case 3:
	{
		Address *t = *phead;
		while (t)
		{
			if (!strcmp(name, t->city))
				break;
			t = t->next;
		}
		if (!t)
			cerr << "��� �� �������" << endl;
		else
			cout << t->name << ' ' << t->street << ' ' << t->city << endl;
	} break;
	}
}


int main(void)
{
	Address *head = NULL;
	Address *last = NULL;
	setlocale(LC_CTYPE, "Rus");
	int k;
	while (true)
	{
		switch (menu())
		{
		case 1: {
			create(setElement(), &head, &last);
		}
				break;
		case 2: {
			char dname[NAME_SIZE];
			cout << "������� ���: ";
			cin.getline(dname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			delet(dname, &head, &last);
		}
				break;
		case 3:  outputList(&head, &last);
			break;
		case 4: {
			char fname[NAME_SIZE];
			cout << "������� ���: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			find(fname, &head);
		}
				break;
		case 5:  writeToFile(&head);
			break;
		case 6:  readFromFile(&head, &last);
			break;
		case 7: {
			char fname[NAME_SIZE];
			cout << "������� ���: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			cout << "�� ������ ���� ������������ ����� (1- �� �����, 2- �� �����, 3- �� ������)"; 
			cin >> k;
			search(fname, &head, k); 
			getchar();
			//system("pause");
			break;
			}
		case 8: exit(0);
		default: exit(1);
		}
	}
	return 0;
}
