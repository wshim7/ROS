#ifndef __ROSCIR_COMMON_FLASER_H__
#define __ROSCIR_COMMON_FLASER_H__

#include <roscir/device/data/FLaserRangeFinderData.h>
#include <roscir/device/CirApi.h>

class CIRAPI CFLaserRangeFinder
{

public :
	virtual ~CFLaserRangeFinder() {}


	/** \brief
		read laser data
	\remarks
		after funtion call, it set a laser data
	\return
		void
	\author
		cspark
	*/
	virtual void readData(CFLaserRangeFinderData& data) =0;
};

#endif /* __ROSCIR_COMMON_FLASER_H__ */