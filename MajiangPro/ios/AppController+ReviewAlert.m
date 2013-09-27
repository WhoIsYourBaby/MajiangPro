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

#define kCountActiveAlertWouldShow 10

@implementation AppController (ReviewAlert)

- (void)reviewInApp
{
    NSString *url = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@",kAPPID];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

- (void)scheduleAlert
{
    //已经购买了的也不弹提示
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"noiad"]) {
        return ;
    }
    NSInteger count = [[NSUserDefaults standardUserDefaults] integerForKey:kCountActiveKey];
    if (count < 0) {
        return;
    }
    count ++;
    [[NSUserDefaults standardUserDefaults] setInteger:count forKey:kCountActiveKey];
    if (count != 0 && (count % kCountActiveAlertWouldShow == 0)) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"Would you like review or share it? Your support is my biggest power!" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Remove iAd", @"Share on Weibo", @"Share on Twitter",@"Review", nil];
        [alert show];
        [alert release];
    }
}


- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1) {
        [IOSHelper buyNoIad];
    }
    else if (buttonIndex == 2) {
        [WeiboShareManager LoginAndShareSina];
    }
    else if (buttonIndex == 3) {
        [WeiboShareManager LoginAndShareTwitter];
    } else if (buttonIndex == 4) {
        [self reviewInApp];
    }
}

@end
