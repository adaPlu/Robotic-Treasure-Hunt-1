// Generated by gencpp from file logical_camera_plugin/logicalImage.msg
// DO NOT EDIT!


#ifndef LOGICAL_CAMERA_PLUGIN_MESSAGE_LOGICALIMAGE_H
#define LOGICAL_CAMERA_PLUGIN_MESSAGE_LOGICALIMAGE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace logical_camera_plugin
{
template <class ContainerAllocator>
struct logicalImage_
{
  typedef logicalImage_<ContainerAllocator> Type;

  logicalImage_()
    : modelName()
    , pose_pos_x(0.0)
    , pose_pos_y(0.0)
    , pose_pos_z(0.0)
    , pose_rot_x(0.0)
    , pose_rot_y(0.0)
    , pose_rot_z(0.0)
    , pose_rot_w(0.0)  {
    }
  logicalImage_(const ContainerAllocator& _alloc)
    : modelName(_alloc)
    , pose_pos_x(0.0)
    , pose_pos_y(0.0)
    , pose_pos_z(0.0)
    , pose_rot_x(0.0)
    , pose_rot_y(0.0)
    , pose_rot_z(0.0)
    , pose_rot_w(0.0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _modelName_type;
  _modelName_type modelName;

   typedef float _pose_pos_x_type;
  _pose_pos_x_type pose_pos_x;

   typedef float _pose_pos_y_type;
  _pose_pos_y_type pose_pos_y;

   typedef float _pose_pos_z_type;
  _pose_pos_z_type pose_pos_z;

   typedef float _pose_rot_x_type;
  _pose_rot_x_type pose_rot_x;

   typedef float _pose_rot_y_type;
  _pose_rot_y_type pose_rot_y;

   typedef float _pose_rot_z_type;
  _pose_rot_z_type pose_rot_z;

   typedef float _pose_rot_w_type;
  _pose_rot_w_type pose_rot_w;





  typedef boost::shared_ptr< ::logical_camera_plugin::logicalImage_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::logical_camera_plugin::logicalImage_<ContainerAllocator> const> ConstPtr;

}; // struct logicalImage_

typedef ::logical_camera_plugin::logicalImage_<std::allocator<void> > logicalImage;

typedef boost::shared_ptr< ::logical_camera_plugin::logicalImage > logicalImagePtr;
typedef boost::shared_ptr< ::logical_camera_plugin::logicalImage const> logicalImageConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::logical_camera_plugin::logicalImage_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace logical_camera_plugin

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'logical_camera_plugin': ['/home/adam/wsfinal/src/logical_camera_plugin/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::logical_camera_plugin::logicalImage_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::logical_camera_plugin::logicalImage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::logical_camera_plugin::logicalImage_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c513e19b80cdf2effbda220ba2ebb388";
  }

  static const char* value(const ::logical_camera_plugin::logicalImage_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc513e19b80cdf2efULL;
  static const uint64_t static_value2 = 0xfbda220ba2ebb388ULL;
};

template<class ContainerAllocator>
struct DataType< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "logical_camera_plugin/logicalImage";
  }

  static const char* value(const ::logical_camera_plugin::logicalImage_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string modelName\n\
float32 pose_pos_x\n\
float32 pose_pos_y\n\
float32 pose_pos_z\n\
float32 pose_rot_x\n\
float32 pose_rot_y\n\
float32 pose_rot_z\n\
float32 pose_rot_w\n\
";
  }

  static const char* value(const ::logical_camera_plugin::logicalImage_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.modelName);
      stream.next(m.pose_pos_x);
      stream.next(m.pose_pos_y);
      stream.next(m.pose_pos_z);
      stream.next(m.pose_rot_x);
      stream.next(m.pose_rot_y);
      stream.next(m.pose_rot_z);
      stream.next(m.pose_rot_w);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct logicalImage_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::logical_camera_plugin::logicalImage_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::logical_camera_plugin::logicalImage_<ContainerAllocator>& v)
  {
    s << indent << "modelName: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.modelName);
    s << indent << "pose_pos_x: ";
    Printer<float>::stream(s, indent + "  ", v.pose_pos_x);
    s << indent << "pose_pos_y: ";
    Printer<float>::stream(s, indent + "  ", v.pose_pos_y);
    s << indent << "pose_pos_z: ";
    Printer<float>::stream(s, indent + "  ", v.pose_pos_z);
    s << indent << "pose_rot_x: ";
    Printer<float>::stream(s, indent + "  ", v.pose_rot_x);
    s << indent << "pose_rot_y: ";
    Printer<float>::stream(s, indent + "  ", v.pose_rot_y);
    s << indent << "pose_rot_z: ";
    Printer<float>::stream(s, indent + "  ", v.pose_rot_z);
    s << indent << "pose_rot_w: ";
    Printer<float>::stream(s, indent + "  ", v.pose_rot_w);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LOGICAL_CAMERA_PLUGIN_MESSAGE_LOGICALIMAGE_H
