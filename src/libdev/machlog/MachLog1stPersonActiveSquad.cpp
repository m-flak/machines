#include <utility>
#include "machlog/MachLog1stPersonActiveSquad.hpp"

#include "ctl/pvector.hpp"
#include "machlog/cntrl_pc.hpp"
#include "machlog/races.hpp"
#include "machlog/administ.hpp"

MachLog1stPersonActiveSquadron::MachLog1stPersonActiveSquadron(MachLogSquadron* initialActiveSquad)
{
    pActiveSquadron_ = initialActiveSquad;
}

MachLog1stPersonActiveSquadron::MachLog1stPersonActiveSquadron()
    : MachLog1stPersonActiveSquadron(nullptr)
{

}

MachLog1stPersonActiveSquadron::~MachLog1stPersonActiveSquadron()
{

}

MachLog1stPersonActiveSquadron::MachLog1stPersonActiveSquadron(MachLog1stPersonActiveSquadron&& other)
{
    pActiveSquadron_ = std::move(other.pActiveSquadron_);
}

MachLog1stPersonActiveSquadron& MachLog1stPersonActiveSquadron::operator=(MachLog1stPersonActiveSquadron&& other)
{
    if (this != &other)
    {
        pActiveSquadron_ = std::move(other.pActiveSquadron_);
    }

    return *this;
}

bool MachLog1stPersonActiveSquadron::hasActiveSquadron() const
{
    return ( (pActiveSquadron_ != nullptr) );
}

int64_t MachLog1stPersonActiveSquadron::getActiveSquadronId() const
{
    int64_t id = 0;

    if (hasActiveSquadron())
    {
        id = pActiveSquadron_->squadronId();
    }

    return id;
}

MachLogMachine* const MachLog1stPersonActiveSquadron::getLeadingMachine() const
{
    if (not hasActiveSquadron())
    {
        return nullptr;
    }

    if (pActiveSquadron_->hasCommander())
    {
        return &pActiveSquadron_->commander();
    }

    return pActiveSquadron_->getStrongestMachine();
}

void MachLog1stPersonActiveSquadron::setActiveSquadron(size_t squadIndex)
{
    MachLogRaces& races = MachLogRaces::instance();
    MachPhys::Race race = races.pcController().race();

    // Optionally set the squad so that empty ones may skipped over by player
    auto squad = races.squadrons(race)[squadIndex];
    if (squad->machines().size() > 0)
    {
        pActiveSquadron_ = squad;
    }
}

void MachLog1stPersonActiveSquadron::clearActiveSquadron()
{
    pActiveSquadron_ = nullptr;
}
