#include "ANIM.H"

void main(void)
{
  fegl::anim & My = fegl::anim::Get();
  My<<new fegl::object<<new fegl::SnowMan;
  My<<new fegl::object<<new fegl::XmasTree;
  My.Run();
}

                  
