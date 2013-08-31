//
//  MaJiongAppController.h
//  MaJiong
//
//  Created by HalloWorld on 12-12-5.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "GADBannerView.h"
#import <iAd/iAd.h>
#include "CCDirector.h"

@interface RootViewController : UIViewController <GADBannerViewDelegate, ADBannerViewDelegate> {
    GADBannerView *admobView;
    ADBannerView *iadView;
}

@end
