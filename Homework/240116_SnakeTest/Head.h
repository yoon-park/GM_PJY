// [SnakeGame/Head.h]
#include "vector"

#include "Part.h"
#include "Body.h"

class Head : public Part
{
protected:
	void Update() override;

private:
	// <����>
	std::vector<Body*> Tail;
};