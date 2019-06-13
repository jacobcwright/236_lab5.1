#ifndef SELECT_H
#define SELECT_H
#include "tuples.h"

class selectParam {
public:
	virtual bool isSelected(Tuple t) = 0;
	virtual ~selectParam() {}
};

#endif // end select.h
