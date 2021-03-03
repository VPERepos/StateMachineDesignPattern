#include "StateMachinePattern.h"

int main()
{
    
    auto spData{ std::make_shared<Data>() };
    auto spExecStatus{ std::make_shared<Status>() };
    auto spSTM{ std::make_unique<StateMachine>(spData, spExecStatus) };

    spSTM->runSTM();
    
    auto resultingStatus = spExecStatus->getStatusMessage();
    for(auto message : *(resultingStatus.get()) )
    {
        std::cout << message << std::endl;
    }
    return 0;

}