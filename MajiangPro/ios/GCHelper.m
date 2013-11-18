//
//  GCHelper.m
//  Puzzle
//
//  Created by Kira on 10/14/13.
//  Copyright (c) 2013 Kira. All rights reserved.
//

#import "GCHelper.h"

@implementation GCHelper

static GCHelper *helperInterface = nil;

+ (GCHelper *)shareInterface
{
    if (helperInterface == nil) {
        helperInterface = [[self alloc] init];
    }
    return helperInterface;
}

- (BOOL) isGameCenterAvailable
{
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

- (id)init {
    if ((self = [super init])) {
        _gameCenterAvailable = [self isGameCenterAvailable];
        if (_gameCenterAvailable) {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
        }
    }
    return self;
}

- (void)authenticationChanged {
    
    if ([GKLocalPlayer localPlayer].isAuthenticated && !_userAuthenticated) {
        _userAuthenticated = TRUE;
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && _userAuthenticated) {
        _userAuthenticated = FALSE;
    }
}

#pragma mark User functions

- (void)authenticateLocalUser {
    
    if (!_gameCenterAvailable) return;
    if ([GKLocalPlayer localPlayer].authenticated == NO) {
        [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
    } else {
        NSLog(@"Already authenticated!");
    }
}

- (void)reportTopLevelScore:(int64_t)score
{
    [self reportScore:score forCategory:@"puzzlepro.toplevel"];
}

- (void)reportScore:(int64_t)score forCategory: (NSString*)category
{
     GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:category] autorelease];
     scoreReporter.value = score;
     [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
         if (error != nil)
         {
             // handle the reporting error
            NSLog(@"上传分数出错.");
             //If your application receives a network error, you should not discard the score.
             //Instead, store the score object and attempt to report the player’s process at
             //a later time.
        }else {
            NSLog(@"上传分数成功");
            [self showBanner];
        }
     }];
}

- (void)showBanner
{
    [GKNotificationBanner showBannerWithTitle:NSLocalizedString(@"topLevelCongratulations", nil) message:NSLocalizedString(@"newTopLevel", nil)
                            completionHandler:^{
                                NSLog(@"%s -> ", __FUNCTION__);
                            }];
}

@end
