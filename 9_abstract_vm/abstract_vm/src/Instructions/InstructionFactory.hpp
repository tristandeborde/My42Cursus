#ifndef INSTRUCTIONFACTORY_HPP
# define INSTRUCTIONFACTORY_HPP

# include "Lexer/TokenType.hpp"
# include "Instructions/IInstruction.hpp"
# include "Instructions/InstructionPush.hpp"
# include "Instructions/InstructionExit.hpp"
# include "Instructions/InstructionAssert.hpp"
# include "Instructions/InstructionDump.hpp"
# include "Instructions/InstructionPop.hpp"
# include "Instructions/InstructionAdd.hpp"
# include "Instructions/InstructionSub.hpp"
# include "Instructions/InstructionMul.hpp"
# include "Instructions/InstructionDiv.hpp"
# include "Instructions/InstructionMod.hpp"
# include "Instructions/InstructionPrint.hpp"

class InstructionFactory {

public:

	typedef IInstruction const * (InstructionFactory::* t_builder) (void);

	~InstructionFactory(void);
	InstructionFactory(void);
	InstructionFactory(const InstructionFactory &) = delete;
	InstructionFactory & operator=(const InstructionFactory &) = delete;

	IInstruction const * createInstruction (TokenType const);

private:
	IInstruction const * createExit( void );
	IInstruction const * createDump( void );
	IInstruction const * createPop( void );
	IInstruction const * createAdd( void );
	IInstruction const * createSub( void );
	IInstruction const * createMul( void );
	IInstruction const * createDiv( void );
	IInstruction const * createMod( void );
	IInstruction const * createPrint( void );

	IInstruction const * createPush( void );
	IInstruction const * createAssert( void );

	static t_builder p_builders[static_cast<int>(TokenType::COUNT)];
};

#endif
