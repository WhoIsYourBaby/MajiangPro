//
//  MaJiongAppController.h
//  MaJiong
//
//  Created by HalloWorld on 12-12-5.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

@class RootViewController;
#import "GCHelper.h"

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate, GCHelperDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

+ (AppController *)shareInterface;

- (void)findPlayer;

@end

