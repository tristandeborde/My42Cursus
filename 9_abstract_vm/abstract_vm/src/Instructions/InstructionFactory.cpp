#include "Instructions/InstructionFactory.hpp"

InstructionFactory::InstructionFactory(void) {
    return;
}

InstructionFactory::~InstructionFactory(void) {
    return;
}

IInstruction const * InstructionFactory::createExit( void ) {
    IInstruction const * instru = new InstructionExit();
    return instru;
}
IInstruction const * InstructionFactory::createDump( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createPop( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createAdd( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createSub( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createMul( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createDiv( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createMod( void ) {
    return NULL;
}
IInstruction const * InstructionFactory::createPrint( void ) {
    return NULL;
}

IInstruction const * InstructionFactory::createPush( void ) {
    IInstruction const * instru = new InstructionPush();
    return instru;
}
IInstruction const * InstructionFactory::createAssert( void ) {
    return NULL;
}

IInstruction const * InstructionFactory::createInstruction (TokenType const type) {
    t_builder p_builders[static_cast<int>(TokenType::COUNT)] = {
        &InstructionFactory::createExit,
        &InstructionFactory::createDump,
        &InstructionFactory::createPush,
        &InstructionFactory::createPop,
        &InstructionFactory::createAssert,
        &InstructionFactory::createAdd,
        &InstructionFactory::createSub,
        &InstructionFactory::createMul,
        &InstructionFactory::createDiv,
        &InstructionFactory::createMod,
        &InstructionFactory::createPrint,
    };

    return ( (this->*(p_builders[static_cast<int>(type)])) () );
}
