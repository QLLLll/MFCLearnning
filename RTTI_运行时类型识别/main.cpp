#include <typeinfo>
#include <iostream>
using namespace std;
class B
{
public:
	virtual double fun()
	{
		return 0.1;
	}
};
class D :public B
{
};
int main()
{
	B *p = new D;
	B &r = *p;    //无名对象照样有别名
	cout << (typeid(p) == typeid(B*)); //仅指向子类中父类部分
	cout << (typeid(p) != typeid(D*));  //而非指向整个子类对象
	cout << (typeid(r) == typeid(D));   //引用的类型却是子类的
	cout << (typeid(*p) == typeid(D)); //间址访问的是子类对象
	cout << (typeid(*p) != typeid(B));  //而非父类
	cout << (typeid(&r) == typeid(B*)); //引用的地址是父类的
	cout << (typeid(&r) != typeid(D*));  //而非子类的


	printf("\n%s",typeid(p).name());

	system("pause");

	return 0;
}