#include "Processor.hpp"

Processor::Processor(void) {
	return;
}

Processor::Processor(const Processor &) {
	*this = src;
	return;
}

Processor::~Processor(void) {
	return;
}

Processor & Processor::operator=(const Processor &) {
	return *this;
}

