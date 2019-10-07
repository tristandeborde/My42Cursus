#include <iostream>
#include <functional>

#include "MainMonad.class.hpp"

#include "exceptions/Exception.class.hpp"

void MainMonad::add(const std::function<void (void)> &init,
  const std::function<void (void)>					 &end) {
	this->_funcs.push_back(std::make_pair(init, end));
}

int	MainMonad::run(const std::function<void (void)> &entrypoint) const{
	size_t i = 0;
	int	ret	 = 0;

	// setup
	for (; i < this->_funcs.size(); ++i) {
		try {
			(this->_funcs[static_cast<size_t>(i)].first)();
		}
		catch (const Exception & exc) {
			std::cerr << exc.what() << std::endl;
			ret = 1;
			break;
		}
	}

	// if all good
	if (i == this->_funcs.size()) {
		try {
			entrypoint();
		}
		catch (const Exception & exc) {
			std::cerr << exc.what() << std::endl;
			ret = 2;
		}
	}

	// cleanup if needeed
	if (i != 0) {
		do {
			--i;
			try {
				(this->_funcs[static_cast<size_t>(i)].second)();
			}
			catch (const Exception & exc) {
				std::cerr << exc.what() << std::endl;
				ret = 3;
			}
		} while (i != 0);
	}

	return (ret);
}	// MainMonad::run
