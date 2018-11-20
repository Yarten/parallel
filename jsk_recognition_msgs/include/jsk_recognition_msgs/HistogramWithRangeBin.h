// Generated by gencpp from file jsk_recognition_msgs/HistogramWithRangeBin.msg
// DO NOT EDIT!


#ifndef JSK_RECOGNITION_MSGS_MESSAGE_HISTOGRAMWITHRANGEBIN_H
#define JSK_RECOGNITION_MSGS_MESSAGE_HISTOGRAMWITHRANGEBIN_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace jsk_recognition_msgs
{
template <class ContainerAllocator>
struct HistogramWithRangeBin_
{
  typedef HistogramWithRangeBin_<ContainerAllocator> Type;

  HistogramWithRangeBin_()
    : min_value(0.0)
    , max_value(0.0)
    , count(0)  {
    }
  HistogramWithRangeBin_(const ContainerAllocator& _alloc)
    : min_value(0.0)
    , max_value(0.0)
    , count(0)  {
  (void)_alloc;
    }



   typedef double _min_value_type;
  _min_value_type min_value;

   typedef double _max_value_type;
  _max_value_type max_value;

   typedef uint32_t _count_type;
  _count_type count;





  typedef boost::shared_ptr< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> const> ConstPtr;

}; // struct HistogramWithRangeBin_

typedef ::jsk_recognition_msgs::HistogramWithRangeBin_<std::allocator<void> > HistogramWithRangeBin;

typedef boost::shared_ptr< ::jsk_recognition_msgs::HistogramWithRangeBin > HistogramWithRangeBinPtr;
typedef boost::shared_ptr< ::jsk_recognition_msgs::HistogramWithRangeBin const> HistogramWithRangeBinConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace jsk_recognition_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'pcl_msgs': ['/opt/ros/melodic/share/pcl_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/melodic/share/sensor_msgs/cmake/../msg'], 'jsk_footstep_msgs': ['/opt/ros/melodic/share/jsk_footstep_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/melodic/share/geometry_msgs/cmake/../msg'], 'jsk_recognition_msgs': ['/media/yarten/DATA/Project/ROS/Parallel/src/jsk_recognition_msgs/msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a7fe6c3021fcba2c6357f3db21601551";
  }

  static const char* value(const ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa7fe6c3021fcba2cULL;
  static const uint64_t static_value2 = 0x6357f3db21601551ULL;
};

template<class ContainerAllocator>
struct DataType< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jsk_recognition_msgs/HistogramWithRangeBin";
  }

  static const char* value(const ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 min_value\n\
float64 max_value\n\
uint32 count\n\
";
  }

  static const char* value(const ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.min_value);
      stream.next(m.max_value);
      stream.next(m.count);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct HistogramWithRangeBin_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::jsk_recognition_msgs::HistogramWithRangeBin_<ContainerAllocator>& v)
  {
    s << indent << "min_value: ";
    Printer<double>::stream(s, indent + "  ", v.min_value);
    s << indent << "max_value: ";
    Printer<double>::stream(s, indent + "  ", v.max_value);
    s << indent << "count: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.count);
  }
};

} // namespace message_operations
} // namespace ros

#endif // JSK_RECOGNITION_MSGS_MESSAGE_HISTOGRAMWITHRANGEBIN_H