// [SnakeGame/Head.h]
#include "vector"

#include "Part.h"
#include "Body.h"

class Head : public Part
{
protected:
	void Update() override;

private:
	// <°úÁ¦>
	std::vector<Body*> Tail;
};