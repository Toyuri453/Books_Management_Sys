#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <tchar.h>
#include <string>
#include <sstream>
#include<iomanip>
#include "vector"
#import "C:\Program Files\Common Files\system\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")rename("BOF", "adoBOF")

using namespace std;

#define LIMIT '5'
#define DATE "2019-09-04"
int current_SNO = 10008;
int option = 9;

int Back() {
	char ism;
	do {
		cout << endl << "输入m返回菜单.";
			cin >> ism;
	} while (ism != 'm');
	return 1;

}



class LibraryManagementSystem {
public:

	void QueryByBookName(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {
		string book_name;
		cout << endl << "请输入图书名称: ";
		cin >> book_name;

		string query_sql;

		query_sql = "SELECT BNU FROM BOOKS_MAIN WHERE BNA = '" + book_name + "'";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);

		_variant_t amount = pRst->GetCollect("BNU");
		if (*((char*)(_bstr_t)amount) != '0') {
			query_sql = "SELECT * FROM BOOKS_INFO WHERE Bna = '" + book_name + "' AND BorrowInfo = '0'";
			_bstr_t bstrSQL2(query_sql.c_str());
			pRst = pMyConnect->Execute(bstrSQL2, NULL, adCmdText);

			vector<_bstr_t> column_name;
			cout << endl << std::right << "书籍名称 " << setw(20) << "书籍编号" << setw(16) << "出版日期" << setw(14) << "出版社" << setw(18) << "存放位置";
			for (int i = 0; i< pRst->Fields->GetCount(); i++)
			{
				//cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
				column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			}
			cout << endl;

			while (!pRst->adoEOF) {
				vector<_bstr_t>::iterator iter = column_name.begin();
				for (iter; iter != column_name.end(); iter++) {
					if (pRst->GetCollect(*iter).vt != VT_NULL) {
						cout  << std::left << setw(15) << (_bstr_t)pRst->GetCollect(*iter) << " ";
					}
					else {
						cout << "NULL" << endl;
					}
				}
				pRst->MoveNext();
				cout << endl;
			}
		}

		else {
			cout << endl << "该图书已无库存！";
		}

	}

	int Borrowing(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {
		string BNO;
		string SNO;
		cout << endl << "请输入借书卡号： ";
		cin >> SNO;

		string query_sql = "SELECT BS FROM CARD_INFO WHERE SNO = '" + SNO + "'";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);

		_variant_t borrowed_amount = pRst->GetCollect("BS");
		if (*((char*)(_bstr_t)borrowed_amount) == LIMIT) {
			cout << endl << "借书数已达上限！";
			return 1;
		}

		query_sql = "SELECT OverdueS FROM CARD_INFO WHERE SNO = '" + SNO + "'";
		_bstr_t bstrSQL2(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL2, NULL, adCmdText);

		_variant_t isoverdue = pRst->GetCollect("OverdueS");
		if (*((char*)(_bstr_t)isoverdue) == '1') {
			cout << endl << "请先归还逾期图书！";
			return 2;
		}

		cout << endl << "请输入借阅图书编号： ";
		cin >> BNO;
		query_sql = "SELECT * FROM BOOKS_INFO WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL3(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL3, NULL, adCmdText);

		/*
		vector<_bstr_t> column_name;

		for (int i = 0; i< pRst->Fields->GetCount(); i++)
		{
			cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		cout << endl;
		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
				}
				else
				{
					cout << "NULL" << endl;
				}
			}
			pRst->MoveNext();
			cout << endl;
		}
		*/

		query_sql = "SELECT BNA FROM BOOKS_INFO WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL4(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL4, NULL, adCmdText);
		_variant_t COM_book_name = pRst->GetCollect("BNA"); 
		string s_book_name = (char *)(_bstr_t)COM_book_name;      

		query_sql = "UPDATE BOOKS_MAIN SET BNU = BNU - 1 WHERE BNA = '" + s_book_name + "'";
		_bstr_t bstrSQL5(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL5, NULL, adCmdText);

		query_sql = "UPDATE BOOKS_INFO SET BorrowInfo = '" + SNO + "' WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL6(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL6, NULL, adCmdText);  

		query_sql = "UPDATE CARD_INFO SET BS = BS + 1 WHERE SNO = '" + SNO + "'";
		_bstr_t bstrSQL7(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL7, NULL, adCmdText); 

		query_sql = "INSERT INTO BORROW_INFO VALUES('" + SNO + "','" + BNO + "','2019-09-04','2019-12-04','0')";
		_bstr_t bstrSQL8(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL8, NULL, adCmdText); 
		
		cout << endl << "您已成功借阅  " << s_book_name << ". ";
		return 3;

	}

	void PayFine(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {

		string SNO;
		cout << endl << "请输入借书卡号： ";
		cin >> SNO;

		string query_sql = "SELECT OverdueS FROM CARD_INFO WHERE SNO = '" + SNO + "'";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);

		_variant_t isoverdue = pRst->GetCollect("OverdueS");
		if (*((char*)(_bstr_t)isoverdue) == '0') {
			cout << endl << "无需缴费！";
		}
		else {

			query_sql = "SELECT OverdueP FROM CARD_INFO WHERE SNO = '" + SNO + "'";
			_bstr_t bstrSQL2(query_sql.c_str());
			pRst = pMyConnect->Execute(bstrSQL2, NULL, adCmdText);
			_variant_t fine = pRst->GetCollect("OverdueP");
			cout << endl << "成功支付逾期费用： " << setw(5) << (char*)(_bstr_t)fine << " 元！";

			query_sql = "UPDATE CARD_INFO SET OverdueS = '0', OverdueP = '0' WHERE SNO = '" + SNO + "'";
			_bstr_t bstrSQL3(query_sql.c_str());
			pRst = pMyConnect->Execute(bstrSQL3, NULL, adCmdText);

		}

	}

	void Register(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {
		string SNA, SDE, SSP;
		cout << endl << "请输入姓名： ";
		cin >> SNA;
		cout << endl << "请输入系别： ";
		cin >> SDE;
		cout << endl << "请输入专业： ";
		cin >> SSP;
		
		stringstream s_current_SNO;
		s_current_SNO << current_SNO;
		string ss_current_SNO = s_current_SNO.str();


		string query_sql = "INSERT INTO STUDENT_INFO VALUES ('" + SNA + "', '" + SDE + "', '" + SSP + "', '" + ss_current_SNO + "')";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);
		query_sql = "INSERT INTO CARD_INFO VALUES ('" + ss_current_SNO + "', " + LIMIT + ", '0', '0','0')";
		_bstr_t bstrSQL2(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL2, NULL, adCmdText);

		cout << endl << "办卡成功！ 您的卡号为： " << ss_current_SNO;
		current_SNO++;
	}

	void Return(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {
		string SNO;
		string BNO;
		cout << endl << "请输入借书卡号： ";
		cin >> SNO;
		cout << endl << "请输入书籍编号： ";
		cin >> BNO;

		string query_sql = "SELECT BNA FROM BOOKS_INFO WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);
		_variant_t COM_book_name = pRst->GetCollect("BNA"); 
		string s_book_name = (char *)(_bstr_t)COM_book_name;

		query_sql = "UPDATE BOOKS_MAIN SET BNU = BNU + 1 WHERE BNA = '" + s_book_name + "'";
		_bstr_t bstrSQL2(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL2, NULL, adCmdText);  

		query_sql = "UPDATE BOOKS_INFO SET BorrowInfo = '0' WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL3(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL3, NULL, adCmdText); 

		query_sql = "UPDATE CARD_INFO SET BS = BS - 1 WHERE SNO = '" + SNO + "'";
		_bstr_t bstrSQL4(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL4, NULL, adCmdText); 

		query_sql = "UPDATE BORROW_INFO SET ReturnTime = '2019-09-04', Overdue = '0' WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL5(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL5, NULL, adCmdText); 

		cout << endl << "还书成功！";
	}

	void Renew(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {
		string BNO;
		cout << endl << "请输入续借书籍编号： ";
		cin >> BNO;

		string query_sql = "UPDATE BORROW_INFO SET BorrowTime = '2019-09-04', ReturnTime = '2019-09-04' WHERE BNO = '" + BNO + "'";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);

		cout << endl << "续借成功！";
	}

	void QueryAll(_ConnectionPtr pMyConnect, _RecordsetPtr pRst) {
		string query_sql;

		query_sql = "SELECT * FROM BOOKS_INFO";
		_bstr_t bstrSQL(query_sql.c_str());
		pRst = pMyConnect->Execute(bstrSQL, NULL, adCmdText);
	
			vector<_bstr_t> column_name;
			cout << endl << std::right << "书籍名称 " << setw(20) << "书籍编号" << setw(16) << "出版日期" << setw(14) << "出版社" << setw(18) << "存放位置" << setw(16) << "出借情况" << endl;
			for (int i = 0; i< pRst->Fields->GetCount(); i++)
			{
				//cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
				column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			}
			cout << endl;

			while (!pRst->adoEOF) {
				vector<_bstr_t>::iterator iter = column_name.begin();
				for (iter; iter != column_name.end(); iter++) {
					if (pRst->GetCollect(*iter).vt != VT_NULL) {
						cout  << std::left << setw(15) << (_bstr_t)pRst->GetCollect(*iter) << " ";
					}
					else {
						cout << "NULL" << endl ;
					}
				}
				cout << endl<< "----------------------------------------------------------------------------------------------";
				pRst->MoveNext();
				cout << endl;
			}
	
	}
};


int main()
{

	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));

	try
	{

		pMyConnect->Open("Provider=SQLOLEDB; Server=127.0.0.1; Database=BOOKS_MANAGEMENT_SYSTEM; uid=admin; pwd=123;", "", "", adModeUnknown);

	}
	catch (_com_error &e)
	{
		cout << "Initiate failed!" << endl;
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return 0;
	}
	cout << "Connect succeed!" << endl;



	LibraryManagementSystem MainThread;

	//int option;

	while( option != 0) {

		system("cls");
		cout << endl << "    图书借阅管理系统\n______________________________ \n\n1.查询书籍  2.借阅书籍 \n \n3.归还书籍  4.办理借阅卡 \n \n5.缴纳费用  6.续借书籍 \n \n7.查询所有书籍情况  0.退出程序 \n______________________________ \n \n请选择功能：";
		cin >> option;

		if (option == 1) {
			MainThread.QueryByBookName(pMyConnect, pRst);
			Back(); continue;
		}
		else if (option == 2) {
			MainThread.Borrowing(pMyConnect, pRst);
			Back(); continue;
		}
		else if (option == 3) {
			MainThread.Return(pMyConnect, pRst);
			Back(); continue;
		}
		else if (option == 4) {
			MainThread.Register(pMyConnect, pRst);
			Back(); continue;
		}
		else if (option == 5) {
			MainThread.PayFine(pMyConnect, pRst);
			Back(); continue;
		}
		else if (option == 6) {
			MainThread.Renew(pMyConnect, pRst);
			Back(); continue;
		}
		else if (option == 7) {
			MainThread.QueryAll(pMyConnect, pRst);
			Back(); continue;
		}
		else {
		};
	};
	
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
	}
	catch (_com_error &e)
	{
		cout << e.Description() << endl;
		cout << e.HelpFile() << endl;
		return 0;
	}
	CoUninitialize(); //释放COM环境
	system("pause");
	return 0;

	}

	


