#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include <string>
#include <io.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
using namespace std;

class CBrowseDir
{
protected:
	//��ų�ʼĿ¼�ľ���·������'\'��β
	char m_szInitDir[_MAX_PATH];

public:
	//ȱʡ������
	CBrowseDir() {
		//�õ�ǰĿ¼��ʼ��m_szInitDir
		_getcwd(m_szInitDir, _MAX_PATH);

		//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'
		int len = strlen(m_szInitDir);
		if (m_szInitDir[len - 1] != '\\')
			strcat_s(m_szInitDir, "\\");
	}

	//���ó�ʼĿ¼Ϊdir���������false����ʾĿ¼������
	bool SetInitDir(const char *dir)
	{
		//�Ȱ�dirת��Ϊ����·��
		if (_fullpath(m_szInitDir, dir, _MAX_PATH) == NULL)
			return false;

		//�ж�Ŀ¼�Ƿ����
		if (_chdir(m_szInitDir) != 0)
			return false;

		//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'
		int len = strlen(m_szInitDir);
		if (m_szInitDir[len - 1] != '\\')
			strcat_s(m_szInitDir, "\\");

		return true;
	}

	//��ʼ������ʼĿ¼������Ŀ¼����filespecָ�����͵��ļ�
	//filespec����ʹ��ͨ��� * ?�����ܰ���·����
	//�������false����ʾ�������̱��û���ֹ
	bool BeginBrowse(const char *filespec)
	{
		ProcessDir(m_szInitDir, NULL);
		return BrowseDir(m_szInitDir, filespec);
	}

	vector<string> BeginBrowseFilenames(const char *filespec) {
		ProcessDir(m_szInitDir, NULL);
		return GetDirFilenames(m_szInitDir, filespec);
	}

protected:
	//����Ŀ¼dir����filespecָ�����ļ�
	//������Ŀ¼,���õ����ķ���
	//�������false,��ʾ��ֹ�����ļ�
	bool BrowseDir(const char *dir, const char *filespec)
	{
		_chdir(dir);

		//���Ȳ���dir�з���Ҫ����ļ�
		long hFile;
		_finddata_t fileinfo;
		if ((hFile = _findfirst(filespec, &fileinfo)) != -1)
		{
			do
			{
				//����ǲ���Ŀ¼
				//�������,����д���
				if (!(fileinfo.attrib & _A_SUBDIR))
				{
					char filename[_MAX_PATH];
					strcpy_s(filename, dir);
					strcat_s(filename, fileinfo.name);
					cout << filename << endl;
					if (!ProcessFile(filename))
						return false;
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
		//����dir�е���Ŀ¼
		//��Ϊ�ڴ���dir�е��ļ�ʱ���������ProcessFile�п��ܸı���
		//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼Ϊdir��
		//ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼
		//��_findnextû��Ӱ�졣
		_chdir(dir);
		if ((hFile = _findfirst("*.*", &fileinfo)) != -1)
		{
			do
			{
				//����ǲ���Ŀ¼
				//�����,�ټ���ǲ��� . �� .. 
				//�������,���е���
				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp
					(fileinfo.name, "..") != 0)
					{
						char subdir[_MAX_PATH];
						strcpy_s(subdir, dir);
						strcat_s(subdir, fileinfo.name);
						strcat_s(subdir, "\\");
						ProcessDir(subdir, dir);
						if (!BrowseDir(subdir, filespec))
							return false;
					}
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
		return true;
	}
	vector<string> GetDirFilenames(const char *dir, const char *filespec)
	{
		_chdir(dir);
		vector<string>filename_vector;
		filename_vector.clear();

		//���Ȳ���dir�з���Ҫ����ļ�
		long hFile;
		_finddata_t fileinfo;
		if ((hFile = _findfirst(filespec, &fileinfo)) != -1)
		{
			do
			{
				//����ǲ���Ŀ¼
				//�������,����д���
				if (!(fileinfo.attrib & _A_SUBDIR))
				{
					char filename[_MAX_PATH];
					strcpy_s(filename, dir);
					strcat_s(filename, fileinfo.name);
					filename_vector.push_back(filename);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
		//����dir�е���Ŀ¼
		//��Ϊ�ڴ���dir�е��ļ�ʱ���������ProcessFile�п��ܸı���
		//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼Ϊdir��
		//ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼
		//��_findnextû��Ӱ�졣
		_chdir(dir);
		if ((hFile = _findfirst("*.*", &fileinfo)) != -1)
		{
			do
			{
				//����ǲ���Ŀ¼
				//�����,�ټ���ǲ��� . �� .. 
				//�������,���е���
				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp
					(fileinfo.name, "..") != 0)
					{
						char subdir[_MAX_PATH];
						strcpy_s(subdir, dir);
						strcat_s(subdir, fileinfo.name);
						strcat_s(subdir, "\\");
						ProcessDir(subdir, dir);
						vector<string>tmp = GetDirFilenames(subdir, filespec);
						for (vector<string>::iterator it = tmp.begin(); it<tmp.end(); it++)
						{
							filename_vector.push_back(*it);
						}
					}
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
		return filename_vector;
	}
	//����BrowseDirÿ�ҵ�һ���ļ�,�͵���ProcessFile
	//�����ļ�����Ϊ�������ݹ�ȥ
	//�������false,��ʾ��ֹ�����ļ�
	//�û����Ը�д�ú���,�����Լ��Ĵ������
	virtual bool ProcessFile(const char *filename)
	{
		return true;
	}

	//����BrowseDirÿ����һ��Ŀ¼,�͵���ProcessDir
	//�������ڴ����Ŀ¼������һ��Ŀ¼����Ϊ�������ݹ�ȥ
	//������ڴ�����ǳ�ʼĿ¼,��parentdir=NULL
	//�û����Ը�д�ú���,�����Լ��Ĵ������
	//�����û�����������ͳ����Ŀ¼�ĸ���
	virtual void ProcessDir(const char *currentdir, const char *parentdir)
	{
	}
};







//��CBrowseDir�����������࣬����ͳ��Ŀ¼�е��ļ�����Ŀ¼����
class CStatDir :public CBrowseDir
{
protected:
	int m_nFileCount;   //�����ļ�����
	int m_nSubdirCount; //������Ŀ¼����

public:
	//ȱʡ������
	CStatDir()
	{
		//��ʼ�����ݳ�Աm_nFileCount��m_nSubdirCount
		m_nFileCount = m_nSubdirCount = 0;
	}

	//�����ļ�����
	int GetFileCount()
	{
		return m_nFileCount;
	}

	//������Ŀ¼����
	int GetSubdirCount()
	{
		//��Ϊ�����ʼĿ¼ʱ��Ҳ����ú���ProcessDir��
		//���Լ�1�������������Ŀ¼������
		return m_nSubdirCount - 1;
	}

protected:
	//��д�麯��ProcessFile��ÿ����һ�Σ��ļ�������1
	virtual bool ProcessFile(const char *filename)
	{
		m_nFileCount++;
		return CBrowseDir::ProcessFile(filename);
	}

	//��д�麯��ProcessDir��ÿ����һ�Σ���Ŀ¼������1
	virtual void ProcessDir
	(const char *currentdir, const char *parentdir)
	{
		m_nSubdirCount++;
		CBrowseDir::ProcessDir(currentdir, parentdir);
	}
};