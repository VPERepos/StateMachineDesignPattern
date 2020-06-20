#include "StateMachinePattern.h"

int main()
{
    
    auto spData{ std::make_shared<cData>() };
    auto spExecStatus{ std::make_shared<cStatus>() };
    auto spSTM{ std::make_unique<cStateMachine>(spData, spExecStatus) };

    spSTM->RunSTM();
    
    auto ResultingStatus = spExecStatus->GetStatusMessage();
    for(auto Message : *(ResultingStatus.get()) )
    {
        std::cout << Message << std::endl;
    }
    return 0;

}