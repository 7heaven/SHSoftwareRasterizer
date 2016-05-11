//
//  IDecoder.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/11.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef IDecoder_h
#define IDecoder_h

#include <string.h>

namespace sh{
class IDecoder{
public:
    virtual std::string getFormat() = 0;
    
    virtual ~IDecoder();
}
}

#endif
