//
//  CppWrapper.m
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/23/23.
//

#import <Foundation/Foundation.h>
#import "CppWrapper.h"
#import "AiDriver.h"

@implementation CppWrapper

- (int) getMove: (int) a
                 second:(int) b
                 third:(int) c
                 fourth:(int) d
                 fifth:(int) e
                 sixth:(int) f
                 seventh:(int) g
                 eighth:(int) h
          ninth:(int) i{
    AiDriver ai;
    return ai.getMove(a, b, c, d, e, f, g, h, i);
}

@end
