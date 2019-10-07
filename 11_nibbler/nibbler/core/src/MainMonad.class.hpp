#ifndef MAINMONAD_CLASS_HPP
#define	MAINMONAD_CLASS_HPP

#include <functional>
#include <vector>

/**
 *	This monad prevents from failures, and frees resources that are used
 *	by other namespaces. If the init of a resource crash early,
 *	all the previous resources will be freed.
 *
 *	At the moment of this write, we have 4 resources in order:
 *		- Logger
 *		- Core
 *		- GraphicsLoader
 *		- MapBuilder
 *	If any X::init crashes somehow, each X::end will be called,
 *	then all resources will be freed correctly, whatever the moment it crashes,
 *	even if no crash happens.
 *
 *	We consider a crash as throwing an Exception.
 */
class MainMonad final
{
	/* Typedefs *******************************************************************/
	using t_init_end_funcs = std::pair<std::function<void(void)>, std::function<void(void)> >;

	/* Instantiation *************************************************************/
	public:
		MainMonad()	 = default;
		~MainMonad() = default;

		MainMonad & operator=(MainMonad const &src) = delete;
		MainMonad(MainMonad const &src) = delete;

	/* Methods ***************************************************************/
	public:
		void		add(const std::function<void (void)> &init,
			const std::function<void (void)>			 &end);
		int			run(const std::function<void (void)> &entrypoint) const;

	/* Attributes ************************************************************/
	private:
		std::vector<t_init_end_funcs> _funcs {};
};

#endif	// ifndef MAINMONAD_CLASS_HPP
