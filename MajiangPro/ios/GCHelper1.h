//
//  GCHelper.h
//  Puzzle
//
//  Created by Kira on 10/14/13.
//  Copyright (c) 2013 Kira. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@protocol GCHelperDelegate
- (void)matchStarted;
- (void)matchEnded;
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID;
@end

@interface GCHelper : NSObject <GKMatchmakerViewControllerDelegate, GKMatchDelegate>

+ (GCHelper *)shareInterface;

@property (assign, readonly) BOOL gameCenterAvailable;
@property (assign, readonly) BOOL userAuthenticated;

- (void)authenticateLocalUser;

//上传分数
- (void)reportTopLevelScore:(int64_t)score;

//联机对战
@property (nonatomic, retain) UIViewController *presentingViewController;
@property (nonatomic, retain) GKMatch *match;
@property (nonatomic, assign) id<GCHelperDelegate> delegate;
@property (nonatomic, assign) BOOL matchStarted;
@property (nonatomic, retain) GKInvite *acceptInvite;
@property (nonatomic, retain) NSArray *invitePlayers;

- (void)findMatchWithViewController:(UIViewController *)viewController
                       delegate:(id<GCHelperDelegate>)theDelegate;

@end
