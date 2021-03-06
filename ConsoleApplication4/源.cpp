
#include "stdafx.h"
#include"源.h"


std::vector<std::string> ThreadData::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作  
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
bool ThreadData::loadData(string str) {
	CoInitialize(NULL); //初始化COM环境             
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象   
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象                 
	try
	{
		//步骤2：创建数据源连接  
		/*打开数据库“SQLServer”，这里需要根据自己PC的数据库的情况 */
		string sdm = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + str;
		pMyConnect->Open(sdm.c_str(), "", "", adModeUnknown);
	}
	catch (_com_error &e)
	{
		cout << "Initiate failed!" << endl;
		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		return 0;
	}
	cout << "Connect succeed!" << endl;

	//步骤3：对数据源中的数据库/表进行操作  
	try
	{
		pRst = pMyConnect->Execute("select * from Six", NULL, adCmdText);//执行SQL： select * from gendat            
		if (!pRst->BOF)
		{
			pRst->MoveFirst();
			//pRst->MoveLast();
		}
		else
		{
			cout << "Data is empty!" << endl;
			return 0;
		}
		//vector<_bstr_t> column_name;

		/*存储表的所有列名，显示表的列名*/
		//for (int i = 0; i< pRst->Fields->GetCount(); i++)
		//{
		//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
		//	column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		//}
		//cout << endl;

		/*对表进行遍历访问,显示表中每一行的内容*/
		while (!pRst->adoEOF)
		{
			//cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
			vector<int> v(11, 0);
			v[0] = pRst->GetCollect("P1");
			v[1] = pRst->GetCollect("P2");
			v[2] = pRst->GetCollect("P3");
			v[3] = pRst->GetCollect("P4");
			v[4] = pRst->GetCollect("P5");
			v[5] = pRst->GetCollect("P6");
			v[6] = pRst->GetCollect("TM");

			string s = (_bstr_t)pRst->GetCollect("RQ");
			//cout << s << endl;
			vector<string> date = split(s, "/");
			v[7] = atoi(date[0].c_str());
			v[8] = atoi(date[1].c_str());
			v[9] = atoi(date[2].c_str());
			v[10] = pRst->GetCollect("QS");
			if (v[8] * 100 + v[9] < 204)
				v[7] -= 1;

			TMdata.push_back(v);

			pRst->MoveNext();
			//pRst->MovePrevious();
			//cout << endl;


		}
		reverse(TMdata.begin(), TMdata.end());
	}
	catch (_com_error &e)
	{
		//cout << e.Description() << endl;
		//			cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());

		return 0;
	}

	//步骤4：关闭数据源  
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集                 
		pMyConnect->Close();//关闭数据库                 
		pRst.Release();//释放记录集对象指针                 
		pMyConnect.Release();//释放连接对象指针  
	}
	catch (_com_error &e)
	{
		//cout << e.Description() << endl;
		//cout << e.HelpFile() << endl;
		AfxMessageBox(e.ErrorMessage());
		AfxMessageBox(e.Description());
		return 0;
	}
	CoUninitialize(); //释放COM环境  




}
int ThreadData::getResultType(int x) {
	switch (x) {
	case 0:
		return 0;
	case 1:
		isUse[2] = false;
		return 1;
	case 2:
		isUse[3] = false;
		return 3;
	case 3:
		isUse[3] = false;
		return 4;
	case 4:
		isUse[2] = false;
		return 2;
	case 5:
		return 5;
	case 6:
		return 7;
	case 7:
		isUse[3] = false;
		return 8;
	case 8:
		isUse[2] = false;
		return 6;
	case 9:
		isUse[2] = false;
		return 9;
	case 10:
		isUse[3] = false;
		return 10;
	case 11:
		isUse[3] = false;
		isUse[2] = false;
		return 11;
	case 12:
		isUse[3] = false;
		isUse[2] = false;
		return 12;
	case 13:
		isUse[3] = false;
		isUse[2] = false;
		return 13;
	case 14:
		isUse[3] = false;
		isUse[2] = false;
		return 14;
	case 15:
		isUse[3] = false;
		isUse[2] = false;
		return 15;
	case 16:
		isUse[3] = false;
		isUse[2] = false;
		return 16;
	case 17:
		isUse[3] = false;
		return 17;
	case 18:
		isUse[3] = false;
		return 18;
	case 19:
		isUse[3] = false;
		return 19;
	case 20:
		isUse[1] = false;
		isUse[3] = false;
		return 20;
	case 21:
		isUse[2] = false;
		return 21;
	default:
		return -1;
	}


}
string ThreadData::getcommand(string str) {
	int p[12];
	string com = "";
	p[0] = GetPrivateProfileInt("TSpinEdit", "SpinEdit7", -1, str.c_str());
	p[1] = GetPrivateProfileInt("TSpinEdit", "SpinEdit8", -1, str.c_str());
	p[2] = GetPrivateProfileInt("TSpinEdit", "SpinEdit9", -1, str.c_str());
	p[3] = GetPrivateProfileInt("TSpinEdit", "SpinEdit10", -1, str.c_str());
	p[4] = GetPrivateProfileInt("TSpinEdit", "SpinEdit25", -1, str.c_str());
	p[5] = GetPrivateProfileInt("TSpinEdit", "SpinEdit26", -1, str.c_str());
	p[6] = GetPrivateProfileInt("TSpinEdit", "SpinEdit27", -1, str.c_str());
	p[7] = GetPrivateProfileInt("TSpinEdit", "SpinEdit28", -1, str.c_str());
	p[8] = GetPrivateProfileInt("TSpinEdit", "SpinEdit29", -1, str.c_str());
	p[9] = GetPrivateProfileInt("TSpinEdit", "SpinEdit30", -1, str.c_str());
	p[10] = GetPrivateProfileInt("TSpinEdit", "SpinEdit31", -1, str.c_str());
	p[11] = GetPrivateProfileInt("TSpinEdit", "SpinEdit32", -1, str.c_str());
	int ComboBox21 = GetPrivateProfileInt("TComboBox", "ComboBox21", -1, str.c_str());
	int ComboBox3 = GetPrivateProfileInt("TComboBox", "ComboBox3", -1, str.c_str());
	switch (ComboBox3) {
	case 0:
		ComboBox3 = 1; break;
	case 1:
		ComboBox3 = 2; break;
	case 2:
		ComboBox3 = 3; break;
	case 3:
		ComboBox3 = 4; break;
	case 7:
		ComboBox3 = 5; break;
	case 8:
		ComboBox3 = 6; break;
	case 9:
		ComboBox3 = 7; break;
	case 10:
		ComboBox3 = 8; break;
	case 11:
		ComboBox3 = 9; break;
	case 12:
		ComboBox3 = 10; break;
	case 13:
		ComboBox3 = 11; break;
	case 14:
		ComboBox3 = 12; break;

	}
	for (int i = 0; i < ComboBox3; i++)
	{
		for (int j = 0; j<p[i]; j++)
			com += ('0' + (i + 1 + ComboBox21) % 2);
	}
	reverse(com.begin(), com.end());
	return com;
}
string ThreadData::Int_to_String(int n)
{
	ostringstream stream;
	stream << n;  //n为int类型
	return stream.str();
}
void ThreadData::load(string str) {
	for (int i = 0; i < 7; i++)
		isUse[i] = true;

	command = getcommand(str.c_str());

	resultType = GetPrivateProfileInt("TComboBox", "ComboBox4", -1, str.c_str());
	//cout << resultType << endl;
	for (int i = 1; i < 50; i++)
	{
		type[0][i] = i % 49;
		if (!type[0][i])
			type[0][i] = 49;
	}

	for (int i = 1; i < 50; i++)
	{
		type[1][i] = (i / 10 + i % 10) % 10;
	}

	for (int i = 1; i < 50; i++)
	{
		type[2][i] = i % 10;
	}

	for (int i = 1; i < 50; i++)
	{
		type[3][i] = i % 12;
		if (!type[3][i])
			type[3][i] = 12;
	}
	for (int i = 1; i < 50; i++)
	{
		type[4][i] = (TMdata[0][7] % 12 + 22 - i % 12) % 12;
		if (!type[4][i])
			type[4][i] = 12;
	}

	for (int i = 1; i < 50; i++)
	{
		type[5][i] = i / 7 + 1;
		if (i % 7 == 0)
			type[5][i] -= 1;
	}

	for (int i = 1; i < 50; i++)
	{
		type[6][i] = i / 10;
	}

	for (int i = 1; i < 50; i++)
	{
		type[7][i] = i % 7;
	}

	{
		int a1[] = { 01,07,13,19,23,29,35,45 };
		int a2[] = { 02,8,12,18,24,30,34,40,46 };
		int a3[] = { 03,9,15,25,31,37,41,47 };
		int a4[] = { 04,10,14,20,26,36,42,48 };
		int a5[] = { 05,11,17,21,27,33,39,43,49 };
		int a6[] = { 06,16,22,28,32,38,44 };
		for (int i = 0; i < 8; i++)
			type[8][a1[i]] = 1;
		for (int i = 0; i < 9; i++)
			type[8][a2[i]] = 0;
		for (int i = 0; i < 8; i++)
			type[8][a3[i]] = 3;
		for (int i = 0; i < 8; i++)
			type[8][a4[i]] = 2;
		for (int i = 0; i < 9; i++)
			type[8][a5[i]] = 5;
		for (int i = 0; i < 7; i++)
			type[8][a6[i]] = 4;
	}

	{
		int a1[] = { 03,04,17,18,25,26,33,34,47,48, };
		int a2[] = { 07,8,15,16,29,30,37,38,45,46, };
		int a3[] = { 05,06,13,14,21,22,35,36,43,44, };
		int a4[] = { 01,02,9,10,23,24,31,32,39,40, };
		int a5[] = { 11,12,19,20,27,28,41,42,49, };

		for (int i = 0; i < 10; i++)
			type[9][a1[i]] = 0;
		for (int i = 0; i < 10; i++)
			type[9][a2[i]] = 1;
		for (int i = 0; i < 10; i++)
			type[9][a3[i]] = 2;
		for (int i = 0; i < 10; i++)
			type[9][a4[i]] = 3;
		for (int i = 0; i < 9; i++)
			type[9][a5[i]] = 4;


	}
	{
		int a1[] = { 01,07,13,19,23,29,35,45 };
		int a2[] = { 02,8,12,18,24,30,34,40,46 };
		int a3[] = { 03,9,15,25,31,37,41,47 };
		int a4[] = { 04,10,14,20,26,36,42,48 };
		int a5[] = { 05,11,17,21,27,33,39,43,49 };
		int a6[] = { 06,16,22,28,32,38,44 };
		for (int i = 0; i < 8; i++)
			type[10][a1[i]] = 1 / 2;
		for (int i = 0; i < 9; i++)
			type[10][a2[i]] = 0 / 2;
		for (int i = 0; i < 8; i++)
			type[10][a3[i]] = 3 / 2;
		for (int i = 0; i < 8; i++)
			type[10][a4[i]] = 2 / 2;
		for (int i = 0; i < 9; i++)
			type[10][a5[i]] = 5 / 2;
		for (int i = 0; i < 7; i++)
			type[10][a6[i]] = 4 / 2;
	}
	for (int i = 1; i < 50; i++)
	{
		type[11][i] = i % 2;
	}
	for (int i = 1; i < 50; i++)
	{
		type[12][i] = i / 25;
	}
	for (int i = 1; i < 50; i++)
	{
		type[13][i] = (i / 10 + i % 10) % 2;
	}
	for (int i = 1; i < 50; i++)
	{
		type[14][i] = (i / 10 + i % 10) / 5;
	}
	for (int i = 1; i < 50; i++)
	{
		type[15][i] = (i % 10) / 5;
	}
	for (int i = 1; i < 50; i++)
	{
		type[16][i] = (i / 25) * 2 + (i % 2);
	}
	for (int i = 1; i < 50; i++)
	{
		type[17][i] = i % 3;
	}
	for (int i = 1; i < 50; i++)
	{
		type[18][i] = i % 4;
	}
	for (int i = 1; i < 50; i++)
	{
		type[19][i] = i % 6;
	}
	for (int i = 1; i < 50; i++)
	{
		type[20][i] = (i / 10) + i % 10;
	}
	for (int i = 1; i < 50; i++)
	{
		type[21][i] = (i / 10) * 2 + i % 2;
	}

	resultType = getResultType(resultType);
	int che74 = GetPrivateProfileInt("TCheckBox", "CheckBox74", -1, str.c_str());
	if (che74)
		for (int i = 0; i < 7; i++)
			isUse[i] = true;
	isYiwei = GetPrivateProfileInt("TCheckBox", "CheckBox89", -1, str.c_str());
	gongshinum = GetPrivateProfileInt("TComboBox", "ComboBox5", -1, str.c_str());


	//cout << gongshinum << endl;
	if (resultType == -1 || isYiwei == -1 || che74 == -1 || gongshinum == -1) {
		cout << "错误" << endl;
		system("pause");
	}

	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox";
		b.push_back('1' + i);
		dd[0][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[0][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[0] && dd[0][i])
			z.push_back(i);

	}
	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox" + Int_to_String(10 + i);
		dd[1][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[1][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[1] && dd[1][i])
			z.push_back(7 + i);

	}

	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox" + Int_to_String(19 + i);
		dd[2][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[2][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[2] && dd[2][i])
			z.push_back(14 + i);

	}
	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox" + Int_to_String(28 + i);
		dd[3][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[3][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[3] && dd[3][i])
			z.push_back(21 + i);

	}
	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox" + Int_to_String(35 + i);
		dd[4][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[4][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[4] && dd[4][i])
			z.push_back(28 + i);

	}
	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox" + Int_to_String(42 + i);
		dd[5][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[5][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[5] && dd[5][i])
			z.push_back(35 + i);

	}
	for (int i = 0; i < 7; i++)
	{

		string b = "CheckBox" + Int_to_String(49 + i);
		dd[6][i] = GetPrivateProfileInt("TCheckBox", b.c_str(), -1, str.c_str());
		if (dd[6][i] == -1)
		{
			cout << "错误" << endl;
			system("pause");
		}
		if (isUse[6] && dd[6][i])
			z.push_back(42 + i);

	}


	len[0] = 49;
	len[1] = 10;
	len[2] = 10;
	len[3] = 12;
	len[4] = 12;
	len[5] = 7;
	len[6] = 5;
	len[7] = 7;
	len[8] = 6;
	len[9] = 5;
	len[10] = 3;
	len[11] = 2;
	len[12] = 2;
	len[13] = 2;
	len[14] = 2;
	len[15] = 2;
	len[16] = 4;
	len[17] = 3;
	len[18] = 4;
	len[19] = 6;
	len[20] = 13;
	len[21] = 10;


}

void ThreadData::getResult(vector<int>& vecInt, vector<int> t) {
	vector<int> result;
	for (int i = 0; i < vecInt.size(); ++i) {
		if (vecInt[i] == 1) {
			result.push_back(t[i]);
		}
	}
	s.push_back(result);

}


void ThreadData::Combination1(vector<int> set, int N, int m)
{
	int C = (1 << m) - 1;
	while (C <= ((1 << N) - (1 << (N - m))))
	{
		int i = 0;
		int k;
		vector<int> result;
		while ((k = 1 << i) <= C)
		{
			//循环测试每个bit是否为1     
			if ((C&k) != 0)
			{
				result.push_back(set[i]);
			}
			i++;
		}
		s.push_back(result);
		C = (C + (C&(-C))) | ((C ^ (C + (C&(-C)))) / (C&(-C))) >> 2;
	}
}
hanshu ThreadData::getSecond(hanshu a, hanshu b) {
	int count = 0;
	int te = b.tema;
	vector<int> jilu;
	int tenum = b.getnum(b.tema);

	for (int i = 1; i < 50; i++) {
		if (b.getnum(i) <= tenum)
		{
			if (jilu.empty() || find(jilu.begin(), jilu.end(), type[resultType][i]) == jilu.end())
			{
				count++;
				jilu.push_back(type[resultType][i]);
				if (type[resultType][i] > type[resultType][te] && b.getnum(i) == tenum) {
					count--;
				}
			}
		}
	}

	//cout << count << endl;
	vector<int> aa;
	multimap<int, int> Map, finalmap;
	for (int i = 1; i < 50; i++) {
		if (Map.find(type[resultType][i]) == Map.end())
			Map.insert(make_pair(type[resultType][i], a.getnum(i)));
	}
	for (multimap<int, int>::iterator it = Map.begin(); it != Map.end(); ++it)
	{
		finalmap.insert(make_pair(it->second, it->first));

	}
	int d = count;
	for (multimap<int, int>::iterator it = finalmap.begin(); it != finalmap.end(); ++it)
	{
		d--;
		if (d == 0)
		{
			int r = it->second;
			vector<int> res(50, 0);
			for (int i = 1; i < 50; i++)

				if (type[resultType][i] == r)
					res[i]++;
			return hanshu(res);

			break;
		}

	}

	return a;
}

hanshu ThreadData::sortone(int first) {
	int count = 0, mod = 1;
	vector<int> r(50, 0);
	for (vector<vector<int>>::iterator it = s.begin(); it != s.end(); ++it)
	{

		mod = 1;
		int m = 0;
		if (isYiwei)
		{
			mod = len[resultType];
			m = 1;
		}


		for (; m < mod; m++) {
			string str = "";

			for (int i = 1 + first; i < command.length() + 1 + first; i++)
			{
				if (resultType == 4) {
					for (int j = 1; j < 50; j++)
					{
						type[4][j] = (TMdata[i][7] % 12 + 22 - j % 12) % 12;
						if (!type[4][j])
							type[4][j] = 12;
					}
				}

				int result = 0;
				//for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); iter++)
				//{
				//	int n = *iter;
				//	int num = TMdata[i][n % 7];
				//	result += type[n / 7][num];
				//}
				for (int j = 0; j < gongshinum + 1; j++)
				{
					int n = (*it)[j];
					int num = TMdata[i][n % 7];
					result += type[n / 7][num];
				}

				result += m;

				if (resultType == 4) {
					for (int j = 1; j < 50; j++)
					{
						type[4][j] = (TMdata[i - 1][7] % 12 + 22 - j % 12) % 12;
						if (!type[4][j])
							type[4][j] = 12;
					}
				}

				if (type[resultType][TMdata[i - 1][6]] % len[resultType] == result % len[resultType])
				{
					if (command[i - 1 - first] == '1')
						str += '1';
					else
						break;
				}
				else
				{
					if (command[i - 1 - first] == '0')
						str += '0';
					else
						break;
				}



			}

			//cout << str << endl;
			if (str == command) {
				count++;
				int result = 0;
				if (resultType == 4) {
					for (int j = 1; j < 50; j++)
					{
						type[4][j] = (TMdata[first][7] % 12 + 22 - j % 12) % 12;
						if (!type[4][j])
							type[4][j] = 12;
					}
				}
				for (vector<int>::iterator iter = (*it).begin(); iter != (*it).end(); ++iter)
				{
					int n = *iter;
					int num = TMdata[0 + first][n % 7];
					result += type[n / 7][num];
					//cout << n << "(" << type[n / 7][num] << ") ";
				}
				//cout << (result) % len[resultType] << endl;
				result += m;

				for (int i = 1; i < 50; i++)
				{
					if (type[resultType][i] % len[resultType] == (result) % len[resultType])
						r[i] += 1;
				}

			}
		}

	}

	if (mod > 1)
		mod -= 1;
	//cout << s.size()*mod << " " << count << endl;

	return hanshu(r);
}
hanshu ThreadData::two(string str) {



	load(str);





	vector<int> r(50, 0);


	Combination1(z, z.size(), gongshinum + 1);


	hanshu a(sortone(0));


	hanshu b(sortone(1));

	b.tema = TMdata[0][6];


	hanshu result = getSecond(a, b);


	z.clear();
	s.clear();
	//cout << s.max_size();
	return result;

}
string ThreadData::all(string tar) {
	clock_t start, finish;
	double totaltime;
	start = clock();

	//char buf[256] = tar;


	//构造类对象
	CStatDir statdir;

	//设置要遍历的目录
	if (!statdir.SetInitDir(tar.c_str()))
	{
		puts("目录不存在。");
		return "目录不存在。";
	}

	//开始遍历

	vector<string>file_vec = statdir.BeginBrowseFilenames("*.*");
	//for (vector<string>::const_iterator it = file_vec.begin(); it < file_vec.end(); ++it)
	//std::cout << *it << std::endl;

	printf("文件总数: %d  ", file_vec.size());

	vector<int> re;
	re.resize(50, 0);
	hanshu finalresult(re);
	//for (int i = 0; i < 9; i++)
	//finalresult = finalresult + one(place[i]);

	for (vector<string>::const_iterator it = file_vec.begin(); it < file_vec.end(); ++it)
	{
		//cout << *it << endl;
		finalresult = finalresult + two(*it);
	}


	//cout << finalresult.jieguo(0);
	//one("C:\\001.ini");
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "此程序的运行时间为" << totaltime << "秒！" << endl;

	int year = TMdata[0][7];
	if (TMdata[0][8] * 100 + TMdata[0][9] < 204)
	{
		year += 1;
	}
	int zeronum = 0;
	if (TMdata[0][10] < 100 && TMdata[0][10]>9)
		zeronum = 1;
	if (TMdata[0][10] < 10)
		zeronum = 2;


	string head = Int_to_String(year) + "年" + string(zeronum, '0') + Int_to_String(TMdata[0][10]) + "期, 批量计算结果统计如下:\r\n";
	string tmstr = Int_to_String(year) + "年" + string(zeronum, '0') + Int_to_String(TMdata[0][10]) + "期: ";
	for (int i = 0; i < 6; i++)
	{
		if (TMdata[0][i] < 10)
			tmstr.append("0");
		tmstr.append(Int_to_String(TMdata[0][i]) + "-");
	}
	tmstr.append("T" + Int_to_String(TMdata[0][6]) + "  \r\n");

	return head + tmstr + finalresult.jieguo(0);
	//system("pause");
}
