/**
 * @file    A_DEM_IO_Driver_Base.cpp
 * @author  Marvin Smith
 * @date    3/27/2015
*/
#include "A_DEM_IO_Driver_Base.hpp"


namespace GEO{
namespace DEM{


/******************************************************/
/*                    Constructor                     */
/******************************************************/
A_DEM_IO_Driver_Base::A_DEM_IO_Driver_Base()
  : m_class_name("A_DEM_IO_Driver_Base")
{
}


/******************************************************/
/*          Initialize the Base Driver Type           */
/******************************************************/
Status A_DEM_IO_Driver_Base::Initialize()
{
    return Status(StatusType::SUCCESS);
}


/******************************************************/
/*              Get the DEM IO Driver Type            */
/******************************************************/
DEM_IO_Driver_Type A_DEM_IO_Driver_Base::Get_DEM_IO_Driver_Type()const
{
    return DEM_IO_Driver_Type::BASE;
}


/******************************************************/
/*           Check Initialization Status              */
/******************************************************/
bool A_DEM_IO_Driver_Base::Is_Initialized( Status& status )const
{
    status = Status( StatusType::SUCCESS );
    return true;
}

} // End of DEM Namespace
} // End of GEO Namespace

