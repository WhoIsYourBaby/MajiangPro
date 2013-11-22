//
//  GCHelper.m
//  Puzzle
//
//  Created by Kira on 10/14/13.
//  Copyright (c) 2013 Kira. All rights reserved.
//

#import "GCHelper.h"
#import "AppController.h"
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
        [GKMatchmaker sharedMatchmaker].inviteHandler =^(GKInvite *acceptedInvite, NSArray *playersToInvite) {
            NSLog(@"Received invite");
            self.acceptInvite = acceptedInvite;
            self.invitePlayers = playersToInvite;
            [[AppController shareInterface] findPlayer];
        };
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
    [self reportScore:score forCategory:@"majiang.toplevel"];
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

#pragma mark - 联机对战

- (void)findMatchWithViewController:(UIViewController *)viewController
                       delegate:(id<GCHelperDelegate>)theDelegate {
    
    if (!_gameCenterAvailable) return;
    
    self.matchStarted = NO;
    self.match = nil;
    self.presentingViewController = viewController;
    self.delegate = theDelegate;
    
    if (self.acceptInvite != nil) {
        
        [self.presentingViewController dismissModalViewControllerAnimated:NO];
        GKMatchmakerViewController *mmvc = [[[GKMatchmakerViewController alloc] initWithInvite:self.acceptInvite] autorelease];
        mmvc.matchmakerDelegate = self;
        [self.presentingViewController presentModalViewController:mmvc animated:YES];
        
        self.acceptInvite = nil;
        self.invitePlayers = nil;
        
    } else {
        
        [self.presentingViewController dismissModalViewControllerAnimated:NO];
        GKMatchRequest *request = [[[GKMatchRequest alloc] init] autorelease];
        request.minPlayers = 2;
        request.maxPlayers = 2;
        request.playersToInvite = self.invitePlayers;
        
        GKMatchmakerViewController *mmvc = [[[GKMatchmakerViewController alloc] initWithMatchRequest:request] autorelease];
        mmvc.matchmakerDelegate = self;
        
        [self.presentingViewController presentModalViewController:mmvc animated:YES];
        
        self.acceptInvite = nil;
        self.invitePlayers = nil;
        
    }
}

#pragma mark GKMatchmakerViewControllerDelegate

// The user has cancelled matchmaking
- (void)matchmakerViewControllerWasCancelled:(GKMatchmakerViewController *)viewController {
    NSLog(@"%s -> ", __FUNCTION__);
    viewController.matchmakerDelegate = nil;
    [self.presentingViewController dismissModalViewControllerAnimated:YES];
}

// Matchmaking has failed with an error
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFailWithError:(NSError *)error {
    viewController.matchmakerDelegate = nil;
    [self.presentingViewController dismissModalViewControllerAnimated:YES];
    NSLog(@"Error finding match: %@", error.localizedDescription);
}

// A peer-to-peer match has been found, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindMatch:(GKMatch *)theMatch {
    viewController.matchmakerDelegate = nil;
    [self.presentingViewController dismissModalViewControllerAnimated:YES];
    self.match = theMatch;
    self.match.delegate= self;
    if (!_matchStarted && self.match.expectedPlayerCount == 0) {
        NSLog(@"Ready to start match!");
    }
}

// Players have been found for a server-hosted game, the game should start
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didFindPlayers:(NSArray *)playerIDs
{
    NSLog(@"%s -> ", __FUNCTION__);
}

// An invited player has accepted a hosted invite.  Apps should connect through the hosting server and then update the player's connected state (using setConnected:forHostedPlayer:)
- (void)matchmakerViewController:(GKMatchmakerViewController *)viewController didReceiveAcceptFromHostedPlayer:(NSString *)playerID
{
    NSLog(@"%s -> ", __FUNCTION__);
}


#pragma mark GKMatchDelegate

// The match received data sent from the player.
- (void)match:(GKMatch *)theMatch didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID {
    NSLog(@"%s -> ", __FUNCTION__);
    if (self.match != theMatch) return;
    
    [self.delegate match:theMatch didReceiveData:data fromPlayer:playerID];
}

// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)theMatch player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state {
    if (self.match != theMatch) return;
    NSLog(@"%s -> ", __FUNCTION__);
    switch (state) {
        case GKPlayerStateConnected:
            // handle a new player connection.
            NSLog(@"Player connected!");
            
            if (!_matchStarted && theMatch.expectedPlayerCount ==0) {
                NSLog(@"Ready to start match!");
            }
            
            break;
        case GKPlayerStateDisconnected:
            // a player just disconnected.
            NSLog(@"Player disconnected!");
            _matchStarted = NO;
            [self.delegate matchEnded];
            break;
    }
}

// The match was unable to connect with the player due to an error.
- (void)match:(GKMatch *)theMatch connectionWithPlayerFailed:(NSString *)playerID withError:(NSError *)error {
    NSLog(@"%s -> ", __FUNCTION__);
    if (self.match != theMatch) return;
    
    NSLog(@"Failed to connect to player with error: %@", error.localizedDescription);
    _matchStarted = NO;
    [self.delegate matchEnded];
}

// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)theMatch didFailWithError:(NSError *)error {
    NSLog(@"%s -> ", __FUNCTION__);
    if (self.match != theMatch) return;
    
    NSLog(@"Match failed with error: %@", error.localizedDescription);
    _matchStarted = NO;
    [self.delegate matchEnded];
}
@end
