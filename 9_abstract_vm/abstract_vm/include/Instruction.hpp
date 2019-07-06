#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

class Instruction {

public:
	Instruction(void);
	virtual ~Instruction(void);
	Instruction(const Instruction &) = delete;
	Instruction & operator=(const Instruction &) = delete;

private:

	virtual void 	isValid(void) const = 0;
	virtual void 	execute(void) const = 0;
};

#endif
