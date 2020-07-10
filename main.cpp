#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;
#pragma warning (disable : 4996)
void getpassword(char *p);
int login(FILE *database);
int menu();
void add(FILE* database);
void explore(FILE* database);
int seek(char* orgin, char* target, int olength, int tlength);
void manage(FILE* database);
void edit(char* name, char* stuID, char* address, char* phone, char* email, FILE* database, int dataexist, char* password);
int del(int dataexist, int sel);
void seek(int dataexist);
void reset();
void ranking(int dataexist);

struct people
{
	char name[10];
	char stuID[15];
	char address[30];
	char phone[15];
	char email[30];
}people[1000];

int main()
{
	
	FILE* database = NULL;
	int status = 0;
	status = login(database);
	if (status == 1)
	{
		system("cls");
		printf("登录成功！\n");
	}
	else if (status == 2)
	{
		system("cls");
		printf("注册成功！\n");
	}
	else
	{
		exit(0);
	}

	while (1)
	{
		int opt = menu();
		switch (opt)
		{
		case 5:exit(0); break;
		case 1:add(database); break;
		case 2:explore(database); break;
		case 3:manage(database); break;
		case 4:reset(); break;
		}

	}


}

	void getpassword(char *p)//接收密码函数，返回密码
	{

			char *password=p;//用于记录起始地址，为退格操作提供上限
			//if (_kbhit())
			//{
				while ((*p = getch()) && *p != 13)//*p负责接收字符，直到收到回车键为止
				{
					if (*p == 8)//退格操作
					{
						if (p != password)
						{
							*(p--) = 0;
							putchar(8);
							putchar(' ');
							putchar(8);
						}
						continue;
					}
					putchar('*');
					p++;
				}
				*(p++) = 0;
			//}

			cout << endl;
			
	}

	int login(FILE* database)
		/*
		返回0-没有登陆
		返回1-登陆成功
		返回2-注册成功
		*/
	{
		int ch;
		if ((database = fopen("addressbook.data", "rb")) == NULL)//检测没有存档
		{
			cout << "未检测到存档，是否创建？（Y/N)";
			while (1)
			{
				if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真

					ch = _getch();//使用_getch()函数获取按下的键值
					//printf("%d", ch);


					if (ch == 89 || ch == 121)//按下Y键
					{
						system("cls");
						cout << "新建存档" << endl;
						database = fopen("addressbook.data", "wb");

					setpassword:
						cout << "请设置密码： ";
						char password1[100];
						getpassword(password1);

						cout << "请再输入一次： ";
						char password2[100];
						getpassword(password2);

						if (strcmp(password1, password2) == 0)
						{
							if (fwrite(&password1, sizeof(password1), 1, database) == 1)
							{
								printf("密码设置成功！\n");
								fflush(database);
								cout << endl;
								return 2;
							}
							else
							{
								printf("注册失败！\n");
								abort();
							}

						}
						else
						{
							printf("两次输入不一致！\n");
							goto setpassword;

						}

						break;

					}

					else if (ch == 78 || ch == 110)
					{
						exit(1);
					}
				}
			}
			fclose(database);
		}
		else // 已有存档
		{
			cout << "欢迎使用班级通讯录管理系统！" << endl << "请输入密码： ";

			while (1)
			{

				char passwordinput[100];
				getpassword(passwordinput);
				char currentpassword[100];
				fread(currentpassword, sizeof(currentpassword), 1, database);
				fclose(database);

				if (strcmp(passwordinput, currentpassword) == 0)
				{
					fclose(database);
					return 1;
					break;
				}
				else
				{
					cout << "密码错误，请重新输入： ";
				}
			}
			
		}
	}

	int menu()
	{
		system("cls");
		cout << "欢迎使用班级通讯录管理系统！" << endl << "By zhaozeyu@stu.bucea.edu.cn" << endl<<endl;
		cout << "F1--增加信息" << endl;
		cout << "F2--信息浏览" << endl;
		cout << "F3--信息管理" << endl;
		cout << "F4--重新录入" << endl;
		cout << "ESC--退出" << endl;
		while(1)
		{
			if (kbhit())
			{
				int opt = 0;
				opt = getch();
				//cout << opt << endl;
				switch (opt)
				{
				case 59:return 1; break;
				case 60:return 2; break;
				case 61:return 3; break;
				case 62:return 4; break;
				case 27:return 5; break;
				}
			}
		}

	}

	void add(FILE* database)
	{
		system("cls");

		database = fopen("addressbook.data", "ab+");
		//database += 100;
		cout << "增加信息  输入*放弃编辑" << endl;
		
		cout << "姓名：";
		cin >> people[1].name;
		if (strcmp(people[1].name, "*") == 0) goto exitadd;

		cout << "学号：";
		cin >> people[1].stuID;
		if (strcmp(people[1].stuID, "*") == 0) goto exitadd;

		cout << "地址：";
		cin >> people[1].address;
		if (strcmp(people[1].address, "*") == 0) goto exitadd;

		cout << "电话：";
		cin >> people[1].phone;
		if (strcmp(people[1].phone, "*") == 0) goto exitadd;

		cout << "E-mail：";
		cin >> people[1].email;
		if (strcmp(people[1].email, "*") == 0) goto exitadd;
		fwrite(&people[1], sizeof(people[1]), 1, database);


		exitadd:
		fclose(database);

		/*
			char name[10];
	char stuID[15];
	char address[30];
	char phone[15];
	char email[30];
		*/
	}

	void explore(FILE* database)
	{
		system("cls");
		char rubbish[100];
		database = fopen("addressbook.data", "rb");
		fread(&rubbish, 100, 1, database);//抛弃掉前100字节
		printf("姓名\t学号\t\t地址\t电话\t电子邮件\n");//输出表头
		int i,j;
		for (i = 0; ; i++)
		{
			if (fread(&people[i], sizeof(people[i]), 1, database) == 0)
			{
				break;
			}
		}
		ranking(i - 1);
		for (j = 0; j < i; j++)
		{
			printf("%s\t%s\t\t%s\t%s\t%s\n", people[j].name, people[j].stuID, people[j].address, people[j].phone, people[j].email);
		}
		fclose(database);
		system("pause");

	}

	/*int seek(char* orgin, char* target,int olength,int tlength)//传入字符数组的指针，分别代表原始数据和目标以及他们的长度
	{
		char innerorgin[50];
		for (int i = 1; i <= olength; i++)//把orgin中的每个元素拷贝到innerorgin
		{
			innerorgin[i] = *(orgin + (i - 1));
		}

		char innertarget[50];
		for (int i = 1; i <= tlength; i++)//把orgin中的每个元素拷贝到innerorgin
		{
			innerorgin[i] = *(target + (i - 1));
		}

		if (strstr(innerorgin, innertarget) != 0)//匹配到字符串就返回1，否则返回0
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	*/

	void manage(FILE* database)
	{
		database = fopen("addressbook.data", "rb");//临时设置为rb,需要修改！！！
		char password[100];
		fread(&password, 100, 1, database);//丢弃前100字节
		int dataexist;
		for (dataexist = 0; ; dataexist++)//将数据读入内存,从【0】开始存的
		{
			if (fread(&people[dataexist], sizeof(people[dataexist]), 1, database) == 0)
			{
				dataexist--;
				break;
			}
			
		}
		fclose(database);
		//由于是dataexist++，所以最终dataexist会比实际存在的数据数量大1
		int sel = 0;//当前光标位置

	showdata:
		system("cls");
		ranking (dataexist);
		if (sel >= dataexist+1)
		{
			sel = 0;
		}
		if (sel < 0)
		{
			sel = dataexist;
		}
		printf("   姓名\t学号\t\t地址\t电话\t电子邮件\n");//输出表头
		for (int i = 0; i <= dataexist; i++)
		{
			if (i == sel)
			{
				cout << " * ";
			}
			else
			{
				cout << "   ";
			}
			printf("%s\t%s\t\t%s\t%s\t%s\n", people[i].name, people[i].stuID, people[i].address, people[i].phone, people[i].email);
			
		}
		printf(" UP-向上移动\tDOWN-向下移动\tF1-检索\t\tEnter-编辑\tDel-删除\tESC-返回主菜单\n");
		while (1)
		{

			if (kbhit())//键值上72，下80
			{
				int ch = 0;
				ch = getch();
				//cout << ch << endl;
				//system("pause");
				switch (ch)
				{
				case 72: sel--; goto showdata; break;
				case 80: sel++; goto showdata; break;
				case 27: goto end; break;
				case 13: system("cls"); cout << "正在编辑：" << people[sel].name << "  输入*放弃编辑"<< endl; edit(people[sel].name, people[sel].stuID, people[sel].address, people[sel].phone, people[sel].email,database,dataexist,password); goto showdata; break;
				case 83: {
					if(del(dataexist, sel))
					{dataexist--; }

					goto showdata; 
					break; 
				}
				case 59: seek(dataexist); goto showdata; break;
				}
				
			}

		}


	end:
		database = fopen("addressbook.data", "wb");
		fwrite(password, 100, 1, database);//文件头写入密码部分
		for (int i = 0; i <= dataexist; i++)
		{
			fwrite(&people[i], sizeof(people[i]), 1, database);
		}
		fclose(database);
	}

	void edit(char* name, char* stuID, char* address, char* phone, char* email,FILE* database,int dataexist,char* password)
	{
		//备份原始数据，已被撤销修改
		char oname[10];
		strcpy(oname, name);
		char ostuID[15];
		strcpy(ostuID, stuID);
		char oaddress[30];
		strcpy(oaddress, address);
		char ophone[15];
		strcpy(ophone, phone);
		char oemail[30];
		strcpy(oemail, email);

		cout << "姓名：";
		cin >> name;
		if (strcmp(name, "*") == 0)
		{
			strcpy(name, oname);
			strcpy(stuID, ostuID);
			strcpy(address, oaddress);
			strcpy(phone, ophone);
			strcpy(email, oemail);
			goto end;
		}

		cout << "学号：";
		cin >> stuID;
		if (strcmp(stuID, "*") == 0)
		{
			strcpy(name, oname);
			strcpy(stuID, ostuID);
			strcpy(address, oaddress);
			strcpy(phone, ophone);
			strcpy(email, oemail);
			goto end;
		}

		cout << "地址：";
		cin >> address;
		if (strcmp(address, "*") == 0)
		{
			strcpy(name, oname);
			strcpy(stuID, ostuID);
			strcpy(address, oaddress);
			strcpy(phone, ophone);
			strcpy(email, oemail);
			goto end;
		}

		cout << "电话：";
		cin >> phone;
		if (strcmp(phone, "*") == 0)
		{
			strcpy(name, oname);
			strcpy(stuID, ostuID);
			strcpy(address, oaddress);
			strcpy(phone, ophone);
			strcpy(email, oemail);
			goto end;
		}

		cout << "E-mail：";
		cin >> email;
		if (strcmp(email, "*") == 0)
		{
			strcpy(name, oname);
			strcpy(stuID, ostuID);
			strcpy(address, oaddress);
			strcpy(phone, ophone);
			strcpy(email, oemail);
			goto end;
		}



	end:;
	}

	int del(int dataexist, int sel)
	{
		cout << "\n将要删除" << people[sel].name << "\nEnter-确认，ESC取消";
		while (1)
		{
			if (kbhit())
			{
				int ch = 0;
				ch = getch();
				//cout << ch << endl;
				//system("pause");
				switch (ch)
				{
				case 13: {
					for (int i = sel; i <= dataexist; i++)
					{
						people[i] = people[i + 1];
					}
					return 1;
					goto end;
					break;
				}
				case 27:return 0; goto end; break;
					
				}
			}
		}
	end:;
	}

	void seek(int dataexist)
	{
		char* s;
		char searchtarget[50];
		s = searchtarget;
		*s = 0;

	showres:
		system("cls");
		cout << "查找--按ESC退出" << endl;
		printf("   姓名\t学号\t\t地址\t电话\t电子邮件\n");//输出表头

		for (int i = 0; i <= dataexist; i++)
		{
			if (
				strstr(people[i].name, searchtarget) != NULL ||
				strstr(people[i].stuID, searchtarget) != NULL ||
				strstr(people[i].address, searchtarget) != NULL ||
				strstr(people[i].email, searchtarget) != NULL ||
				strstr(people[i].phone, searchtarget) != NULL
				)
			{
				printf("   %s\t%s\t\t%s\t%s\t%s\n", people[i].name, people[i].stuID, people[i].address, people[i].phone, people[i].email);
			}
		}
		cout << "\n输入要查找的内容：";
		cout << searchtarget;

		while ((*s = getch()) && *s!=29)
		{
			if (*s == 8)
			{
				if (s != searchtarget)
				{
					*(s--) = 0;
					putchar(8);
					putchar(' ');
					putchar(8);
					*s = 0;
					
				}

				goto showres;
			}
			else if (*s == 27) goto end;
			
			s++;
			*s = 0;
			goto showres;

			
		}
	end:;
	}

	void reset()
	{
		cout << endl << "警告：此操作将会清空所有数据，输入YES继续：";
		char control[10];
		cin >> control;
		if (strcmp(control, "YES") == 0)
		{
			remove("addressbook.data");
			cout << "已删除数据！将要重新开始录入。";
			system("pause");
			system("start AddressBook.exe");
			exit(0);
		}
	}

	void ranking (int dataexist)
	{
		for (int i = dataexist; i >= 0; i--)
		{
			for (int j = i-1; j >=0; j--)
			{
				int idi = 0, idj = 0;//将学号转换为int并比较大小
				sscanf(people[i].stuID, "%d", &idi);
				sscanf(people[j].stuID, "%d", &idj);
				if (idi < idj)
				{
					people[999] = people[i];
					people[i] = people[j];
					people[j] = people[999];

				}
			}
		}

	}