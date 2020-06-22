# State Machine Design Pattern in modern C++

## Motivation
Working several years as a firmware developer for FPGA-systems, where the whole business logic must be  implemented in the form of a state machine, I really got used to them and found it later on very practical also for C++ programming. A lot of algorithms, like for example text parsing, have this kind of non-linear flow with transitions and abortions, where the state machines are, may be, the best design choice. I adopted the idea of the class polymorphism (underlying in almost all design patterns, except for singleton as to my knowledge) to a state machine and implemented it in terms of the modern C++. This kind of software design was also applied for my real life programming problems, like non-XML text protocol parser.

## Classes structure and functionality

```plantuml
@startuml

class cData{
    +m_vGuestBook
    +bChangeState = true
    +nPreviousRandomNumber=1
}

class cStatus{
    +SetStatus()
    +SetStatusMessage()
    +GetStatus()
    +GetStatusMessage()
    -m_bExecutionStatus = true
    -m_spExecMessage
}

class cStateMachine{
    -m_spData
    -m_spStatus
    -m_spActualState
    -m_spNextState
    -m_spState1
    -m_spState2
    -m_spState3
    -m_spState4
    +RunSTM()
}

class cState{
    #m_spData
    #m_spStatus
    #m_spPossibleNextStates
    #m_spNextState
    +AddPossibleNextStates()
    +ReturnNextState()
    {abstract}+ExecuteStateTask()
    +SetDataPointer()
    +SetStatusPointer()
}
class cState1{
    +ExecuteStateTask()
}
class cState2{
    +ExecuteStateTask()
}
class cState3{
    +ExecuteStateTask()
}
class cState4{
    +ExecuteStateTask()
}

cState <|-- cState1
cState <|-- cState2
cState <|-- cState3
cState <|-- cState4

cStateMachine *-- cData
cStateMachine *-- cStatus
cStateMachine *-- cState1
cStateMachine *-- cState2
cStateMachine *-- cState3
cStateMachine *-- cState4

@enduml
```
UML-diagram above represents the design of the example program. There is a class called cStateMachine, which consists of shared pointers to the objects of the classes cData, cStatus and cState1 to cState4. The shared pointers of types cStatus and cData are passed by parameters of the constructor of the cStateMachine class. The objects of cState1 to cState4 types are allocated on heap in this constructor. Objects of types cData, cStatus and cStateMachine are allocated on heap in main function. Transitions of the state machine, made possible by derivation from the base class cState, are implemented in the function RunSTM(). They are dependent on the results of the business logic of each state, but there is only one main loop, which runs until exit is initiated. In common, the states can be filled with custom business logic, but in this example a random number is generated, which represents the next state and main loop executes the next state in the next iteration. The execution stops ordinary in the 4-th state and with an error during transition from the 3-rd to the 4-th state. It is implemented this way only in order to show the principle. Generally, as mentioned above, this design can be configured to work in any way, depending on needs.