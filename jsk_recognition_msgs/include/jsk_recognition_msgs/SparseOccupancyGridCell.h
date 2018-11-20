// Generated by gencpp from file jsk_recognition_msgs/SparseOccupancyGridCell.msg
// DO NOT EDIT!


#ifndef JSK_RECOGNITION_MSGS_MESSAGE_SPARSEOCCUPANCYGRIDCELL_H
#define JSK_RECOGNITION_MSGS_MESSAGE_SPARSEOCCUPANCYGRIDCELL_H


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
struct SparseOccupancyGridCell_
{
  typedef SparseOccupancyGridCell_<ContainerAllocator> Type;

  SparseOccupancyGridCell_()
    : row_index(0)
    , value(0.0)  {
    }
  SparseOccupancyGridCell_(const ContainerAllocator& _alloc)
    : row_index(0)
    , value(0.0)  {
  (void)_alloc;
    }



   typedef int32_t _row_index_type;
  _row_index_type row_index;

   typedef float _value_type;
  _value_type value;





  typedef boost::shared_ptr< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> const> ConstPtr;

}; // struct SparseOccupancyGridCell_

typedef ::jsk_recognition_msgs::SparseOccupancyGridCell_<std::allocator<void> > SparseOccupancyGridCell;

typedef boost::shared_ptr< ::jsk_recognition_msgs::SparseOccupancyGridCell > SparseOccupancyGridCellPtr;
typedef boost::shared_ptr< ::jsk_recognition_msgs::SparseOccupancyGridCell const> SparseOccupancyGridCellConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a5179e922852f82ee6322db1f097ab64";
  }

  static const char* value(const ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa5179e922852f82eULL;
  static const uint64_t static_value2 = 0xe6322db1f097ab64ULL;
};

template<class ContainerAllocator>
struct DataType< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jsk_recognition_msgs/SparseOccupancyGridCell";
  }

  static const char* value(const ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 row_index\n\
float32 value\n\
";
  }

  static const char* value(const ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.row_index);
      stream.next(m.value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SparseOccupancyGridCell_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::jsk_recognition_msgs::SparseOccupancyGridCell_<ContainerAllocator>& v)
  {
    s << indent << "row_index: ";
    Printer<int32_t>::stream(s, indent + "  ", v.row_index);
    s << indent << "value: ";
    Printer<float>::stream(s, indent + "  ", v.value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // JSK_RECOGNITION_MSGS_MESSAGE_SPARSEOCCUPANCYGRIDCELL_H