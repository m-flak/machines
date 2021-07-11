#include <utility>
#include "machlog/MachLog1stPersonActiveSquad.hpp"

#include "ctl/pvector.hpp"
#include "machlog/cntrl_pc.hpp"
#include "machlog/races.hpp"

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
    return (pActiveSquadron_ != nullptr);
}

void MachLog1stPersonActiveSquadron::setActiveSquadron(size_t squadIndex)
{
    MachLogRaces& races = MachLogRaces::instance();
    MachPhys::Race race = races.pcController().race();

    pActiveSquadron_ = races.squadrons(race)[squadIndex];

    std::cerr << "Active Squadron PTR: " << pActiveSquadron_ << std::endl;
}

void MachLog1stPersonActiveSquadron::clearActiveSquadron()
{
    pActiveSquadron_ = nullptr;
}
