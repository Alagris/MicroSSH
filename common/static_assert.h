//
//  static_assert.h
//  MicroSSH
//
//  Created by Alagris on 07/12/2017.
//  Copyright © 2017 alagris. All rights reserved.
//

#ifndef static_assert_h
#define static_assert_h

#define STATIC_ASSERT(x) typedef int[x?0:-1]
#endif /* static_assert_h */
