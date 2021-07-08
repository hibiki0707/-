#ifndef SCENE_H_INCLIDED
#define SCENE_H_INCLIDED

namespace Battle {
	class Player;
}

class Scene
{
private:
	Battle::Player* player_;
public:
	void Update();
};

#endif