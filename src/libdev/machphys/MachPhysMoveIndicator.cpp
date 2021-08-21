#include "machphys/MachPhysMoveIndicator.hpp"

#include "render/texture.hpp"
#include "render/texmgr.hpp"
#include "render/colour.hpp"

PER_DEFINE_PERSISTENT( MachPhysMoveIndicator );

MachPhysMoveIndicator::MachPhysMoveIndicator(W4dEntity* pParent, const W4dTransform3d& localTransform, MATHEX_SCALAR size)
    : W4dSprite3d(pParent, localTransform, size, size, getMaterial())
{

}

MachPhysMoveIndicator::MachPhysMoveIndicator( PerConstructor con )
: W4dSprite3d( con )
{
}

MachPhysMoveIndicator::~MachPhysMoveIndicator()
{

}

ostream& operator <<( ostream& o, const MachPhysMoveIndicator& t )
{

    o << "MachPhysMoveIndicator " << (void*)&t << " start" << std::endl;
    o << "MachPhysMoveIndicator " << (void*)&t << " end" << std::endl;

    return o;
}

void perWrite( PerOstream& ostr, const MachPhysMoveIndicator& indicator )
{
    const W4dSprite3d& base = indicator;

    ostr << base;
}

void perRead( PerIstream& istr, MachPhysMoveIndicator& indicator )
{
    W4dSprite3d& base = indicator;

    istr >> base;
}


//static
RenMaterial MachPhysMoveIndicator::getMaterial()
{
    static RenMaterial indicatorMaterial_ = createMaterial();

    return indicatorMaterial_;
}
//static
RenTexture MachPhysMoveIndicator::createTexture()
{
    static RenTexture indicatorTexture_ = RenTexManager::instance().createTexture("move_indicator.bmp");

    return indicatorTexture_;
}

//static
RenMaterial MachPhysMoveIndicator::createMaterial()
{
    auto material = RenMaterial{ RenColour::black() };
    material.texture(createTexture());

    return material;
}
