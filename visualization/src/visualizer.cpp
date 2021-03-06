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
    marker_pub = nh_.advertise<visualization_msgs::Marker>("/visualization", 1,true);
}

bool Visualizer::set_marker (visualization_msgs::Marker &marker, m_type type)
{
	if (type == line_s) 
	{
		marker.header.frame_id = "/base_link";
		marker.header.stamp = ros::Time::now();
		marker.ns = "markers";
		marker.id = 0;
		marker.type = visualization_msgs::Marker::LINE_STRIP;
		marker.action = visualization_msgs::Marker::ADD;

		marker.pose.orientation.w = 1.0; 
		marker.scale.x = 0.01;
		marker.scale.y = 0.01;
		marker.scale.z = 0.01;

		marker.color.r = 0.0f;
		marker.color.g = 0.5f;
		marker.color.b = 0.5f;
		marker.color.a = 0.5;

		marker.lifetime = ros::Duration(0.5);
	}
    
    return true;
}

void Visualizer::spin()
{
    int i = 0;
    ros::Rate R(10);
	while (marker_pub.getNumSubscribers() < 1 && nh_.ok()) 
	    {
	        ROS_WARN_ONCE("Please create a subscriber to the marker");
	        R.sleep();
	    }

   while(nh_.ok())
    {
		visualization_msgs::Marker contour;
		set_marker(contour, line_s);
		pnt.x = X_SIZE;
		pnt.y = Y_SIZE;
		pnt.z = 0.01;
		contour.points.push_back(pnt);
		pnt.y = -Y_SIZE;
		contour.points.push_back(pnt);
		pnt.x= -X_SIZE;
		contour.points.push_back(pnt);
		pnt.y = Y_SIZE;
		contour.points.push_back(pnt);
		pnt.x = X_SIZE;
		contour.points.push_back(pnt);
		marker_pub.publish(contour);
		ros::spinOnce();

/*		contour.points.clear();
		//set_marker(contour, line_s);
		contour.id = 1;
		pnt.x = X_SIZE+BORD;
		pnt.y = Y_SIZE+BORD;
		pnt.z = 0.01;
		contour.points.push_back(pnt);
		pnt.x = pnt.x - X_SIZE - Y_SIZE - BORD_2;
		contour.points.push_back(pnt);
		pnt.y = pnt.y - Y_SIZE*2 - BORD_2;
		contour.points.push_back(pnt);
		pnt.x = pnt.x + Y_SIZE + X_SIZE + BORD_2;
		contour.points.push_back(pnt);
		pnt.y = pnt.y + Y_SIZE*2 + BORD_2;
		contour.points.push_back(pnt);
		marker_pub.publish(contour);
		ros::spinOnce();*/
        R.sleep();
    }
}

Visualizer::~Visualizer()
{
    marker_pub.shutdown();
}