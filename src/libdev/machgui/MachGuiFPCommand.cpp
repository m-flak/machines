#include "machgui/MachGuiFPCommand.hpp"

#include "system/pathname.hpp"
#include "gui/painter.hpp"

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
    // Display widget body, active squad icon, etc...
    const int minX = absoluteBoundary().minCorner().x();
    const int minY = absoluteBoundary().minCorner().y();

    GuiPainter::instance().blit( widgetBody(), Gui::Coord( minX, minY ) );
    GuiPainter::instance().blit( noSquadronSelected(), Gui::Coord( minX+41, minY+52 ) );
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
