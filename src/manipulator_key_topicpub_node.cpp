#include "ros/ros.h"
#include "std_msgs/Int8.h"

#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

int getch()
{
#ifdef __linux__
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
#elif defined(_WIN32) || defined(_WIN64)
  return _getch();
#endif
}


int open_topic_pub=0;


void printText()
{
  printf("\n");
  printf("---------------------------\n");
  printf("Control Your OpenManipulator!\n");
  printf("---------------------------\n");
  printf("w : increase x axis in task space\n");
  printf("s : decrease x axis in task space\n");
  printf("a : increase y axis in task space\n");
  printf("d : decrease y axis in task space\n");
  printf("z : increase z axis in task space\n");
  printf("x : decrease z axis in task space\n");
  printf("\n");
  printf("y : increase joint 1 angle\n");
  printf("h : decrease joint 1 angle\n");
  printf("u : increase joint 2 angle\n");
  printf("j : decrease joint 2 angle\n");
  printf("i : increase joint 3 angle\n");
  printf("k : decrease joint 3 angle\n");
  printf("o : increase joint 4 angle\n");
  printf("l : decrease joint 4 angle\n");
  printf("\n");
  printf("g : gripper open\n");
  printf("f : gripper close\n");
  printf("       \n");
  printf("1 : init pose\n");
  printf("2 : home pose\n");
  printf("       \n");
  printf("@b : scan x,y,z @\n");
  printf("       \n");
  printf("q to quit\n");
  printf("---------------------------\n");
 /* printf("Present Joint Angle J1: %.3lf J2: %.3lf J3: %.3lf J4: %.3lf\n",
         getPresentJointAngle().at(0),
         getPresentJointAngle().at(1),
         getPresentJointAngle().at(2),
         getPresentJointAngle().at(3));
  printf("Present Kinematics Position X: %.3lf Y: %.3lf Z: %.3lf\n",
         getPresentKinematicsPose().at(0),
         getPresentKinematicsPose().at(1),
         getPresentKinematicsPose().at(2));*/
  printf("---------------------------\n");

}
void setGoal(char ch)
{

  if (ch == 'w' || ch == 'W')
  {
    printf("input : w \tincrease(++) x axis in task space\n");
    open_topic_pub = 1;


  }
  else if (ch == 's' || ch == 'S')
  {
    printf("input : s \tdecrease(--) x axis in task space\n");
 open_topic_pub = 2;

  }
  else if (ch == 'a' || ch == 'A')
  {
    printf("input : a \tincrease(++) y axis in task space\n");
 open_topic_pub =3 ;
  }
  else if (ch == 'd' || ch == 'D')
  {
    printf("input : d \tdecrease(--) y axis in task space\n");
 open_topic_pub =4 ;
  }
  else if (ch == 'z' || ch == 'Z')
  {
    printf("input : z \tincrease(++) z axis in task space\n");
 open_topic_pub = 5;
  }
  else if (ch == 'x' || ch == 'X')
  {
    printf("input : x \tdecrease(--) z axis in task space\n");
 open_topic_pub = 6;
  }
  else if (ch == 'y' || ch == 'Y')
  {
    printf("input : y \tincrease(++) joint 1 angle\n");
 open_topic_pub =7 ;
  }
  else if (ch == 'h' || ch == 'H')
  {
    printf("input : h \tdecrease(--) joint 1 angle\n");
 open_topic_pub = 8;
  }
  else if (ch == 'u' || ch == 'U')
  {
    printf("input : u \tincrease(++) joint 2 angle\n");
 open_topic_pub = 9;
  }
  else if (ch == 'j' || ch == 'J')
  {
    printf("input : j \tdecrease(--) joint 2 angle\n");
 open_topic_pub = 10;
  }
  else if (ch == 'i' || ch == 'I')
  {
    printf("input : i \tincrease(++) joint 3 angle\n");
 open_topic_pub = 11;
  }
  else if (ch == 'k' || ch == 'K')
  {
    printf("input : k \tdecrease(--) joint 3 angle\n");
 open_topic_pub = 12;
  }
  else if (ch == 'o' || ch == 'O')
  {
    printf("input : o \tincrease(++) joint 4 angle\n");
 open_topic_pub = 13;
  }
  else if (ch == 'l' || ch == 'L')
  {
    printf("input : l \tdecrease(--) joint 4 angle\n");
 open_topic_pub = 14;
  }
  else if (ch == 'g' || ch == 'G')
  {
    printf("input : g \topen gripper\n");
 open_topic_pub = 15;
  }
  else if (ch == 'f' || ch == 'F')
  {
    printf("input : f \tclose gripper\n");
 open_topic_pub =16 ;
  }
  else if (ch == '2')
  {
    printf("input : 2 \thome pose\n");
 open_topic_pub = 17;
  }
  else if (ch == '1')
  {
    printf("input : 1 \tinit pose\n");

 open_topic_pub = 18;
  }

  else if (ch == 'b' || ch == 'B')
  { //kudos input
    printf("fuck you\n");
 open_topic_pub = 19;
  }


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "manipulator_key_topicpub_node");
  ros::NodeHandle node_handle_;

  ros::Publisher open_topic_pub_woo = node_handle_.advertise<std_msgs::Int8>("open_key_num", 1000);//kudospub

  char ch;
  printText();
/*  while (ros::ok() || (ch = std::getchar()) != 'q')
  {
    ros::spinOnce();
    //openManipulatorTeleop.printText();
    //ros::spinOnce();
    openManipulatorTeleop.setGoal(ch);
  }*/

  while (ros::ok() && (ch = getch()) != 'q')
  {
    ros::spinOnce();
    printText();
    ros::spinOnce();
    setGoal(ch);
    //kudospub
    std_msgs::Int8 openpub_msg;
    openpub_msg.data = open_topic_pub;
    open_topic_pub_woo.publish(openpub_msg);

  }

  return 0;
}
