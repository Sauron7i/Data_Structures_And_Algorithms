#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

typedef int ElemType;
typedef struct Node
{
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// 单链表实现
class LinkList
{
public:
	LinkList()
	{
		// 给head_初始化指向头节点
		head_ = new Node();
	}
	~LinkList()
	{
		// 节点的释放
		Node* p = head_;

		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		head_ = nullptr;
	}

public:
	// 链表尾插法
	void InsertTail(int val)
	{
		// 找到末尾节点
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// 申请新节点
		Node* newNode = new Node(val);

		// 新节点挂到尾节点后面
		// newNode->next_ = p->next_;
		p->next_ = newNode;
	}

	// 链表头插 O(1)
	void InsertHead(int val)
	{
		Node* newNode = new Node(val);
		newNode->next_ = head_->next_;
		head_->next_ = newNode;
	}

	// 按值删除元素
	void Remove(int val)
	{
		Node* q = head_;
		Node* p = head_->next_;

		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				return;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}

	// 删除多个节点
	void RemoveAll(int val)
	{
		Node* q = head_;
		Node* p = head_->next_;

		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				p = q->next_;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}

	// find
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				return true;
			}
			p = p->next_;
		}
		return false;
	}

	// 打印
	void show()const
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}

private:
	Node* head_;	// 指向链表的头节点
	friend void mergeLink(LinkList& link1, LinkList& link2);
};

// 合并两个有序链表
void mergeLink(LinkList& link1, LinkList& link2)
{
	Node* p = link1.head_->next_;
	Node* q = link2.head_->next_;
	Node* last = link1.head_;
	link2.head_->next_ = nullptr;

	while (p != nullptr && q != nullptr)
	{
		if (p->data_ < q->data_)
		{
			last->next_ = p;
			p = p->next_;
		}
		else
		{
			last->next_ = q;
			q = q->next_;
		}
		last = last->next_;
	}

	if (p != nullptr)
	{
		last->next_ = p;
	}
	else
	{
		last->next_ = q;
	}
}

// 判断链表有环，返回入口节点
bool isLinkHasCircle(Node* head, int& val)
{
	Node* fast = head;
	Node* last = head;
	while (fast != nullptr && fast->next_ != nullptr)
	{
		fast = fast->next_->next_;
		last = last->next_;

		if (fast == last)
		{
			fast = head;
			while (fast != last)
			{
				fast = fast->next_;
				last = last->next_;
			}

			val = last->data_;
			return true;
		}
	}
	return false;
}

// 旋转链表
Node* rotateList(Node* head, int k)
{
	if (head == nullptr || k == 0)
		return nullptr;

	Node* p = head;
	Node* q = head;

	int num = 0;
	for (Node* k = head; k != nullptr; k = k->next_)
	{
		num++;
	}

	k = k % num;

	for (int i = 0; i < k; ++i)
	{
		p = p->next_;
	}

	while (p->next_ != nullptr)
	{
		p = p->next_;
		q = q->next_;
	}

	p->next_ = head;
	head = q->next_;
	q->next_ = nullptr;
	
	return head;
}

int main(void)
{
	LinkList link;
	srand(time(0));
	for (int i = 0; i < 10; ++i)
	{
		int val = rand() % 100;
		link.InsertHead(val);
	}
	link.show();

	link.InsertTail(100);
	link.show();

	link.Remove(100);
	link.show();
	return 0;
}
