#ifndef __TEST_H__
#define __TEST_H__

#include "Common/Task/TaskBase.h"

class Test1 : public TaskBase{

private:

	int mHandle;
	int mPosX;

public :

	Test1(int posX);
	~Test1();

	bool Initialize() override;
	bool Updata() override;
	void Draw() override ;
	void Finalize() override;
	
};

#endif