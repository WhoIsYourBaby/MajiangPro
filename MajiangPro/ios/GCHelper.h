//
//  GCHelper.h
//  Puzzle
//
//  Created by Kira on 10/14/13.
//  Copyright (c) 2013 Kira. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface GCHelper : NSObject

+ (GCHelper *)shareInterface;

@property (assign, readonly) BOOL gameCenterAvailable;
@property (assign, readonly) BOOL userAuthenticated;

- (void)authenticateLocalUser;

- (void)reportTopLevelScore:(int64_t)score;

@end
