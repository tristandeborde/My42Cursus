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
    IInstruction const * instru = new InstructionDump();
    return instru;
}
IInstruction const * InstructionFactory::createPop( void ) {
    IInstruction const * instru = new InstructionPop();
    return instru;
}
IInstruction const * InstructionFactory::createAdd( void ) {
    IInstruction const * instru = new InstructionAdd();
    return instru;
}
IInstruction const * InstructionFactory::createSub( void ) {
    IInstruction const * instru = new InstructionSub();
    return instru;
}
IInstruction const * InstructionFactory::createMul( void ) {
    IInstruction const * instru = new InstructionMul();
    return instru;
}
IInstruction const * InstructionFactory::createDiv( void ) {
    IInstruction const * instru = new InstructionDiv();
    return instru;
}
IInstruction const * InstructionFactory::createMod( void ) {
    IInstruction const * instru = new InstructionMod();
    return instru;
}
IInstruction const * InstructionFactory::createPrint( void ) {
    IInstruction const * instru = new InstructionPrint();
    return instru;
}

IInstruction const * InstructionFactory::createPush( void ) {
    IInstruction const * instru = new InstructionPush();
    return instru;
}
IInstruction const * InstructionFactory::createAssert( void ) {
    IInstruction const * instru = new InstructionAssert();
    return instru;
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
