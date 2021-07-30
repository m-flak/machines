#pragma once

#include "ctl/pvector.hpp"
#include "machlog/machine.hpp"
#include "machlog/squad.hpp"
#include "machlog/strategy.hpp"

template<class Operation>
class MachLog1stPersonOpDispatch
{
public:
    explicit MachLog1stPersonOpDispatch(MachLogSquadron** ppSquad)
    {
        ppSquad_ = ppSquad;
    }
    ~MachLog1stPersonOpDispatch() {}

    // YO!: The first parameter of an operation, pActor, is handled internally.
    template<typename ...OperationArgs>
    void dispatchOperation(OperationArgs... args) const
    {
        MachLogSquadron* dispatchTo = *ppSquad_;

        if (dispatchTo == nullptr)
        {
            return;
        }
        if (dispatchTo->machines().size() == 0)
        {
            return;
        }

        // The Player-controlled machine will not be in this list. It is removed while in 1st person.
        for (auto machine : dispatchTo->machines())
        {
            // DON'T PANIC! MachLogStrategy is responsible for Operation disposal.
            machine->strategy().newOperation(new Operation(machine, args...));
        }
    }

private:
    MachLogSquadron** ppSquad_;
};
