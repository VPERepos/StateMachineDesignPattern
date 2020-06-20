#include "StateMachinePattern.h"
#include <time.h>

void cState::AddPossibleNextStates( const std::shared_ptr<cState>& spPossibleNextState )
{
    m_spPossibleNextStates.push_back( spPossibleNextState );
}

std::shared_ptr<cState> cState::ReturnNextState() const
{
    return m_spNextState;
}

void cState::SetDataPointer( const std::shared_ptr<cData>& spData )
{
    m_spData = spData;
}

void cState::SetStatusPointer( const std::shared_ptr<cStatus>& spStatus )
{
    m_spStatus = spStatus;
}

void cState1::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "State 1 was here" );
    m_spStatus->SetStatusMessage("STM: Executing state 1");

    srand( (unsigned)time(NULL) );
    size_t nRsandNum = ( rand() % 4 ) + 1;
    
    while(m_spData->nPreviousRandomNumber == nRsandNum )
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    m_spData->nPreviousRandomNumber = nRsandNum;

    m_spNextState = m_spPossibleNextStates[nRsandNum-1];
}

void cState2::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "State 2 was here" );
    m_spStatus->SetStatusMessage("STM: Executing state 2");
    
    srand( (unsigned)time(NULL) );
    size_t nRsandNum = ( rand() % 4 ) + 1;

    while(m_spData->nPreviousRandomNumber == nRsandNum )
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    m_spData->nPreviousRandomNumber = nRsandNum;

    m_spNextState = m_spPossibleNextStates[nRsandNum-1];
}

void cState3::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "State 3 was here" );
    m_spStatus->SetStatusMessage("STM: Executing state 3");
    srand( (unsigned)time(NULL) );
    size_t nRsandNum = ( rand() % 4 ) + 1;

    while(m_spData->nPreviousRandomNumber == nRsandNum)
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    m_spData->nPreviousRandomNumber = nRsandNum;
    
    if(nRsandNum == 4)
    {
        m_spStatus->SetStatus(false);
        m_spStatus->SetStatusMessage("STM ERROR: Transition from state 3 to State 4 is forbidden!");
        m_spData->bChangeState = false;
        m_spNextState = m_spPossibleNextStates[1];
    }
    else
    {
        m_spNextState = m_spPossibleNextStates[nRsandNum-1];
    }
    
}

void cState4::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "State 4 was here" );
    m_spStatus->SetStatusMessage("STM: Executing state 4");
    m_spStatus->SetStatusMessage("STM: Execution is successfull"); 
    m_spData->bChangeState = false;
    
}

cStateMachine::cStateMachine(const std::shared_ptr<cData>& spData, const std::shared_ptr<cStatus>& spStatus):
m_spData(spData), m_spStatus(spStatus)
{
    m_spActualState = std::shared_ptr<cState>( new cState1 );
    m_spNextState = std::shared_ptr<cState>( new cState1 );

    m_spState1 = std::shared_ptr<cState>( new cState1 );
    m_spState2 = std::shared_ptr<cState>( new cState2 );
    m_spState3 = std::shared_ptr<cState>( new cState3 );
    m_spState4 = std::shared_ptr<cState>( new cState4 );

    m_spState1->SetDataPointer( m_spData );
    m_spState2->SetDataPointer( m_spData );
    m_spState3->SetDataPointer( m_spData );
    m_spState4->SetDataPointer( m_spData );

    m_spState1->SetStatusPointer( m_spStatus );
    m_spState2->SetStatusPointer( m_spStatus );
    m_spState3->SetStatusPointer( m_spStatus );
    m_spState4->SetStatusPointer( m_spStatus );

    m_spState1->AddPossibleNextStates( m_spState1 );
    m_spState1->AddPossibleNextStates( m_spState2 );
    m_spState1->AddPossibleNextStates( m_spState3 );
    m_spState1->AddPossibleNextStates( m_spState4 );

    m_spState2->AddPossibleNextStates( m_spState1 );
    m_spState2->AddPossibleNextStates( m_spState2 );
    m_spState2->AddPossibleNextStates( m_spState3 );
    m_spState2->AddPossibleNextStates( m_spState4 );

    m_spState3->AddPossibleNextStates( m_spState1 );
    m_spState3->AddPossibleNextStates( m_spState2 );
    m_spState3->AddPossibleNextStates( m_spState3 );

    m_spActualState = m_spState1;  
    m_spNextState = m_spState1;

    m_spStatus->SetStatusMessage("STM: State machine is initialized");  
}

void cStateMachine::RunSTM()
{
    m_spStatus->SetStatusMessage("STM: Starting execution"); 
    while ( m_spData->bChangeState && m_spStatus->GetStatus())
    {
        m_spActualState = m_spNextState;
        m_spActualState->ExecuteStateTask();
        m_spNextState = m_spActualState->ReturnNextState();
    }
};

cStatus::cStatus()
{
    m_spExecMessage = std::make_shared<std::vector<std::string>>();
};

void cStatus::SetStatusMessage(const std::string& sStatusMessage)
{
    m_spExecMessage->push_back(sStatusMessage);
};

void cStatus::SetStatus(const bool& bExecStatus)
{
    m_bExecutionStatus = bExecStatus;
};

std::shared_ptr<std::vector<std::string>> cStatus::GetStatusMessage() const
{
    return m_spExecMessage;
};

bool cStatus::GetStatus() const
{
    return m_bExecutionStatus;
}