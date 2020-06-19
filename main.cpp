#include "StateMachinePattern.h"

int main()
{
    
    auto spData{ std::make_shared<cData>() };
    auto spState1{ std::shared_ptr<cState>( new cState1 ) };
    auto spState2{ std::shared_ptr<cState>( new cState2 ) };
    auto spState3{ std::shared_ptr<cState>( new cState3 ) };
    auto spState4{ std::shared_ptr<cState>( new cState4 ) };

    spState1->SetDataPointer( spData );
    spState2->SetDataPointer( spData );
    spState3->SetDataPointer( spData );
    spState4->SetDataPointer( spData );

    spState1->AddPossibleNextStates( spState1 );
    spState1->AddPossibleNextStates( spState2 );
    spState1->AddPossibleNextStates( spState3 );
    spState1->AddPossibleNextStates( spState4 );

    spState2->AddPossibleNextStates( spState1 );
    spState2->AddPossibleNextStates( spState2 );
    spState2->AddPossibleNextStates( spState3 );
    spState2->AddPossibleNextStates( spState4 );

    spState3->AddPossibleNextStates( spState1 );
    spState3->AddPossibleNextStates( spState2 );
    spState3->AddPossibleNextStates( spState3 );
    spState3->AddPossibleNextStates( spState4 );
    
    auto spActualSate{ std::shared_ptr<cState>( new cState1 ) };
    spActualSate = spState1;
    
    auto spNextSate{ std::shared_ptr<cState>( new cState1 ) };
    spNextSate = spState1;
    
    while ( spData->bChangeState )
    {
        spActualSate = spNextSate;
        spActualSate->ExecuteStateTask();
        spNextSate = spActualSate->ReturnNextState();
    }
    return 0;

}