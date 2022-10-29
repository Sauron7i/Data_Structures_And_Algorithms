#include <iostream>
using namespace std;

const int INC = 2;	// 扩容倍数,可更改
class SeqStack
{
public:
	SeqStack(int size = 10)
		: mtop(0)
		, mcap(size)
	{
		mpStack = new int[mcap];
	}

	~SeqStack()
	{
		delete[] mpStack;
		mpStack = nullptr;
	}

public:
	// 入栈
	void push(int val)
	{
		if (mcap == mtop)
		{
			expand(INC * mcap);
		}

		mpStack[mtop++] = val;
	}

	// 出栈
	void pop()
	{
		if (isEmpty())
			throw "stack is empty!";
		mtop--;
	}

	// top
	int top() const
	{
		if (isEmpty())
			throw "stack is empty!";
		return mpStack[mtop - 1];
	}

	bool isEmpty() const
	{
		return 0 == mtop;
	}

	int size() const
	{
		return mtop;
	}

private:
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpStack, sizeof(int) * mtop);
		delete[]mpStack;
		mpStack = p;
		mcap = size;
	}
private:
	int* mpStack;	// 动态数组
	int mtop;		// 栈顶位置
	int mcap;		// 容量
};

int main(void)
{
	int nums[] = { 12, 23, 34, 45, 56, 67, 78 };
	SeqStack s;

	for (int num : nums)
	{
		s.push(num);
	}

	int count = s.size();
	int topnum = s.top();
	s.pop();

	cout << "stack size = " << count << " " << "top num = " << topnum << endl;
	return 0;
}
