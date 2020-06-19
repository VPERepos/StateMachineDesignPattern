#include "StateMachinePattern.h"
#include <time.h>
#include <iostream>
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

void cState1::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "cState1 was here" );
    
    srand( (unsigned)time(NULL) );
    size_t nRsandNum = ( rand() % 4 ) + 1;
    
    while(m_spData->nPreviousRandomNumber == nRsandNum )
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    m_spData->nPreviousRandomNumber = nRsandNum;

    std::cout << "State 1" << std::endl;
    m_spNextState = m_spPossibleNextStates[nRsandNum-1];
}

void cState2::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "cState2 was here" );
    
    srand( (unsigned)time(NULL) );
    size_t nRsandNum = ( rand() % 4 ) + 1;

    while(m_spData->nPreviousRandomNumber == nRsandNum )
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    m_spData->nPreviousRandomNumber = nRsandNum;

    std::cout << "State 2" << std::endl;
    m_spNextState = m_spPossibleNextStates[nRsandNum-1];
}

void cState3::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "cState3 was here" );
    
    srand( (unsigned)time(NULL) );
    size_t nRsandNum = ( rand() % 4 ) + 1;

    while(m_spData->nPreviousRandomNumber == nRsandNum)
    {
        nRsandNum = ( rand() % 4 ) + 1;
    }
     
    m_spData->nPreviousRandomNumber = nRsandNum;

    std::cout << "State 3" << std::endl;
    m_spNextState = m_spPossibleNextStates[nRsandNum-1];
}

void cState4::ExecuteStateTask()
{
    m_spData->m_vGuestBook.push_back( "Stop changing states" );
    m_spData->bChangeState = false;
    std::cout << "End State" << std::endl;
}