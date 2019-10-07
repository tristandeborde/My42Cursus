#ifndef MODELCONFIG_CLASS_HPP
#define	MODELCONFIG_CLASS_HPP

#include "Model.class.hpp"

struct ModelConfig{
	ModelConfig(void) = default;
	ModelConfig(const Model &m, float s);

	Model model;
	float size{};
};

#endif	// #ifndef MODELCONFIG_CLASS_HPP
