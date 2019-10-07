#ifndef GRAPHICS_LOADER_EXCEPTION_CLASS_HPP
#define	GRAPHICS_LOADER_EXCEPTION_CLASS_HPP

#include "Exception.class.hpp"

class GraphicsLoaderException: public Exception {
	public:
		explicit GraphicsLoaderException(const std::string &);
		~GraphicsLoaderException() override;

		GraphicsLoaderException() = delete;
		GraphicsLoaderException(const GraphicsLoaderException &) noexcept;
		GraphicsLoaderException &operator=(const GraphicsLoaderException &) = default;
};

#endif	// ifndef GRAPHICS_LOADER_EXCEPTION_CLASS_HPP
