#include "machgui/MachGuiFPCommand.hpp"

#include "system/pathname.hpp"
#include "gui/painter.hpp"
#include "machgui/actbmpnm.hpp"
#include "machlog/canattac.hpp"
#include "machlog/machine.hpp"
#include "machlog/MachLog1stPersonActiveSquad.hpp"

MachGuiFPCommand::MachGuiFPCommand( GuiDisplayable* pParent, const Gui::Coord& relPos )
    : GuiDisplayable( pParent, Gui::Box( relPos, 1, 1 ) )
{
    pLogHandler_ = nullptr;
    pActiveSquadIcon_ = &noSquadronSelected();
}

MachGuiFPCommand::~MachGuiFPCommand()
{

}

void MachGuiFPCommand::logHandler( MachLog1stPersonHandler* logHandler)
{
    pLogHandler_ = logHandler;
}

void MachGuiFPCommand::resetLogHandler()
{
    pLogHandler_ = nullptr;
}

void MachGuiFPCommand::updateSquadIcon()
{
    if (not pLogHandler_)
    {
        return;
    }

    MachLogMachine* squadLeader = pLogHandler_->getActiveSquadron().getLeadingMachine();

    if (squadLeader)
    {
        // This is needed for the bitmap name function. )^:?
        MachPhys::WeaponCombo wc = MachPhys::N_WEAPON_COMBOS;
        if ( squadLeader->objectIsCanAttack() )
        {
            wc = squadLeader->asCanAttack().weaponCombo();
        }

        activeSquadIcon_ = Gui::bitmap( MachActorBitmaps::name( squadLeader->objectType(), squadLeader->subType(), squadLeader->asMachine().hwLevel(), wc, squadLeader->race(), true ) );
        pActiveSquadIcon_ = &activeSquadIcon_;
        return;
    }

    // No squad leader? no squad!
    pActiveSquadIcon_ = &noSquadronSelected();
}

void MachGuiFPCommand::clearSquadIcon()
{
    pActiveSquadIcon_ = &noSquadronSelected();
}

//virtual
void MachGuiFPCommand::doDisplay()
{
    // Display widget body, active squad icon, etc...
    const int minX = absoluteBoundary().minCorner().x();
    const int minY = absoluteBoundary().minCorner().y();

    GuiPainter::instance().blit( widgetBody(), Gui::Coord( minX, minY ) );
    GuiPainter::instance().blit( *pActiveSquadIcon_, Gui::Coord( minX+41, minY+52 ) );
}

//static
GuiBitmap& MachGuiFPCommand::noSquadronSelected()
{
    static GuiBitmap blankIcon = Gui::bitmap( SysPathName("gui/fstpersn/machines/backgrnd.bmp" ) );
    return blankIcon;
}

//static
GuiBitmap& MachGuiFPCommand::widgetBody()
{
    static GuiBitmap widget = Gui::bitmap( SysPathName("gui/fstpersn/command/widget.bmp" ) );
    return widget;
}