/**
 * @file    ChannelType.cpp
 * @author  Marvin Smith
 * @date    3/21/2015
*/
#include "ChannelType.hpp"

namespace GEO{
namespace IMG{

// Instanciate Max Values
constexpr double ChannelTypeDouble::maxValue;
constexpr double ChannelTypeDoubleFree::maxValue;
constexpr uint8_t ChannelTypeUInt8::maxValue;
constexpr uint16_t ChannelTypeUInt12::maxValue;
constexpr uint16_t ChannelTypeUInt14::maxValue;
constexpr uint16_t ChannelTypeUInt16::maxValue;
constexpr uint32_t ChannelTypeUInt32::maxValue;

// Instanciate Min Values
constexpr double ChannelTypeDouble::minValue;
constexpr double ChannelTypeDoubleFree::minValue;
constexpr uint8_t ChannelTypeUInt8::minValue;
constexpr uint16_t ChannelTypeUInt12::minValue;
constexpr uint16_t ChannelTypeUInt14::minValue;
constexpr uint16_t ChannelTypeUInt16::minValue;
constexpr uint32_t ChannelTypeUInt32::minValue;

} // End of IMG Namespace
} // End of GEO Namespace

