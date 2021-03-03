#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
class Data
{
public:
    Data(){};
    ~Data(){};
    std::vector<std::string> vGuestBook;
    bool bChangeState = true;
    size_t nPreviousRandomNumber=1;
};

class Status
{
public:
    Status();
    ~Status(){};
    void setStatus(const bool& bExecStatus);
    void setStatusMessage(const std::string& sStatusMessage);
    bool getStatus() const;
    std::shared_ptr<std::vector<std::string>> getStatusMessage()const;
private:
    bool bExecutionStatus = true;
    std::shared_ptr<std::vector<std::string>> spExecMessage;
};

class State
{
public:
    State( ){};
    virtual ~State( ){};
    void addPossibleNextStates( const std::shared_ptr<State>& spPossibleNextState );
    std::shared_ptr<State> returnNextState() const;
    virtual void executeStateTask(){};
    
    void setDataPointer( const std::shared_ptr<Data>& spData );
    void setStatusPointer( const std::shared_ptr<Status>& spStatus );
protected:
    std::shared_ptr<Data> spData;
    std::shared_ptr<Status> spStatus;
    std::vector<std::shared_ptr<State>> spPossibleNextStates;
    std::shared_ptr<State> spNextState;
};

class State1 : public State
{
public:
    ~State1()override {};
    void executeStateTask() override;
};

class State2 : public State
{
public:
    ~State2()override {};
    void executeStateTask() override;
};

class State3 : public State
{
public:
    ~State3()override {};
    void executeStateTask() override;
};

class State4 : public State
{
public:
    ~State4()override {};
    void executeStateTask() override;
};

class StateMachine
{
public: 
    StateMachine(const std::shared_ptr<Data>& spData, const std::shared_ptr<Status>& spStatus);
    ~StateMachine(){};
    void runSTM();
    void changeState();
    bool checkForChangingState();
private:
    std::shared_ptr<Data> spData;   
    std::shared_ptr<Status> spStatus; 
    
    std::shared_ptr<State> spActualState;
    std::shared_ptr<State> spNextState;

    std::shared_ptr<State> spState1;
    std::shared_ptr<State> spState2;
    std::shared_ptr<State> spState3;
    std::shared_ptr<State> spState4;
};