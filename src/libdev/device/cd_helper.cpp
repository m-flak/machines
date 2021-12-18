#include "device/cd_helper.hpp"

#include "device/cd.hpp"
#include "device/DevCDImpl.hpp"
#include "system/registry.hpp"

void device::helper::cd::configure(DevCD* cd)
{
    constexpr char configEnableMusic[] = "Options\\Music\\enabled";
    auto configValue                   = std::string{};
    auto dummy                         = SysRegistry::KeyHandle{};

    // by default enable, unless otherwise specified
    bool enableMusic                   = true;

    if (SysRegistry::SUCCESS == SysRegistry::instance().queryValueNoRecord(dummy, configEnableMusic, configValue))
    {
        enableMusic &= ( std::atoi(configValue.c_str()) != 0 );
    }

    cd->pImpl_->musicEnabled_ = enableMusic;
}
