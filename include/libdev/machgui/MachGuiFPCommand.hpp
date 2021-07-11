#pragma once

#include "gui/displaya.hpp"

class MachLog1stPersonHandler;

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

protected:
    virtual void doDisplay() override;

private:
    static GuiBitmap& noSquadronSelected();

    MachLog1stPersonHandler* pLogHandler_;
};
