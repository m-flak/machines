#include "machgui/MachGuiFPCommand.hpp"

#include "system/pathname.hpp"

MachGuiFPCommand::MachGuiFPCommand( GuiDisplayable* pParent, const Gui::Coord& relPos )
    : GuiDisplayable( pParent, Gui::Box( relPos, 1, 1 ) )
{
    pLogHandler_ = nullptr;
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

//virtual
void MachGuiFPCommand::doDisplay()
{

}

//static
GuiBitmap& MachGuiFPCommand::noSquadronSelected()
{
    static GuiBitmap blankIcon = Gui::bitmap( SysPathName("gui/fstpersn/machines/backgrnd.bmp" ) );
    return blankIcon;
}
