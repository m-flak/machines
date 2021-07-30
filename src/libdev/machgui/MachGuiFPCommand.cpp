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

    attackCommandState_ = CommandIconState::INVALID;
    followCommandState_ = CommandIconState::INVALID;
    moveCommandState_   = CommandIconState::INVALID;
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

void MachGuiFPCommand::setAttackIconState(CommandIconState state)
{
    attackCommandState_ = state;
}
void MachGuiFPCommand::setFollowIconState(CommandIconState state)
{
    followCommandState_ = state;
}
void MachGuiFPCommand::setMoveIconState(CommandIconState state)
{
    moveCommandState_ = state;
}

//virtual
void MachGuiFPCommand::doDisplay()
{
    // Display widget body, active squad icon, etc...
    const int minX = absoluteBoundary().minCorner().x();
    const int minY = absoluteBoundary().minCorner().y();

    GuiPainter::instance().blit( widgetBody(), Gui::Coord( minX, minY ) );
    GuiPainter::instance().blit( *pActiveSquadIcon_, Gui::Coord( minX+41, minY+52 ) );

    // widget.bmp: 130x130
    // the command icons: 64x24
    int state = static_cast<int>(moveCommandState_);
    GuiPainter::instance().blit( moveCommandIcons()[state], Gui::Coord( minX, minY+130 ) );
    state = static_cast<int>(followCommandState_);
    GuiPainter::instance().blit( followCommandIcons()[state], Gui::Coord( minX+66, minY+130 ) );
    state = static_cast<int>(attackCommandState_);
    GuiPainter::instance().blit( attackCommandIcons()[state], Gui::Coord( minX+130/2-64/2, minY+130+24 ) );
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

//static
GuiBitmap* MachGuiFPCommand::attackCommandIcons()
{
    static GuiBitmap attackIcons[NumCommandIconStates] =
    {
        /* INVALID   */ Gui::bitmap( SysPathName("gui/fstpersn/command/attack_invalid.bmp") ),
        /* VALID     */ Gui::bitmap( SysPathName("gui/fstpersn/command/attack_valid.bmp") ),
        /* ACTIVATED */ Gui::bitmap( SysPathName("gui/fstpersn/command/attack_activate.bmp") )
    };

    return attackIcons;
}

//static
GuiBitmap* MachGuiFPCommand::followCommandIcons()
{
    static GuiBitmap followIcons[NumCommandIconStates] =
    {
        /* INVALID   */ Gui::bitmap( SysPathName("gui/fstpersn/command/follow_invalid.bmp") ),
        /* VALID     */ Gui::bitmap( SysPathName("gui/fstpersn/command/follow_valid.bmp") ),
        /* ACTIVATED */ Gui::bitmap( SysPathName("gui/fstpersn/command/follow_activate.bmp") )
    };

    return followIcons;
}

//static
GuiBitmap* MachGuiFPCommand::moveCommandIcons()
{
    static GuiBitmap moveIcons[NumCommandIconStates] =
    {
        /* INVALID   */ Gui::bitmap( SysPathName("gui/fstpersn/command/move_invalid.bmp") ),
        /* VALID     */ Gui::bitmap( SysPathName("gui/fstpersn/command/move_valid.bmp") ),
        /* ACTIVATED */ Gui::bitmap( SysPathName("gui/fstpersn/command/move_activate.bmp") )
    };

    return moveIcons;
}
