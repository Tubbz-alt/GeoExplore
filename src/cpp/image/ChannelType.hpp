/**
 * @file    ChannelType.hpp
 * @author  Marvin Smith
 * @date    5/6/2014
*/
#ifndef __SRC_CPP_IMAGE_CHANNELTYPE_HPP__
#define __SRC_CPP_IMAGE_CHANNELTYPE_HPP__

/// C++ Standard Libraries
#include <cinttypes>

/// GeoExplore Libraries
#include <GeoExplore/core/Enumerations.hpp>


namespace GEO{

/**
 * @class ChannelType
 *
 * Defines the range of a particular pixel type.
*/
template <typename DataType, int PixelDepth>
class ChannelType{

    public:
        
        ///  Accumulator Type
        typedef DataType accumulator_type;

        ///  Type of Value
        typedef DataType type;

        /// Maximum Value
        static constexpr double maxValue = 1;

        /// Minimum Value
        static constexpr double minValue = 0;

}; /// End of ChannelType Class


/**
 * Class Template Specialization for Double-type images
*/
template<>
class ChannelType<double, 1>{

    public:
        
        /// Accumulator Type
        typedef double accumulator_type;

        /// Type of value
        typedef double type;

        /// Maximum Value
        static constexpr type maxValue = 1;

        /// Minimum Value
        static constexpr type minValue = 0;

}; /// End of ChannelType<double,1> specialization

/**
 * Class Template Specialization for Double Images that are range-free
*/
template <>
class ChannelType<double, 2>{

    public:
        
        /// Accumulator type
        typedef double accumulator_type;
        
        /// Type Parameter
        typedef double type;

        /// min value
        static constexpr type maxValue = 1;

        /// max value
        static constexpr type minValue = -1;

}; /// End of ChannelType<double,2> Specialization

/**
 * Class Template Specialization for UInt8 images
*/
template<>
class ChannelType<uint8_t, 8>{

    public:

        /// Accumulator Type
        typedef uint16_t accumulator_type;

        /// Type of value
        typedef uint8_t type;

        /// Maximum Value
        static constexpr type maxValue = 255;

        /// Minimum Value
        static constexpr type minValue = 0;


}; /// End of ChannelType<uint8_t,8> specialization


/**
 * Class Template Specialization for UInt12 images
*/
template<>
class ChannelType<uint16_t, 12>{

    public:
        
        /// Accumulator Type
        typedef uint32_t accumulator_type;

        /// Type of value
        typedef uint16_t type;

        /// Maximum Value
        static constexpr type maxValue = 4095;

        /// Minimum Value
        static constexpr type minValue = 0;

}; /// End of ChannelType<uint16_t,12> specialization



/**
 * Class Template Specialization for UInt14 images
*/
template<>
class ChannelType<uint16_t, 14>{

    public:
        
        /// Accumulator Type
        typedef uint32_t accumulator_type;
        
        /// Type of value
        typedef uint16_t type;

        /// Maximum Value
        static constexpr type maxValue = 16383;

        /// Minimum Value
        static constexpr type minValue = 0;

}; /// End of ChannelType<uint16_t,14> specialization


/**
 * Class Template Specialization for UInt16 images
*/
template<>
class ChannelType<uint16_t,16>{

    public:
         
        /// Accumulator Type
        typedef uint32_t accumulator_type;
        
        /// Type of value
        typedef uint16_t type;

        /// Maximum Value
        static constexpr type maxValue = 65535;

        /// Minimum Value
        static constexpr type minValue = 0;

}; /// End of ChannelType<uint16_t,16> specialization



/**
 * Class Template Specialization for UInt32 images
*/
template<>
class ChannelType<uint32_t,32>{

    public:

        /// Accumulator Type
        typedef uint64_t accumulator_type;
        
        /// Type of Value
        typedef uint32_t type;

        /// Maximum Value
        static constexpr type maxValue = 4294967295;

        /// Minimum Value
        static constexpr type minValue = 0;

}; /// End of ChannelType<uint32_t,32> specialization



/// Typedefs for ChannelTypes
typedef ChannelType<uint32_t, 32>  ChannelTypeUInt32;
typedef ChannelType<uint16_t, 16>  ChannelTypeUInt16;
typedef ChannelType<uint16_t, 14>  ChannelTypeUInt14;
typedef ChannelType<uint16_t, 12>  ChannelTypeUInt12;
typedef ChannelType<uint8_t,  8>   ChannelTypeUInt8;
typedef ChannelType<double, 1>     ChannelTypeDouble;
typedef ChannelType<double, 2>     ChannelTypeDoubleFree;


/**
 * Scale a pixel depending on its type.
 */
template <typename BeforeType, typename AfterType>
typename AfterType::type range_cast( typename BeforeType::type const& value ){
    
    /// Free-Range ChannelTypes require just passing the value through 
    if( std::is_same<AfterType, ChannelTypeDoubleFree>::value ){
        return (static_cast<typename AfterType::type>(value));
    }
    
    /// Otherwise do proper range scaling
    return ((( (static_cast<double>(value) - BeforeType::minValue) / 
               (      BeforeType::maxValue - BeforeType::minValue)  ) 
            *( AfterType::maxValue - AfterType::minValue)) + AfterType::minValue);
}



} /// End of Namespace GEO


#endif
