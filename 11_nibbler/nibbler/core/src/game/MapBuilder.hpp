#ifndef MAPBUILDER_HPP
#define	MAPBUILDER_HPP

#include "Party.class.hpp"

namespace MapBuilder
{
	// (de)allocation funcs
	void	init(void);
	void	end(void);

	void	setMapSize(Party::t_dims dims);
	// generate the map and store the new entities in party
	void	build(Party &party);
}// namespace MapBuilder

#endif	// ifndef MAPBUILDER_HPP
