#ifndef AINSTRUCTION_HPP
# define AINSTRUCTION_HPP

class IInstruction {

public:

	virtual ~IInstruction(void) {};

	virtual bool check() = 0;
	virtual void run() = 0;

private:

};

#endif
