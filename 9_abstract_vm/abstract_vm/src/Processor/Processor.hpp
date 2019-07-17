#ifndef PROCESSOR_HPP
# define PROCESSOR_HPP

// Takes a sequence of IInstruction objects as input and executes them on a stack.

class Processor {

public:

	Processor(void);
	Processor(const Processor &);
	~Processor(void);
	Processor & operator=(const Processor &);

private:

};

#endif
