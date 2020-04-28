#pragma once
class Interface {
public:
	virtual~Interface() {};

	virtual int sum(int a,int b) = 0;

};