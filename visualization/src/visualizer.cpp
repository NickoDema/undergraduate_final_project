/* visualizer.cpp
 *
 *  Created on: 16.04.2017
 *       Email: Nicko_Dema@protonmail.com
 *              ITMO University
 *              Department of Computer Science and Control Systems
 */

#include <visualizer.h>

Visualizer::Visualizer(std::string node_name): nh_("~")
{
    marker_pub = nh_.advertise<visualization_msgs::Marker>("/visualization", 3,true);
}

bool Visualizer::set_marker (visualization_msgs::Marker &marker)
{
    marker.header.frame_id = "/base_link";
	marker.header.stamp = ros::Time::now();
	marker.ns = "markers";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::POINTS;
	marker.action = visualization_msgs::Marker::ADD;

	marker.pose.orientation.w = 1.0; 
	marker.scale.x = 0.01;
	marker.scale.y = 0.01;
	marker.scale.z = 0.01;

	marker.color.r = 0.0f;
	marker.color.g = 0.5f;
	marker.color.b = 0.5f;
	marker.color.a = 1.0;

	marker.lifetime = ros::Duration(0.2);
    return true;
}

void Visualizer::spin()
{
    int i = 0;
    ros::Rate R(5);
    while(nh_.ok())
    {
        while (marker_pub.getNumSubscribers() < 1 && nh_.ok()) 
	    {
	        ROS_WARN_ONCE("Please create a subscriber to the marker");
	        R.sleep();
	    }
        visualization_msgs::Marker marker;
        set_marker(marker);
        pnt.x = 0.61*sin(i*M_PI/180);
	    pnt.y = 0.61*cos(i*M_PI/180);
	    pnt.z = 0;
	    marker.points.push_back(pnt);

	    std::cout << "marker x: " << marker.points[0].x << std::endl;
        std::cout << "pnt x: " << pnt.x << std::endl;

        marker_pub.publish(marker);

        ros::spinOnce();

	    i++;
	    i==360 ? i = 0 :  
        
        R.sleep();
    }
}

Visualizer::~Visualizer()
{
    marker_pub.shutdown();
}