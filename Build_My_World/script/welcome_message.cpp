
#include <gazebo/gazebo.hh>

namespace gazebo
{
  class PluginProject1 : public WorldPlugin
  {
    public: PluginProject1() : WorldPlugin()
            {
              printf("Welcome to Mohamed's World!\n");
            }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  GZ_REGISTER_WORLD_PLUGIN(PluginProject1)
}
