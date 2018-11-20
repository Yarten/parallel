// Generated by gencpp from file autoware_msgs/DetectedObject.msg
// DO NOT EDIT!


#ifndef AUTOWARE_MSGS_MESSAGE_DETECTEDOBJECT_H
#define AUTOWARE_MSGS_MESSAGE_DETECTEDOBJECT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PolygonStamped.h>
#include <autoware_msgs/LaneArray.h>

namespace autoware_msgs
{
template <class ContainerAllocator>
struct DetectedObject_
{
  typedef DetectedObject_<ContainerAllocator> Type;

  DetectedObject_()
    : header()
    , id(0)
    , label()
    , pose()
    , dimensions()
    , variance()
    , velocity()
    , convex_hull()
    , candidate_trajectories()
    , pose_reliable(false)
    , velocity_reliable(false)
    , behavior_state(0)  {
    }
  DetectedObject_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , id(0)
    , label(_alloc)
    , pose(_alloc)
    , dimensions(_alloc)
    , variance(_alloc)
    , velocity(_alloc)
    , convex_hull(_alloc)
    , candidate_trajectories(_alloc)
    , pose_reliable(false)
    , velocity_reliable(false)
    , behavior_state(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint32_t _id_type;
  _id_type id;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _label_type;
  _label_type label;

   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _pose_type;
  _pose_type pose;

   typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _dimensions_type;
  _dimensions_type dimensions;

   typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _variance_type;
  _variance_type variance;

   typedef  ::geometry_msgs::Twist_<ContainerAllocator>  _velocity_type;
  _velocity_type velocity;

   typedef  ::geometry_msgs::PolygonStamped_<ContainerAllocator>  _convex_hull_type;
  _convex_hull_type convex_hull;

   typedef  ::autoware_msgs::LaneArray_<ContainerAllocator>  _candidate_trajectories_type;
  _candidate_trajectories_type candidate_trajectories;

   typedef uint8_t _pose_reliable_type;
  _pose_reliable_type pose_reliable;

   typedef uint8_t _velocity_reliable_type;
  _velocity_reliable_type velocity_reliable;

   typedef uint32_t _behavior_state_type;
  _behavior_state_type behavior_state;





  typedef boost::shared_ptr< ::autoware_msgs::DetectedObject_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autoware_msgs::DetectedObject_<ContainerAllocator> const> ConstPtr;

}; // struct DetectedObject_

typedef ::autoware_msgs::DetectedObject_<std::allocator<void> > DetectedObject;

typedef boost::shared_ptr< ::autoware_msgs::DetectedObject > DetectedObjectPtr;
typedef boost::shared_ptr< ::autoware_msgs::DetectedObject const> DetectedObjectConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autoware_msgs::DetectedObject_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autoware_msgs::DetectedObject_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace autoware_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'pcl_msgs': ['/opt/ros/melodic/share/pcl_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/melodic/share/sensor_msgs/cmake/../msg'], 'jsk_footstep_msgs': ['/opt/ros/melodic/share/jsk_footstep_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/melodic/share/geometry_msgs/cmake/../msg'], 'jsk_recognition_msgs': ['/media/yarten/DATA/Project/ROS/Parallel/src/jsk_recognition_msgs/msg'], 'actionlib_msgs': ['/opt/ros/melodic/share/actionlib_msgs/cmake/../msg'], 'autoware_msgs': ['/media/yarten/DATA/Project/ROS/Parallel/src/autoware_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autoware_msgs::DetectedObject_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autoware_msgs::DetectedObject_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autoware_msgs::DetectedObject_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c06586ec9d717a6bea036a0fc1901bdd";
  }

  static const char* value(const ::autoware_msgs::DetectedObject_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc06586ec9d717a6bULL;
  static const uint64_t static_value2 = 0xea036a0fc1901bddULL;
};

template<class ContainerAllocator>
struct DataType< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autoware_msgs/DetectedObject";
  }

  static const char* value(const ::autoware_msgs::DetectedObject_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n\
\n\
uint32 id\n\
string label\n\
\n\
geometry_msgs/Pose pose\n\
geometry_msgs/Vector3 dimensions\n\
geometry_msgs/Vector3 variance\n\
geometry_msgs/Twist velocity\n\
\n\
geometry_msgs/PolygonStamped convex_hull\n\
autoware_msgs/LaneArray candidate_trajectories\n\
\n\
bool pose_reliable\n\
bool velocity_reliable\n\
\n\
# Behavior State of the Detected Object\n\
# FORWARD_STATE			= 0\n\
# STOPPING_STATE 		= 1\n\
# BRANCH_LEFT_STATE		= 2\n\
# BRANCH_RIGHT_STATE	= 3 \n\
# YIELDING_STATE		= 4\n\
# ACCELERATING_STATE	= 5\n\
# SLOWDOWN_STATE 		= 6\n\
\n\
uint32 behavior_state\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
================================================================================\n\
MSG: geometry_msgs/Twist\n\
# This expresses velocity in free space broken into its linear and angular parts.\n\
Vector3  linear\n\
Vector3  angular\n\
\n\
================================================================================\n\
MSG: geometry_msgs/PolygonStamped\n\
# This represents a Polygon with reference coordinate frame and timestamp\n\
Header header\n\
Polygon polygon\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Polygon\n\
#A specification of a polygon where the first and last points are assumed to be connected\n\
Point32[] points\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point32\n\
# This contains the position of a point in free space(with 32 bits of precision).\n\
# It is recommeded to use Point wherever possible instead of Point32.  \n\
# \n\
# This recommendation is to promote interoperability.  \n\
#\n\
# This message is designed to take up less space when sending\n\
# lots of points at once, as in the case of a PointCloud.  \n\
\n\
float32 x\n\
float32 y\n\
float32 z\n\
================================================================================\n\
MSG: autoware_msgs/LaneArray\n\
lane[] lanes\n\
================================================================================\n\
MSG: autoware_msgs/lane\n\
Header header\n\
int32 increment\n\
int32 lane_id\n\
waypoint[] waypoints\n\
\n\
================================================================================\n\
MSG: autoware_msgs/waypoint\n\
# global id\n\
int32 gid \n\
# local id\n\
int32 lid\n\
geometry_msgs/PoseStamped pose\n\
geometry_msgs/TwistStamped twist\n\
dtlane dtlane\n\
int32 change_flag\n\
WaypointState wpstate\n\
\n\
================================================================================\n\
MSG: geometry_msgs/PoseStamped\n\
# A Pose with reference coordinate frame and timestamp\n\
Header header\n\
Pose pose\n\
\n\
================================================================================\n\
MSG: geometry_msgs/TwistStamped\n\
# A twist with reference coordinate frame and timestamp\n\
Header header\n\
Twist twist\n\
\n\
================================================================================\n\
MSG: autoware_msgs/dtlane\n\
float64 dist\n\
float64 dir\n\
float64 apara\n\
float64 r\n\
float64 slope\n\
float64 cant\n\
float64 lw\n\
float64 rw\n\
\n\
================================================================================\n\
MSG: autoware_msgs/WaypointState\n\
int32 aid\n\
uint8 NULLSTATE=0\n\
uint8 lanechange_state\n\
\n\
uint8 steering_state\n\
uint8 STR_LEFT=1\n\
uint8 STR_RIGHT=2\n\
uint8 STR_STRAIGHT=3\n\
\n\
uint8 accel_state\n\
uint8 stopline_state\n\
  uint8 TYPE_NULL=0\n\
  uint8 TYPE_STOPLINE=1\n\
  uint8 TYPE_STOP=2\n\
# 1 is stopline, 2 is stop which 2 can only be released manually.\n\
uint64 event_state\n\
";
  }

  static const char* value(const ::autoware_msgs::DetectedObject_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.id);
      stream.next(m.label);
      stream.next(m.pose);
      stream.next(m.dimensions);
      stream.next(m.variance);
      stream.next(m.velocity);
      stream.next(m.convex_hull);
      stream.next(m.candidate_trajectories);
      stream.next(m.pose_reliable);
      stream.next(m.velocity_reliable);
      stream.next(m.behavior_state);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DetectedObject_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autoware_msgs::DetectedObject_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autoware_msgs::DetectedObject_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "id: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.id);
    s << indent << "label: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.label);
    s << indent << "pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.pose);
    s << indent << "dimensions: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.dimensions);
    s << indent << "variance: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.variance);
    s << indent << "velocity: ";
    s << std::endl;
    Printer< ::geometry_msgs::Twist_<ContainerAllocator> >::stream(s, indent + "  ", v.velocity);
    s << indent << "convex_hull: ";
    s << std::endl;
    Printer< ::geometry_msgs::PolygonStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.convex_hull);
    s << indent << "candidate_trajectories: ";
    s << std::endl;
    Printer< ::autoware_msgs::LaneArray_<ContainerAllocator> >::stream(s, indent + "  ", v.candidate_trajectories);
    s << indent << "pose_reliable: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.pose_reliable);
    s << indent << "velocity_reliable: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.velocity_reliable);
    s << indent << "behavior_state: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.behavior_state);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTOWARE_MSGS_MESSAGE_DETECTEDOBJECT_H