#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 数组实现
class Array
{
public:
	Array(int size = 10)
		: m_Cursize(0), m_Capacity(size)
	{
		m_Nums = new int[m_Capacity]();
	}

	~Array()
	{
		delete[] m_Nums;
		m_Nums = nullptr;
	}

	// 末尾增加元素
	void push_back(int val)
	{
		if (m_Cursize == m_Capacity)
		{ // 数组满了，扩容
			expand(m_Capacity * 2);
		}
		m_Nums[m_Cursize++] = val;
	}

	// 末尾删除元素
	void pop_back()
	{
		if (m_Cursize == 0)
			return;
		--m_Cursize;
	}

	// 按位置增加元素
	void insert(int pos, int val)
	{
		if (pos > m_Cursize || pos < 0)
		{
			return; // throw "pos invalid"
		}

		if (m_Cursize == m_Capacity)
		{
			expand(m_Capacity * 2);
		}

		// 移动元素
		for (int i = m_Cursize - 1; i >= pos; --i)
		{
			m_Nums[i + 1] = m_Nums[i];
		}

		m_Nums[pos] = val;
		++m_Cursize;
	}

	// 按位置删除
	void erase(int pos)
	{
		if (pos < 0 || pos > m_Cursize)
			return;

		// 直接向前覆盖
		for (int i = pos + 1; i < m_Cursize; ++i)
		{
			m_Nums[i - 1] = m_Nums[i];
		}

		--m_Cursize;
	}
	
	// 元素查询
	int find(int val)
	{
		for (int i = 0; i < m_Cursize; ++i)
		{
			if (m_Nums[i] == val)
			{
				return i;
			}
		}
		return -1;
	}

	// 打印
	void show() const
	{
		for (int i = 0; i < m_Cursize; ++i)
		{
			cout << m_Nums[i] << " ";
		}
		cout << endl;
	}

private:
	// 扩容接口
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, m_Nums, sizeof(int) * m_Capacity);
		delete[]m_Nums;

		m_Nums = p;
		m_Capacity = size;
	}
private:
	int* m_Nums;		// 指向可扩容的数组内存
	int m_Cursize;		// 有效个数
	int m_Capacity;		// 容量
};


int main(void)
{
	Array nums;

	srand(time(0));
	for (int i = 0; i < 10; ++i)
	{
		nums.push_back(rand() % 100);
	}

	nums.show();

	nums.pop_back();
	nums.show();

	nums.insert(0, 10);
	nums.show();

	nums.erase(8);
	nums.show();

	return 0;
}
