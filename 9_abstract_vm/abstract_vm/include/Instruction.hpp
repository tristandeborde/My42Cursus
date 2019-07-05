#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

class Instruction {

public:

	virtual ~Instruction(void);

private:

	virtual void 	isValid(void) const = 0;
	virtual void 	execute(void) const = 0;
};

#endif
