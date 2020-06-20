#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class cData
{
public:
    cData(){};
    ~cData(){};
    std::vector<std::string> m_vGuestBook;
    bool bChangeState = true;
    size_t nPreviousRandomNumber=1;
};

class cStatus
{
public:
    cStatus();
    ~cStatus(){};
    void SetStatus(const bool& bExecStatus);
    void SetStatusMessage(const std::string& sStatusMessage);
    bool GetStatus() const;
    std::shared_ptr<std::vector<std::string>> GetStatusMessage()const;
private:
    bool m_bExecutionStatus = true;
    std::shared_ptr<std::vector<std::string>> m_spExecMessage;
};
class cState
{
public:
    cState( ){};
    virtual ~cState( ){};
    void AddPossibleNextStates( const std::shared_ptr<cState>& spPossibleNextState );
    std::shared_ptr<cState> ReturnNextState() const;
    virtual void ExecuteStateTask(){};
    void SetDataPointer( const std::shared_ptr<cData>& spData );
    void SetStatusPointer( const std::shared_ptr<cStatus>& spStatus );
protected:
    std::shared_ptr<cData> m_spData;
    std::shared_ptr<cStatus> m_spStatus;
    std::vector<std::shared_ptr<cState>> m_spPossibleNextStates;
    std::shared_ptr<cState> m_spNextState;
};

class cState1 : public cState
{
public:
    ~cState1()override {};
    void ExecuteStateTask() override;
};

class cState2 : public cState
{
public:
    ~cState2()override {};
    void ExecuteStateTask() override;
};

class cState3 : public cState
{
public:
    ~cState3()override {};
    void ExecuteStateTask() override;
};

class cState4 : public cState
{
public:
    ~cState4()override {};
    void ExecuteStateTask() override;
};

class cStateMachine
{
public: 
    cStateMachine(const std::shared_ptr<cData>& spData, const std::shared_ptr<cStatus>& spStatus);
    ~cStateMachine(){};
    void RunSTM();
private:
    std::shared_ptr<cData> m_spData;   
    std::shared_ptr<cStatus> m_spStatus; 
    
    std::shared_ptr<cState> m_spActualState;
    std::shared_ptr<cState> m_spNextState;

    std::shared_ptr<cState> m_spState1;
    std::shared_ptr<cState> m_spState2;
    std::shared_ptr<cState> m_spState3;
    std::shared_ptr<cState> m_spState4;
};