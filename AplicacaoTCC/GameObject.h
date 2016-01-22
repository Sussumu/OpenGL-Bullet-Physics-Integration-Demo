#pragma once

class GameObject
{
public:

	GameObject();
	~GameObject();

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

private:


};

