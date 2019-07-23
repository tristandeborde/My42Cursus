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

	typedef IInstruction * (InstructionFactory::* t_builder) (void);

	~InstructionFactory(void);
	InstructionFactory(void);
	InstructionFactory(const InstructionFactory &) = delete;
	InstructionFactory & operator=(const InstructionFactory &) = delete;

	IInstruction * createInstruction (TokenType const);

private:
	IInstruction * createExit( void );
	IInstruction * createDump( void );
	IInstruction * createPop( void );
	IInstruction * createAdd( void );
	IInstruction * createSub( void );
	IInstruction * createMul( void );
	IInstruction * createDiv( void );
	IInstruction * createMod( void );
	IInstruction * createPrint( void );

	IInstruction * createPush( void );
	IInstruction * createAssert( void );

	static t_builder p_builders[static_cast<int>(TokenType::COUNT)];
};

#endif
