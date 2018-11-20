// Generated by gencpp from file jsk_recognition_msgs/CheckCircle.msg
// DO NOT EDIT!


#ifndef JSK_RECOGNITION_MSGS_MESSAGE_CHECKCIRCLE_H
#define JSK_RECOGNITION_MSGS_MESSAGE_CHECKCIRCLE_H

#include <ros/service_traits.h>


#include <jsk_recognition_msgs/CheckCircleRequest.h>
#include <jsk_recognition_msgs/CheckCircleResponse.h>


namespace jsk_recognition_msgs
{

struct CheckCircle
{

typedef CheckCircleRequest Request;
typedef CheckCircleResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct CheckCircle
} // namespace jsk_recognition_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::jsk_recognition_msgs::CheckCircle > {
  static const char* value()
  {
    return "36549e2f705ec32b8c873cf22d68b357";
  }

  static const char* value(const ::jsk_recognition_msgs::CheckCircle&) { return value(); }
};

template<>
struct DataType< ::jsk_recognition_msgs::CheckCircle > {
  static const char* value()
  {
    return "jsk_recognition_msgs/CheckCircle";
  }

  static const char* value(const ::jsk_recognition_msgs::CheckCircle&) { return value(); }
};


// service_traits::MD5Sum< ::jsk_recognition_msgs::CheckCircleRequest> should match 
// service_traits::MD5Sum< ::jsk_recognition_msgs::CheckCircle > 
template<>
struct MD5Sum< ::jsk_recognition_msgs::CheckCircleRequest>
{
  static const char* value()
  {
    return MD5Sum< ::jsk_recognition_msgs::CheckCircle >::value();
  }
  static const char* value(const ::jsk_recognition_msgs::CheckCircleRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::jsk_recognition_msgs::CheckCircleRequest> should match 
// service_traits::DataType< ::jsk_recognition_msgs::CheckCircle > 
template<>
struct DataType< ::jsk_recognition_msgs::CheckCircleRequest>
{
  static const char* value()
  {
    return DataType< ::jsk_recognition_msgs::CheckCircle >::value();
  }
  static const char* value(const ::jsk_recognition_msgs::CheckCircleRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::jsk_recognition_msgs::CheckCircleResponse> should match 
// service_traits::MD5Sum< ::jsk_recognition_msgs::CheckCircle > 
template<>
struct MD5Sum< ::jsk_recognition_msgs::CheckCircleResponse>
{
  static const char* value()
  {
    return MD5Sum< ::jsk_recognition_msgs::CheckCircle >::value();
  }
  static const char* value(const ::jsk_recognition_msgs::CheckCircleResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::jsk_recognition_msgs::CheckCircleResponse> should match 
// service_traits::DataType< ::jsk_recognition_msgs::CheckCircle > 
template<>
struct DataType< ::jsk_recognition_msgs::CheckCircleResponse>
{
  static const char* value()
  {
    return DataType< ::jsk_recognition_msgs::CheckCircle >::value();
  }
  static const char* value(const ::jsk_recognition_msgs::CheckCircleResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // JSK_RECOGNITION_MSGS_MESSAGE_CHECKCIRCLE_H