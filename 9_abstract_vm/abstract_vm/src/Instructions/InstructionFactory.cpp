#include "Instructions/InstructionFactory.hpp"

InstructionFactory::InstructionFactory(void) {
    return;
}

InstructionFactory::~InstructionFactory(void) {
    return;
}

IInstruction * InstructionFactory::createExit( void ) {
    IInstruction * instru = new InstructionExit();
    return instru;
}
IInstruction * InstructionFactory::createDump( void ) {
    IInstruction * instru = new InstructionDump();
    return instru;
}
IInstruction * InstructionFactory::createPop( void ) {
    IInstruction * instru = new InstructionPop();
    return instru;
}
IInstruction * InstructionFactory::createAdd( void ) {
    IInstruction * instru = new InstructionAdd();
    return instru;
}
IInstruction * InstructionFactory::createSub( void ) {
    IInstruction * instru = new InstructionSub();
    return instru;
}
IInstruction * InstructionFactory::createMul( void ) {
    IInstruction * instru = new InstructionMul();
    return instru;
}
IInstruction * InstructionFactory::createDiv( void ) {
    IInstruction * instru = new InstructionDiv();
    return instru;
}
IInstruction * InstructionFactory::createMod( void ) {
    IInstruction * instru = new InstructionMod();
    return instru;
}
IInstruction * InstructionFactory::createPrint( void ) {
    IInstruction * instru = new InstructionPrint();
    return instru;
}

IInstruction * InstructionFactory::createPush( void ) {
    IInstruction * instru = new InstructionPush();
    return instru;
}
IInstruction * InstructionFactory::createAssert( void ) {
    IInstruction * instru = new InstructionAssert();
    return instru;
}

IInstruction * InstructionFactory::createInstruction (eTokenType const type) {
    t_builder p_builders[static_cast<int>(eTokenType::COUNT)] = {
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
