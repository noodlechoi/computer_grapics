#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*
• 최대 10개의 점 데이터를 저장하도록 한다. => 예외처리
• 리스트에 데이터를 입력하거나 삭제하고 출력하는 명령어를 실행한다.
• 각 명령어를 입력 받으면 결과 리스트를 다음페이지의 그림과 같이 항상 10개의 항목을 가진 리스트로 (인덱스와 데이터 값) 출력한다.

• 구현 함수 프로토타입과 명령어:
• + x y z: 리스트의 맨 위에 입력 (x, y, z: 숫자)
• -: 리스트의 맨 위에서 삭제한다.
• e x y z: 리스트의 맨 아래에 입력 (명령어 +와 반대의 위치, 리스트에 저장된 데이터값이 위로 올라간다.)
• d: 리스트의 맨 아래에서 삭제한다. (리스트에서 삭제된 칸이 비어있다.)
• l: 리스트에 저장된 점의 개수를 출력한다.
• c: 리스트를 비운다. 리스트를 비운 후 다시 입력하면 0번부터 저장된다.
• m: 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다.
• n: 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다.
• a: 원점과의 거리를 정렬하여 오름차순으로 정렬하여 출력한다. 인덱스 0번부터 빈 칸없이 저장하여 출력한다.
• s: 원점과의 거리를 정렬하여 내림차순으로 정렬하여 출력한다. (다시 a 또는 s를 누르면 원래의 인덱스 위치에 출력한다.)
• q: 프로그램을 종료한다
*/

// 점 (x, y, z) 데이터 값을 저장하는 리스트를 만든다. (점 데이터는 각각 정수이고, 구조체를 사용하도록 한다.)
typedef struct Pos
{
	int x, y, z;
}POS;

typedef struct Node
{
	POS data;
	struct Node* next;
}NODE;

class ListCommad
{
private:
	NODE* head;
	int node_num;
public:
	// head에 널 값 부여
	ListCommad();
	// head가 NULL이 아니면 모든 노트 해제
	~ListCommad();
	// 리스트 출력 함수
	void PrintList();
	// 리스트 갯수 출력
	void GetListNum();
	// 꼬리 노드 반환 함수
	NODE* TailNode();
	// 노드 생성 함수
	void InsertNode(POS data, const char& m);
	// 노드 서치 함수
	NODE* SearchNode(POS data, NODE* p);
	// 노드 삭제 함수
	void DeleteNode(const char& m);
	// 리스트 클리어
	void ClearList();
	// 거리 비교
	void CompareDis(const char& m);
	// 버블 정렬 거리순(오름차순)
	void BubbleAscending();
	// 버블 정렬 거리순(내림차순)
	void BubbleDescending();
	// 대입 연산자
	ListCommad& operator=(const ListCommad& c);
};

ListCommad::ListCommad() : node_num{0}
{
	head = NULL;
}

ListCommad::~ListCommad()
{
	while(head)
		DeleteNode('d');
}

void ListCommad::PrintList()
{
	if (head) {
		NODE* p;
		int i = 1;
		for (p = head; p->next != NULL; p = p->next) {
			cout << i++ << "번째 : " << p->data.x << ' ' << p->data.y << ' ' << p->data.z << endl;
		}
		cout << i << "번째 : " << p->data.x << ' ' << p->data.y << ' ' << p->data.z << endl;
	}
}

void ListCommad::GetListNum()
{
	cout << "리스트 수 : " << node_num << endl;
}

NODE* ListCommad::TailNode()
{
	NODE* p;
	for (p = head; p->next != NULL; p = p->next) {
	}

	return p;
}

void ListCommad::InsertNode(POS data, const char& m)
{
	// 10개의 리스트만 허용 예외처리
	try
	{
		if (node_num >= 10)	throw node_num;
	}
	catch (const int& num)
	{
		cout << "리스트가 가득 찼습니다." << endl;
		return;
	}

	// 새로운 노드 동적할당
	NODE* p = new NODE;
	p->next = NULL;
	p->data = data;

	// 처음 노드 생성할 때
	if (head == NULL) {
		head = p;
	}
	else {
		// 맨 위 입력
		if (m == '+') {
			TailNode()->next = p;
		}
		// 맨 아래 입력
		else if (m == 'e') {
			p->next = head;
			head = p;
		}
	}

	node_num++;
}

NODE* ListCommad::SearchNode(POS data, NODE* p)
{
	if (p == NULL) {
		p = head;
	}

	// 만약 삭제할 데이터가 head면
	if ((p->data.x == data.x) && (p->data.y == data.y) && (p->data.z == data.z)) {
		if(p->next == NULL)
			return p;
	}

	// 같으면 리턴
	if ((p->next->data.x == data.x) && (p->next->data.y == data.y) && (p->next->data.z == data.z)) {
		if (p->next->next == NULL)
			return p;
	}

	p = p->next;
	return SearchNode(data, p);
}

void ListCommad::DeleteNode(const char& m)
{
	try {
		if (head == NULL) throw 0;
	}
	catch (const int& n) {
		return;
	}

	// 맨 위
	if (m == '-') {
		// 삭제할 노드 이전의 노드 저장
		NODE* pridel = SearchNode(TailNode()->data, NULL);

		if ((pridel == head) && pridel->next == NULL) {
			head = NULL;
			delete pridel;
		}
		else {
			NODE* temp = pridel->next;
			pridel->next = NULL;
			delete temp;
		}
	}
	// 맨 아래
	else if (m == 'd') {
		NODE* temp = head;
		head = temp->next;
		temp->next = NULL;

		delete temp;
	}

	node_num--;
}

void ListCommad::ClearList()
{
	while (head)
		DeleteNode('d');
}

void ListCommad::CompareDis(const char& m)
{
	if (head) {
		NODE* p;

		int max = 0;
		int min = 1'000'000;
		NODE* max_node = NULL;
		NODE* min_node = NULL;
		int dis = 0;

		for (p = head; p->next != NULL; p = p->next) {
			// 거리
			dis = (p->data.x) * (p->data.x) + (p->data.y) * (p->data.y) + (p->data.z) * (p->data.z);
			if (dis > max) {
				max = dis;
				max_node = p;
			}
			if (dis < min) {
				min = dis;
				min_node = p;
			}
		}
		// 거리
		dis = (p->data.x) * (p->data.x) + (p->data.y) * (p->data.y) + (p->data.z) * (p->data.z);
		if (dis > max) {
			max = dis;
			max_node = p;
		}
		if (dis < min) {
			min = dis;
			min_node = p;
		}

		if (m == 'm')
			cout << "(" << max_node->data.x << ", " << max_node->data.y << ", " << max_node->data.z << ")" << endl;
		else if (m == 'n')
			cout << "(" << min_node->data.x << ", " << min_node->data.y << ", " << min_node->data.z << ")" << endl;
	}
}

void ListCommad::BubbleAscending()
{
	for (NODE* p = head; p != NULL; p = p->next) {
		int dis1 = (p->data.x) * (p->data.x) + (p->data.y) * (p->data.y) + (p->data.z) * (p->data.z);
		for (NODE* q = p->next; q != NULL; q = q->next) {
			int dis2 = (q->data.x) * (q->data.x) + (q->data.y) * (q->data.y) + (q->data.z) * (q->data.z);
			// 왼쪽 수가 오른쪽 보다 크면 값 교환
			if (dis1 > dis2) {
				POS tmp = { p->data.x, p->data.y, p->data.z };
				p->data = { q->data.x, q->data.y, q->data.z };
				q->data = { tmp.x, tmp.y, tmp.z };

				// 값이 변하면 다시
				dis1 = (p->data.x) * (p->data.x) + (p->data.y) * (p->data.y) + (p->data.z) * (p->data.z);
			}
		}
	}
}

void ListCommad::BubbleDescending()
{
	for (NODE* p = head; p != NULL; p = p->next) {
		int dis1 = (p->data.x) * (p->data.x) + (p->data.y) * (p->data.y) + (p->data.z) * (p->data.z);
		for (NODE* q = p->next; q != NULL; q = q->next) {
			int dis2 = (q->data.x) * (q->data.x) + (q->data.y) * (q->data.y) + (q->data.z) * (q->data.z);
			// 오른쪽 수가 왼쪽 보다 크면 값 교환
			if (dis1 < dis2) {
				POS tmp = { p->data.x, p->data.y, p->data.z };
				p->data = { q->data.x, q->data.y, q->data.z };
				q->data = { tmp.x, tmp.y, tmp.z };

				// 값이 변하면 다시
				dis1 = (p->data.x) * (p->data.x) + (p->data.y) * (p->data.y) + (p->data.z) * (p->data.z);
			}
		}
	}
}

ListCommad& ListCommad::operator=(const ListCommad& c)
{
	// 동적할당
	while (this->head)
		DeleteNode('d');

	NODE* p = NULL;
	for (p = c.head; p != NULL; p = p->next) {
		InsertNode(p->data, '+');
	}

	return *this;
}


// 원래 노드 저장
ListCommad copy;
bool is_a = false;
bool is_s = false;

int CheckCommand(ListCommad& c)
{
	char m;
	cout << "command : ";
	cin >> m;

	switch (m) {
	case 'd':
	case 'D':
		c.DeleteNode('d');

		// 정렬 후 삭제하거나 추가 후에는 되돌리기 X
		if (is_a)	is_a = false;
		if (is_s)	is_s = false;
		break;
	case 'e':
	case 'E':
	{
		POS p;
		cin >> p.x >> p.y >> p.z;
		c.InsertNode(p, 'e');

		if (is_a)	is_a = false;
		if (is_s)	is_s = false;
	}
	break;
	case 'l':
	case 'L':
		c.GetListNum();
		break;
	case 'c':
	case 'C':
		c.ClearList();
	break;
	case 'm':
	case 'M':
		c.CompareDis('m');
		break;
	case 'n':
	case 'N':
		c.CompareDis('n');
		break;
	case 'a':
	case 'A':
	{
		if (!is_a) {
			copy = c;
			c.BubbleAscending();
			is_a = true;
		}
		else {
			c = copy;
			is_a = false;
		}
	}
		break;
	case 's':
	case 'S':
	{
		if (!is_s) {
			copy = c;
			c.BubbleDescending();
			is_s = true;
		}
		else {
			c = copy;
			is_s = false;
		}
	}
		break;
	case '+':
	{
		POS p;
		cin >> p.x >> p.y >> p.z;
		c.InsertNode(p, '+');

		if (is_a)	is_a = false;
		if (is_s)	is_s = false;
	}
		break;
	case '-':
		c.DeleteNode('-');
		if (is_a)	is_a = false;
		if (is_s)	is_s = false;
		break;
	case 'q':
	case 'Q':
		cout << "프로그램이 종료됩니다." << endl;
		return 0;
	default:
		cout << "존재하지 않는 명령어 입니다. 다시 입력해주세요" << endl;
		break;
	}

	return 1;
}

int main()
{
	ListCommad c;

	while (1) {
		c.PrintList();

		if (!CheckCommand(c)) break;
	}
}