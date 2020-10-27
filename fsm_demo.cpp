#include <iostream>
using namespace std;

class State;
class StateOne;
class StateTwo;
class StateThree;

class Fsm
{
public:
	Fsm();
	~Fsm();

	State* GetCurState()
	{
		return state;
	}
	void SetState(State* s)
	{
		state = s;
	}
	void Handle(int input);
private:
	State* state;
};

class State
{
public:
	State() {};
	virtual ~State() {};
	virtual void Handle(Fsm* fsm, int input) = 0;
};

class StateOne : public State
{
private:
	StateOne() {};

	static StateOne* stateOne;

public:
	~StateOne() {};
	static StateOne* GetState();
	void Handle(Fsm* fsm, int input) override;

};

class StateTwo : public State
{
private:
	StateTwo() {};

	static StateTwo* stateTwo;

public:
	~StateTwo() {};
	static StateTwo* GetState();
	void Handle(Fsm* fsm, int input) override;

};

class StateThree : public State
{
private:
	StateThree() {};

	static StateThree* stateThree;

public:
	~StateThree() {};
	static StateThree* GetState();
	void Handle(Fsm* fsm, int input) override;

};

Fsm::Fsm()
{
	state = StateOne::GetState();
}

Fsm::~Fsm()
{
	if (StateOne::GetState() != NULL)
		delete (StateOne::GetState());
	if (StateTwo::GetState() != NULL)
		delete (StateTwo::GetState());
	if (StateThree::GetState() != NULL)
		delete (StateThree::GetState());
}

void Fsm::Handle(int input)
{
	state->Handle(this, input);
}

StateOne* StateOne::stateOne = NULL;
StateOne* StateOne::GetState()
{
	if (stateOne == NULL)
		stateOne = new StateOne;
	return stateOne;
}

void StateOne::Handle(Fsm* fsm, int input)
{
	cout << "StateOne::Handle, input is " << input << endl;
	switch(input)
	{
	case 1:
		cout << "1" << endl;
		break;
	case 2:
		fsm->SetState(StateTwo::GetState());
		break;
	default:
		break;
	}
}

StateTwo* StateTwo::stateTwo = NULL;
StateTwo* StateTwo::GetState()
{
	if (stateTwo == NULL)
		stateTwo = new StateTwo;
	return stateTwo;
}

void StateTwo::Handle(Fsm* fsm, int input)
{
	cout << "StateTwo::Handle, input is " << input << endl;
	switch(input)
	{
	case 1:
		fsm->SetState(StateTwo::GetState());
		break;
	case 2:
		fsm->SetState(StateThree::GetState());
		break;
	default:
		break;
	}
}

StateThree* StateThree::stateThree = NULL;
StateThree* StateThree::GetState()
{
	if (stateThree == NULL)
		stateThree = new StateThree;
	return stateThree;
}

void StateThree::Handle(Fsm* fsm, int input)
{
	cout << "StateThree::Handle, input is " << input << endl;
	switch(input)
	{
	case 1:
		fsm->SetState(StateOne::GetState());
		break;
	case 2:
		cout << "2" << endl;
		break;
	default:
		break;
	}
}


int main() {
	int input;
	Fsm f;

	while(1)
	{
		cin >> input;
		if (input == 1 || input == 2)
			f.Handle(input);
		//cout << "input is " << input << endl;
	}

	return 0;
}
