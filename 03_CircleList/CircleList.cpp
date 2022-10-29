#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 单向循环链表
class CircleLink
{
public:
	CircleLink()
	{
		head_ = new Node();
		tail_ = head_;
		head_->next_ = head_;
	}
	~CircleLink()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
	}

public:
	// 尾插
	void InsertTail(int val)
	{
		Node* newNode = new Node(val);
		newNode->next_ = head_;
		tail_->next_ = newNode;
		tail_ = newNode;
	}

	// 头插
	void InsertHead(int val)
	{
		Node* newNode = new Node(val);
		newNode->next_ = head_->next_;
		head_->next_ = newNode;
		if (newNode->next_ == head_)
			tail_ = newNode;
	}

	// 删除节点
	void Remove(int val)
	{
		Node* q = head_;
		Node* p = head_->next_;

		while (p != head_)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				if (q->next_ == head_) // 删的末尾
				{
					tail_ = q;
				}
				
				return;
			}
			q = p;
			p = p->next_;
		}
	}

	// 查询
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
				return true;
			p = p->next_;
		}
		return false;
	}

	// 打印
	void show()const
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}

private:
	struct Node
	{
		Node(int data = 0) : data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_;	// 指向头
	Node* tail_;	// 指向尾
};

int main(void)
{
	CircleLink link;
	srand(time(0));

	for (int i = 0; i < 10; ++i)
	{
		link.InsertTail(rand() % 100);
	}
	link.show();

	link.InsertHead(100);
	link.show();

	link.Remove(100);
	link.show();

	return 0;
}

/*
struct Node
{
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// 约瑟夫环问题-从第k个人开始报数，报到m的出列
void Joseph(Node* head, int k, int m)
{
	Node* p = head;
	Node* q = head;
	// q初始化成头节点的前驱
	while (q->next_ != head)
	{
		q = q->next_;
	}

	// 从第k个人开始
	for (int i = 1; i < k; ++i)
	{
		q = p;
		p = p->next_;
	}

	for (; ;)
	{
		for (int i = 1; i < m; ++i)
		{
			q = p;
			p = p->next_;
		}

		cout << p->data_ << " ";

		if (p == q)
		{
			delete p;
			break;
		}

		q->next_ = p->next_;
		delete p;
		p = q->next_;
	}
}
*/
