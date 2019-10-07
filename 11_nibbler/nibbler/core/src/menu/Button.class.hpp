#ifndef BUTTON_CLASS_HPP
#define	BUTTON_CLASS_HPP

#include <string>
#include <functional>
#include "libmedia_interface.hpp"

typedef struct s_button t_button;

class Button
{
	/* Typedefs *******************************************************************/
	public:
		using t_callback = std::function<void(void)>;

	/* Instantiation **************************************************************/
	public:
		explicit Button(t_callback _action, std::string _title = "Button");
		Button(Button const &src) = default;
		~Button(void) = default;

		Button  &operator=(Button const &rhs) = default;

	/* Button methods ***************************************************************/
	public:
		t_button	serialize(void) const;

	/* Attributes *****************************************************************/
	public:
		std::string	title;
		t_callback action;
};

#endif	// ifndef BUTTON_CLASS_HPP
