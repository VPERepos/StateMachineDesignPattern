#pragma once
#include <vector>
#include <memory>
class cData
{
public:
    cData(){};
    ~cData(){};
    std::vector<std::string> m_vGuestBook;
    bool bChangeState = true;
    size_t nPreviousRandomNumber=1;
};

class cState
{
public:
    cState( ){};
    void AddPossibleNextStates( const std::shared_ptr<cState>& spPossibleNextState );
    std::shared_ptr<cState> ReturnNextState() const;
    virtual void ExecuteStateTask(){};
    void SetDataPointer( const std::shared_ptr<cData>& spData );
protected:
    std::shared_ptr<cData> m_spData;
    std::vector<std::shared_ptr<cState>> m_spPossibleNextStates;
    std::shared_ptr<cState> m_spNextState;
};

class cState1 : public cState
{
public:
    void ExecuteStateTask() override;
};

class cState2 : public cState
{
    void ExecuteStateTask() override;
};

class cState3 : public cState
{
    void ExecuteStateTask() override;
};

class cState4 : public cState
{
    void ExecuteStateTask() override;
};