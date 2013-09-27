//
//  AppDelegate+ReviewAlert.m
//  Puzzle
//
//  Created by Kira on 9/16/13.
//  Copyright (c) 2013 Kira. All rights reserved.
//

#import "AppController+ReviewAlert.h"
#import "WeiboShareManager.h"
#import "IOSHelper.h"


#define kAPPID @"688211409"

#define kCountActiveKey @"kCountActiveKey"

#define kCountActiveAlertWouldShow 3

@implementation AppController (ReviewAlert)

- (void)reviewInApp
{
    NSString *url = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@",kAPPID];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

- (void)scheduleAlert
{
    NSInteger count = [[NSUserDefaults standardUserDefaults] integerForKey:kCountActiveKey];
    if (count < 0) {
        return;
    }
    count ++;
    [[NSUserDefaults standardUserDefaults] setInteger:count forKey:kCountActiveKey];
    if (count != 0 && (count % kCountActiveAlertWouldShow == 0)) {
//        UIActionSheet *act = [[UIActionSheet alloc] initWithTitle:@"Your support is my biggest power!" delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles:@"Review", @"Share on Weibo", @"Share on Twitter", nil];
//        [act showInView:self.window];
//        [act release];
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"Would you like review or share it? Your support is my biggest power!" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Review", @"Share on Weibo", @"Share on Twitter",@"Remove iAd", nil];
        [alert show];
        [alert release];
    }
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        [self reviewInApp];
    }
    else if (buttonIndex == 1) {
        [WeiboShareManager LoginAndShareSina];
    }
    else if (buttonIndex == 2) {
        [WeiboShareManager LoginAndShareTwitter];
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1) {
        [self reviewInApp];
    }
    else if (buttonIndex == 2) {
        [WeiboShareManager LoginAndShareSina];
    }
    else if (buttonIndex == 3) {
        [WeiboShareManager LoginAndShareTwitter];
    } else if (buttonIndex == 4) {
        [IOSHelper buyNoIad];
    }
}



@end
