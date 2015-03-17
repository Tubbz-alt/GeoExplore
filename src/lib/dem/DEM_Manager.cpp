#include "DEM_Manager.hpp"

namespace GEO{
namespace DEM{

/**
 * Dem Manager
*/
DEM_Manager::DEM_Manager(){

}


/**
 * Add DEM Driver
*/
void DEM_Manager::Add_DEM_IO_Driver( A_DEM_IO_Driver_Base::ptr_t driver )
{
    m_drivers.push_back(driver);
}


static DEM_Manager::ptr_t m_instance(nullptr);

/**
 * Instance Of
*/
DEM_Manager::ptr_t The_DEM_Manager::Instance_Of(){
    if( m_instance == nullptr ){
        Initialize();
    }
    return m_instance;
}


/**
 * Initialize
*/
void The_DEM_Manager::Initialize(){    
    if( m_instance == nullptr ){
        m_instance.reset( new DEM_Manager());
    }
}


/**
 * Constructor
*/
The_DEM_Manager::The_DEM_Manager()
{
}

/**
 * Copy Constructor
*/
The_DEM_Manager::The_DEM_Manager( The_DEM_Manager const& rhs )
{
}

/**
 * Assignment Operator
*/
void The_DEM_Manager::operator = ( The_DEM_Manager const& rhs )const{

}


} /// End of DEM Namespace
} /// End of GEO Namespace

