#pragma once

#include "gui/displaya.hpp"
#include "machlog/p1handlr.hpp"

class MachGuiFPCommand : public GuiDisplayable
{
public:
    MachGuiFPCommand( GuiDisplayable* pParent, const Gui::Coord& relPos );
    ~MachGuiFPCommand();
    // NON-COPYABLE
    MachGuiFPCommand(const MachGuiFPCommand&) = delete;
    MachGuiFPCommand& operator=(const MachGuiFPCommand&) = delete;

    ///////////////////////////////////////////////////

    void logHandler( MachLog1stPersonHandler* logHandler);
    void resetLogHandler();

    // Change the icon that displays within the control
    void updateSquadIcon();
    void clearSquadIcon();

protected:
    virtual void doDisplay() override;

private:
    static GuiBitmap& noSquadronSelected();
    static GuiBitmap& widgetBody();

    GuiBitmap activeSquadIcon_;

    // Will either point to noSquadronSelected() OR activeSquadIcon_
    GuiBitmap* pActiveSquadIcon_;
    MachLog1stPersonHandler* pLogHandler_;
};
