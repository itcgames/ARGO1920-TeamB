#pragma once

class MoveCommand {
public:
	virtual ~MoveCommand() {}
	virtual void execute() = 0;
protected:
	MoveCommand() {}
};

class moveUp : public MoveCommand {
public:
	virtual void execute() override {

	}
};

