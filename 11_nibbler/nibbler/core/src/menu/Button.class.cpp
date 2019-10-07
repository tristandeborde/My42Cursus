#include "Button.class.hpp"

#include "libmedia_interface.hpp"

/* Instantiation **************************************************************/
Button::Button(Button::t_callback _action, std::string _title)
	: title(std::move(_title)), action(std::move(_action))
{}

/* Button methods ***************************************************************/
t_button Button::serialize(void) const{
	t_button res;

	res.title = this->title.c_str();

	return res;
}
