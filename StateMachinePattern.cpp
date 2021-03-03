#include "StateMachinePattern.h"
#include <time.h>

void State::addPossibleNextStates( const std::shared_ptr<State>& spPossibleNextState )
{
    spPossibleNextStates.push_back( spPossibleNextState );
}

std::shared_ptr<State> State::returnNextState() const
{
    return spNextState;
}

void State::setDataPointer( const std::shared_ptr<Data>& spData )
{
    this->spData = spData;
}

void State::setStatusPointer( const std::shared_ptr<Status>& spStatus )
{
    this->spStatus = spStatus;
}

void State1::executeStateTask()
{
    spData->vGuestBook.push_back( "State 1 was here" );
    spStatus->setStatusMessage("STM: Executing state 1");
    
    size_t nRsandNum = ( rand() % 4 ) + 1;
    
    while(spData->nPreviousRandomNumber == nRsandNum )
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    spData->nPreviousRandomNumber = nRsandNum;

    spNextState = spPossibleNextStates[nRsandNum-1];
}

void State2::executeStateTask()
{
    spData->vGuestBook.push_back( "State 2 was here" );
    spStatus->setStatusMessage("STM: Executing state 2");
    
    size_t nRsandNum = ( rand() % 4 ) + 1;

    while(spData->nPreviousRandomNumber == nRsandNum )
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    spData->nPreviousRandomNumber = nRsandNum;

    spNextState = spPossibleNextStates[nRsandNum-1];
}

void State3::executeStateTask()
{
    spData->vGuestBook.push_back( "State 3 was here" );
    spStatus->setStatusMessage("STM: Executing state 3");
    
    size_t nRsandNum = ( rand() % 4 ) + 1;

    while(spData->nPreviousRandomNumber == nRsandNum)
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    spData->nPreviousRandomNumber = nRsandNum;
    
    if(nRsandNum == 4)
    {
        spStatus->setStatus(false);
        spStatus->setStatusMessage("STM ERROR: Transition from state 3 to State 4 is forbidden!");
        spData->bChangeState = false;
        spNextState = spPossibleNextStates[1];
    }
    else
    {
        spNextState = spPossibleNextStates[nRsandNum-1];
    }
    
}

void State4::executeStateTask()
{
    spData->vGuestBook.push_back( "State 4 was here" );
    spStatus->setStatusMessage("STM: Executing state 4");
    spStatus->setStatusMessage("STM: Execution is successfull"); 
    spData->bChangeState = false;
    
}

StateMachine::StateMachine(const std::shared_ptr<Data>& spData, const std::shared_ptr<Status>& spStatus):
spData(spData), spStatus(spStatus)
{
    spActualState = std::shared_ptr<State>( new State1 );
    spNextState = std::shared_ptr<State>( new State1 );

    spState1 = std::shared_ptr<State>( new State1 );
    spState2 = std::shared_ptr<State>( new State2 );
    spState3 = std::shared_ptr<State>( new State3 );
    spState4 = std::shared_ptr<State>( new State4 );

    spState1->setDataPointer( spData );
    spState2->setDataPointer( spData );
    spState3->setDataPointer( spData );
    spState4->setDataPointer( spData );

    spState1->setStatusPointer( spStatus );
    spState2->setStatusPointer( spStatus );
    spState3->setStatusPointer( spStatus );
    spState4->setStatusPointer( spStatus );

    spState1->addPossibleNextStates( spState1 );
    spState1->addPossibleNextStates( spState2 );
    spState1->addPossibleNextStates( spState3 );
    spState1->addPossibleNextStates( spState4 );

    spState2->addPossibleNextStates( spState1 );
    spState2->addPossibleNextStates( spState2 );
    spState2->addPossibleNextStates( spState3 );
    spState2->addPossibleNextStates( spState4 );

    spState3->addPossibleNextStates( spState1 );
    spState3->addPossibleNextStates( spState2 );
    spState3->addPossibleNextStates( spState3 );

    spActualState = spState1;  
    spNextState = spState1;
    
    srand( (unsigned)time(NULL) );
    
    spStatus->setStatusMessage("STM: State machine is initialized");  
}

void StateMachine::runSTM()
{
    spStatus->setStatusMessage("STM: Starting execution"); 
    while (checkForChangingState())
    {
        changeState();
    }
};

void StateMachine::changeState()
{
    spActualState = spNextState;
    spActualState->executeStateTask();
    spNextState = spActualState->returnNextState();
}

bool StateMachine::checkForChangingState()
{
    return spData->bChangeState && spStatus->getStatus();
}
Status::Status()
{
    spExecMessage = std::make_shared<std::vector<std::string>>();
};

void Status::setStatusMessage(const std::string& sStatusMessage)
{
    spExecMessage->push_back(sStatusMessage);
};

void Status::setStatus(const bool& bExecStatus)
{
    bExecutionStatus = bExecStatus;
};

std::shared_ptr<std::vector<std::string>> Status::getStatusMessage() const
{
    return spExecMessage;
};

bool Status::getStatus() const
{
    return bExecutionStatus;
}