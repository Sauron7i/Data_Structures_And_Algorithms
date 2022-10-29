#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

bool Priority(char ch, char topch)
{
	if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
		return true;
	if (topch == '(' && ch != ')')
		return true;

	return false;
}
// 中缀表达式-》后缀表达式
string MiddleToEndExpr(string& expr)
{
	string result;
	stack<char> s;

	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result.push_back(ch);
		}
		else
		{
			for (; ;)
			{
				// 处理符号
				if (s.empty() || ch == '(')
				{
					s.push(ch);
					break;
				}

				// 比较当前ch和栈顶符号的优先级
				char topch = s.top();

				// true -> ch > topch
				if (Priority(ch, topch))
				{
					s.push(ch);
					break;
				}
				else
				{
					s.pop();
					if (topch == '(')
						break;
					result.push_back(topch);
				}
			}
		}
	}

	// 如果符号栈还存留符号，直接输出到后缀表达式
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}

	return result;
}


// 链式栈
class LinkStack
{
public:
	LinkStack()
	{
		head_ = new Node;
		size_ = 0;
	}
	~LinkStack()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

	// 入栈
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		size_++;
	}

	// 出栈
	void pop()
	{
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
		size_--;
	}

	int top() const
	{
		if (head_->next_ == nullptr)
			throw "stack is empty!";
		
		return head_->next_->data_;
	}

	// 判空
	bool isEmpty() const
	{
		return head_->next_ == nullptr;
	}

	// 返回栈的元素个数
	int size() const
	{
		return size_;
	}

private:
	struct Node
	{
		Node(int data = 0) : data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_;
	int size_;
};

int main(void)
{
	int nums[] = { 12, 23, 34, 45, 56, 67, 78 };
	LinkStack s;

	for (int num : nums)
	{
		s.push(num);
	}

	return 0;
}
